#include "Collision Resolver.h"

void Senku2D::CollisionResolver::ResolvePenetration(ContactList* pContactList)
 {
	//Resolving Penetration According to Inverse Mass of the Bodies
	//
	//Iterating through the List
	for (unsigned int i = 0; i < pContactList->GetLimit(); ++i)
	{
		//Getting the Contact Data For Each Pair of Rigid Bodies
		CollisionData* pContactData = pContactList->GetContactData(i);

		//If Penetration is Negative or Zero then Continue
		if (pContactData->_Contact.Penetration <= 0)
		{
			continue;
		}

		//Setting References to Bodies
		RigidBody& RB1 = *pContactData->_Bodies.RigidBodies[0];
		RigidBody& RB2 = *pContactData->_Bodies.RigidBodies[1];

		//Getting the Total Inverse Mass of the Pair of Rigid Bodies
		Real TotalInvMass = RB1.GetInverseMass() + RB2.GetInverseMass();

		//If Both Rigid Bodies have Infinite Mass, Then Do Nothing
		if (TotalInvMass <= 0)
		{
			continue;
		}

		//Amount of Movement Required To Move Each Body Appart
		Vector2 MovePerInvMass = pContactData->_Contact.ContactNormal * (pContactData->_Contact.Penetration / TotalInvMass);
		
		//Setting Positions of Rigid Bodies
		RB1.SetPosition((MovePerInvMass * RB1.GetInverseMass()) + RB1.GetPosition());
		RB2.SetPosition((MovePerInvMass * -RB2.GetInverseMass()) + RB2.GetPosition());
	}
}

void Senku2D::CollisionResolver::ResolveVelocity(ContactList* pContactList, const Real& Timestep)
{
	//Iterating through the List
	for (unsigned int i = 0; i < pContactList->GetLimit(); ++i)
	{
		//Getting the Contact Data For Each Pair of Rigid Bodies
		CollisionData* pContactData = pContactList->GetContactData(i);

		if (pContactData->_Bodies.RigidBodies[0] == nullptr ||
			pContactData->_Bodies.RigidBodies[1] == nullptr)
		{
			continue;
		}

		//Calculating Separating Velocity
		Real SeparatingVelocity = CalculateSeparatingVelocity(pContactData);

		//Check if Resolution is Required
		if (SeparatingVelocity > 0)
		{
			continue;
		}

		//Setting RigidBody References
		RigidBody& RB1 = *pContactData->_Bodies.RigidBodies[0];
		RigidBody& RB2 = *pContactData->_Bodies.RigidBodies[1];

		//Getting Velocity Caused By Acceleration Build Up
		Vector2 AccCausedVel = Vector2(RB1.GetLinearAcceleration())
			- RB2.GetLinearAcceleration();
		//Getting Separating Velocity Caused By Acceleration Build Up
		Real AccCausedSeparatingVel = AccCausedVel * pContactData->_Contact.ContactNormal * Timestep;
		
		//Calculating Restitution
		Restitution = Real_Min(RB1.GetRestitution(), 
			RB2.GetRestitution());

		//New Separating Velocity
		Real NewSepVelocity = -SeparatingVelocity * Restitution;

		if (AccCausedSeparatingVel < 0)
		{
			NewSepVelocity += Restitution * AccCausedSeparatingVel;

			if (NewSepVelocity < 0)
			{
				NewSepVelocity = 0;
			}
		}
		//Getting Delta Velocity
		Real DeltaVelocity = NewSepVelocity - SeparatingVelocity;

		//Getting Inverse Mass
		Real TotalInvMass = RB1.GetInverseMass()
			+ RB2.GetInverseMass();

		//Calculating the Impulse to Apply
		Real Impulse = DeltaVelocity / TotalInvMass;
		Vector2 ImpulsePerInvMass = pContactData->_Contact.ContactNormal * Impulse;

		//Setting Impulses
		RB1.SetLinearVelocity(ImpulsePerInvMass * 
			RB1.GetInverseMass() +
			RB1.GetLinearVelocity());

		RB2.SetLinearVelocity(ImpulsePerInvMass *
			-RB2.GetInverseMass() +
			RB2.GetLinearVelocity());
	}
}

Senku2D::Real Senku2D::CollisionResolver::CalculateSeparatingVelocity(CollisionData* CD)
{
	Vector2 RelativeVelocity = Senku2D::Vector2(CD->_Bodies.RigidBodies[0]->GetLinearVelocity())
		- CD->_Bodies.RigidBodies[1]->GetLinearVelocity();
	return RelativeVelocity * CD->_Contact.ContactNormal;
}

Senku2D::CollisionResolver::CollisionResolver()	:
	Restitution(0.1f)
{

}

Senku2D::CollisionResolver::~CollisionResolver()
{

}

void Senku2D::CollisionResolver::Resolve(ContactList* pContactList, const Real& Timestep)
{
	ResolvePenetration(pContactList);
	ResolveVelocity(pContactList, Timestep);
}
