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

		//Getting the Total Inverse Mass of the Pair of Rigid Bodies
		Real TotalInvMass = pContactData->_Bodies.RigidBodies[0]->GetInverseMass() + pContactData->_Bodies.RigidBodies[1]->GetInverseMass();

		//If Both Rigid Bodies have Infinite Mass, Then Do Nothing
		if (TotalInvMass <= 0)
		{
			continue;
		}

		//Amount of Movement Required To Move Each Body Appart
		Vector2 MovePerInvMass = pContactData->_Contact.ContactNormal * (pContactData->_Contact.Penetration / TotalInvMass);
		
		//Setting Positions of Rigid Bodies
		pContactData->_Bodies.RigidBodies[0]->SetPosition((MovePerInvMass * pContactData->_Bodies.RigidBodies[0]->GetInverseMass()) + pContactData->_Bodies.RigidBodies[0]->GetPosition());
		pContactData->_Bodies.RigidBodies[1]->SetPosition((MovePerInvMass * -pContactData->_Bodies.RigidBodies[1]->GetInverseMass()) + pContactData->_Bodies.RigidBodies[1]->GetPosition());
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
			return;
		}

		//Getting Velocity Caused By Acceleration Build Up
		Vector2 AccCausedVel = Vector2(pContactData->_Bodies.RigidBodies[0]->GetLinearAcceleration())
			- pContactData->_Bodies.RigidBodies[1]->GetLinearAcceleration();
		//Getting Separating Velocity Caused By Acceleration Build Up
		Real AccCausedSeparatingVel = AccCausedVel * pContactData->_Contact.ContactNormal * Timestep;
		
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
		Real TotalInvMass = pContactData->_Bodies.RigidBodies[0]->GetInverseMass()
			+ pContactData->_Bodies.RigidBodies[1]->GetInverseMass();

		//Calculating the Impulse to Apply
		Real Impulse = DeltaVelocity / TotalInvMass;
		Vector2 ImpulsePerInvMass = pContactData->_Contact.ContactNormal * Impulse;

		//Setting Impulses
		pContactData->_Bodies.RigidBodies[0]->SetLinearVelocity(ImpulsePerInvMass * 
			pContactData->_Bodies.RigidBodies[0]->GetInverseMass() +
			pContactData->_Bodies.RigidBodies[0]->GetLinearVelocity());

		pContactData->_Bodies.RigidBodies[1]->SetLinearVelocity(ImpulsePerInvMass *
			-pContactData->_Bodies.RigidBodies[1]->GetInverseMass() +
			pContactData->_Bodies.RigidBodies[1]->GetLinearVelocity());
	}
}

Senku2D::Real Senku2D::CollisionResolver::CalculateSeparatingVelocity(CollisionData* CD)
{
	Vector2 RelativeVelocity = Senku2D::Vector2(CD->_Bodies.RigidBodies[0]->GetLinearVelocity())
		- CD->_Bodies.RigidBodies[1]->GetLinearVelocity();
	return RelativeVelocity * CD->_Contact.ContactNormal;
}

Senku2D::CollisionResolver::CollisionResolver()	:
	Restitution(0.1)
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
