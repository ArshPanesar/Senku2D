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
		Vector2 MovePerInvMass = pContactData->_Contact.ContactNormal * (-pContactData->_Contact.Penetration / TotalInvMass);

		//Setting Positions of Rigid Bodies
		pContactData->_Bodies.RigidBodies[0]->SetPosition((MovePerInvMass * pContactData->_Bodies.RigidBodies[0]->GetInverseMass()) + pContactData->_Bodies.RigidBodies[0]->GetPosition());
		pContactData->_Bodies.RigidBodies[1]->SetPosition((MovePerInvMass * -pContactData->_Bodies.RigidBodies[1]->GetInverseMass()) + pContactData->_Bodies.RigidBodies[1]->GetPosition());
	}
}

Senku2D::CollisionResolver::CollisionResolver()
{

}

Senku2D::CollisionResolver::~CollisionResolver()
{

}

void Senku2D::CollisionResolver::Resolve(ContactList* pContactList)
{
	//Resolve Penetration
	ResolvePenetration(pContactList);
}
