#include "Narrow Phase.h"

unsigned int Senku2D::NarrowPhase::GeneratePrimitiveTestResultsList(PotentialContactList* OldContacts, PotentialContactList* NewContacts)
{
	unsigned int NumOfContacts = 0;

	//Primitive AABB Test
	for (unsigned int i = 0; i < OldContacts->GetLimit(); ++i)
	{
		//Getting the Rigid Bodies
		RigidBody* pRB1 = OldContacts->GetContact(i).RigidBodies[0];
		RigidBody* pRB2 = OldContacts->GetContact(i).RigidBodies[1];

		//Checking if their AABBs Overlap
		if (pRB1->Overlaps(pRB2->GetAABB()))
		{
			//Potential Contact Generated
			NewContacts->GetContact(i).RigidBodies[0] = pRB1;
			NewContacts->GetContact(i).RigidBodies[1] = pRB2;

			//Increment Number of Contacts
			++NumOfContacts;
		}
	}

	return NumOfContacts;
}

unsigned int Senku2D::NarrowPhase::GenerateShapeTestResultsList(PotentialContactList* PotentialContacts, ContactList* CList)
{
	unsigned int NumOfContacts = 0;

	for (unsigned int i = 0; i < PotentialContacts->GetLimit(); ++i)
	{
		//Maximum Limit For the Contact List Reached?
		if (NumOfContacts >= CList->GetLimit())
		{
			break;
		}

		//Getting the Potential Contact
		PotentialRigidBodyContact& rPRBC = PotentialContacts->GetContact(i);

		//Getting the Shape Pair
		ShapePairs CurrentShapePair = ShapeSolver::Get().GetShapePair(rPRBC.RigidBodies[0]->GetShape()->GetShapeType(), rPRBC.RigidBodies[1]->GetShape()->GetShapeType());

		//Doing the Correct Shape Test Based on the Current Shape Pair
		bool CollisionTestResult = false;
		switch (CurrentShapePair)
		{
		case ShapePairs::BOX_AND_BOX:
			CollisionTestResult = CollisionDetector::BoxAndBox(&rPRBC, &CList->GetContactData(NumOfContacts));
			break;
		case ShapePairs::BOX_AND_CIRCLE:
			CollisionTestResult = CollisionDetector::BoxAndCircle(&rPRBC, &CList->GetContactData(NumOfContacts));
			break; 
		case ShapePairs::CIRCLE_AND_CIRCLE:
			CollisionTestResult = CollisionDetector::CircleAndCircle(&rPRBC, &CList->GetContactData(NumOfContacts));
			break;
		}

		//Collision Has Happened
		if (CollisionTestResult)
		{
			//Increase the Number of Contacts Found
			++NumOfContacts;
		}
	}

	return NumOfContacts;
}
