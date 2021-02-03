#include "Broad Phase.h"

void Senku2D::BroadPhase::InsertDynamicBodiesToGrid(HashedGrid::Grid* pGrid, RigidBodyList* pRBList)
{
	const size_t& Size = pRBList->GetDynamicBodyListSize();
	for (size_t i = 0; i < Size; ++i)
	{
		pGrid->Insert(pRBList->GetRigidBodyFromDynamicList(i));
	}
}

void Senku2D::BroadPhase::InsertStaticBodiesToGrid(HashedGrid::Grid* pGrid, RigidBodyList* pRBList)
{
	const size_t& Size = pRBList->GetStaticBodyListSize();
	for (size_t i = 0; i < Size; ++i)
	{
		pGrid->Insert(pRBList->GetRigidBodyFromStaticList(i));
	}
}

unsigned int Senku2D::BroadPhase::QueryDynamicBodiesUsingGrid(HashedGrid::Grid* pGrid, PotentialContactList* pList, const unsigned int& RegisteredNumOfContacts)
{
	unsigned int NumOfContacts = 0;

	NumOfContacts = pGrid->QueryActiveCells(pList, RegisteredNumOfContacts);

	return NumOfContacts;
}

unsigned int Senku2D::BroadPhase::QueryStaticBodiesUsingGrid(HashedGrid::Grid* pGrid, RigidBodyList* pRBList, PotentialContactList* pList, const unsigned int& RegisteredNumOfContacts)
{
	unsigned int NumOfContacts = RegisteredNumOfContacts;
	
	const size_t& Size = pRBList->GetDynamicBodyListSize();
	for (size_t i = 0; i < Size; ++i)
	{
		unsigned int LocalNumOfContacts = pGrid->QueryRigidBody(pRBList->GetRigidBodyFromDynamicList(i), pList,
			NumOfContacts);

		if (LocalNumOfContacts > 0)
		{
			NumOfContacts = LocalNumOfContacts;
		}
	}
	
	return NumOfContacts;
}
