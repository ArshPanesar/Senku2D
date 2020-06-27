#include "Narrow Phase.h"

unsigned int Senku2D::NarrowPhase::GeneratePrimitiveTestResultsList(PotentialContactList* OldContacts, PotentialContactList* NewContacts)
{
	unsigned int NumOfContacts = 0;

	//Primitive AABB Test
	for (unsigned int i = 0; i < OldContacts->GetLimit(); ++i)
	{
		//Getting the Rigid Bodies
		RigidBody* pRB1 = OldContacts->GetContact(i)->RigidBodies[0];
		RigidBody* pRB2 = OldContacts->GetContact(i)->RigidBodies[1];

		//Checking if their AABBs Overlap
		if (pRB1->Overlaps(pRB2->GetAABB()))
		{
			//Potential Contact Generated
			NewContacts->GetContact(i)->RigidBodies[0] = pRB1;
			NewContacts->GetContact(i)->RigidBodies[1] = pRB2;

			//Increment Number of Contacts
			++NumOfContacts;
		}
	}

	return NumOfContacts;
}
