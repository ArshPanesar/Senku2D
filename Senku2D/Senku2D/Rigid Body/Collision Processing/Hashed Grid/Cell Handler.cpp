#include "Cell Handler.h"

Senku2D::HashedGrid::CellHandler::CellHandler(CellData& CD)	:
	m_NumOfBodies(4),
	EmptyBitFlag(0),
	CheckedBitFlag(1)
{
	//Resizing Number of Cells
	CD.BodyList.resize(DEFAULT_NUM_OF_CELLS);
	CD.Flags.resize(DEFAULT_NUM_OF_CELLS);
}

Senku2D::HashedGrid::CellHandler::~CellHandler()
{

}

void Senku2D::HashedGrid::CellHandler::AddData(CellData& CD, RigidBody* pRB, const size_t& Index)
{	
	if (CD.BodyList.size() < (Index + 1))
	{
		//Possible Reallocation to Accomodate More Cells
		const size_t NewSize = CD.BodyList.size() + DEFAULT_NUM_OF_CELLS;
		CD.BodyList.resize(NewSize);

		for (size_t i = Index; i < NewSize; ++i)
		{
			CD.BodyList[i].reserve(m_NumOfBodies);
		}
	}

	CD.BodyList[Index].push_back(pRB);
	CD.Flags[Index].set(EmptyBitFlag, false);
}

unsigned int Senku2D::HashedGrid::CellHandler::QueryRigidBody(CellData& CD, RigidBody* pRB, const size_t& Index, PotentialContactList* pList, const unsigned int& RegisteredNumOfContacts)
{
	unsigned int NumOfContacts = RegisteredNumOfContacts;

	//Checking if the Cell is Either Empty or Already Been Checked
	if (CD.Flags[Index].test(EmptyBitFlag) == false)
	{
		const size_t& Size = CD.BodyList[Index].size();
		for (size_t i = 0; i < Size; ++i)
		{
			if (NumOfContacts < pList->GetLimit())
			{
				if (pRB != CD.BodyList[Index][i])
				{
					pList->GetContact(NumOfContacts).RigidBodies[0] = pRB;
					pList->GetContact(NumOfContacts).RigidBodies[1] = CD.BodyList[Index][i];
					++NumOfContacts;
				}
			}
			else
			{
				break;
			}
		}
	}

	if (NumOfContacts == RegisteredNumOfContacts)
	{
		//No New Contacts Found
		return 0;
	}

	return NumOfContacts;
}

unsigned int Senku2D::HashedGrid::CellHandler::QueryWithSize(CellData& CD, const size_t& Size, PotentialContactList* pList, const unsigned int& RegisteredNumOfContacts)
{
	unsigned int NumOfContacts = RegisteredNumOfContacts;

	for (size_t k = 0; k < Size; ++k)
	{
		const size_t& RBListSize = CD.BodyList[k].size();

		//If There are No or Only One Body in this Cell, Continue with the Next Cell
		if (RBListSize < 2)
		{
			continue;
		}

		for(size_t i = 0; i < RBListSize - 1; ++i)
		{
			for (size_t j = i + 1; j < RBListSize; ++j)
			{
				if (NumOfContacts < pList->GetLimit())
				{
					pList->GetContact(NumOfContacts).RigidBodies[0] = CD.BodyList[k][i];
					pList->GetContact(NumOfContacts).RigidBodies[1] = CD.BodyList[k][j];
					++NumOfContacts;
				}
				else
				{
					break;
				}
			}
		}
	}

	if (NumOfContacts == RegisteredNumOfContacts)
	{
		//No New Contacts Found
		return 0;
	}

	return NumOfContacts;
}

unsigned int Senku2D::HashedGrid::CellHandler::QueryForRay(CellData& CD, const size_t& Index, std::vector<RigidBody*>& RBList)
{
	unsigned int NumOfBodies = 0;

	if (CD.Flags[Index].test(EmptyBitFlag) == false)
	{
		//Running Through the Rigid Body List in the Given Cell
		std::vector<RigidBody*>& BodiesInCell = CD.BodyList[Index];
		for (size_t i = 0; i < BodiesInCell.size(); ++i)
		{
			RBList.push_back(BodiesInCell[i]);
			++NumOfBodies;
		}
	}

	return NumOfBodies;
}

void Senku2D::HashedGrid::CellHandler::ClearData(CellData& CD, const size_t& Size)
{
	for (size_t i = 0; i < Size; ++i)
	{
		//Clearing the Body List
		CD.BodyList[i].clear();
		CD.BodyList[i].reserve(m_NumOfBodies);

		//Resetting the Flags List
		CD.Flags[i].reset();
	}
}

