#include "Grid.h"

Senku2D::HashedGrid::Grid::Grid()	:
	m_Map(),
	m_CellData(),
	m_CellHandler(m_CellData),
	m_CellSize(DEFAULT_CELL_WIDTH, DEFAULT_CELL_HEIGHT),
	m_CellIndex(0)
{
	m_Map.reserve(DEFAULT_NUM_OF_CELLS * 2);
}

Senku2D::HashedGrid::Grid::~Grid()
{
	m_Map.clear();
	m_CellHandler.ClearData(m_CellData, m_CellData.BodyList.size());
	m_CellData.BodyList.clear();
	m_CellData.Flags.clear();
	m_CellSize.Clear();
	m_CellIndex = 0;
}

void Senku2D::HashedGrid::Grid::SetCellSize(const Real& CellWidth, const Real& CellHeight)
{
	m_CellSize = Vector2(CellWidth, CellHeight);
}

void Senku2D::HashedGrid::Grid::Insert(RigidBody* pRB)
{
	//Getting the Cell Positions
	CellPosition StartPosition, EndPosition;
	StartPosition.x = (int)(pRB->GetAABB().Position.x / m_CellSize.x);
	StartPosition.y = (int)(pRB->GetAABB().Position.y / m_CellSize.y);
	EndPosition.x = (int)((pRB->GetAABB().Position.x + pRB->GetAABB().Size.x) / m_CellSize.x);
	EndPosition.y = (int)((pRB->GetAABB().Position.y + pRB->GetAABB().Size.y) / m_CellSize.y);

	//Filling the Cell(s) With the Rigid Body
	if (StartPosition == EndPosition)
	{
		//Check if Key Already Exists
		if (m_Map.count(StartPosition) == 0)
		{
			m_Map[StartPosition] = m_CellIndex;

			//Adding the Body to the Cell
			m_CellHandler.AddData(m_CellData, pRB, m_CellIndex);

			//Incrementing the Cell Index
			++m_CellIndex;
		}
		else
		{
			//Key Already Exists
			//Adding the Body to the Cell
			m_CellHandler.AddData(m_CellData, pRB, m_Map[StartPosition]);
		}
	}
	else
	{
		for (int i = StartPosition.x; i <= EndPosition.x; ++i)
		{
			for (int j = StartPosition.y; j <= EndPosition.y; ++j)
			{
				CellPosition Position;
				Position.x = i;
				Position.y = j;

				//Check if Key Already Exists
				if (m_Map.count(Position) == 0)
				{
					m_Map[Position] = m_CellIndex;

					//Adding the Body to the Cell
					m_CellHandler.AddData(m_CellData, pRB, m_CellIndex);

					//Incrementing the Cell Index
					++m_CellIndex;
				}
				else
				{
					//Key Already Exists
					//Adding the Body to the Cell
					m_CellHandler.AddData(m_CellData, pRB, m_Map[Position]);
				}
			}
		}		
	}
}

unsigned int Senku2D::HashedGrid::Grid::QueryRigidBody(RigidBody* pRB, PotentialContactList* pList, const unsigned int& RegisteredNumOfContacts)
{
	unsigned int NumOfContacts = RegisteredNumOfContacts;

	//Getting the Cell Positions
	CellPosition StartPosition, EndPosition;
	StartPosition.x = (int)(pRB->GetAABB().Position.x / m_CellSize.x);
	StartPosition.y = (int)(pRB->GetAABB().Position.y / m_CellSize.y);
	EndPosition.x = (int)((pRB->GetAABB().Position.x + pRB->GetAABB().Size.x) / m_CellSize.x);
	EndPosition.y = (int)((pRB->GetAABB().Position.y + pRB->GetAABB().Size.y) / m_CellSize.y);

	//Querying the Cell(s) With the Rigid Body
	if (StartPosition == EndPosition && m_Map.count(StartPosition) == 1)
	{
		NumOfContacts = m_CellHandler.QueryRigidBody(m_CellData, pRB, m_Map[StartPosition], 
			pList, RegisteredNumOfContacts);
	}
	else
	{
		for (int i = StartPosition.x; i <= EndPosition.x; ++i)
		{
			for (int j = StartPosition.y; j <= EndPosition.y; ++j)
			{
				CellPosition Position;
				Position.x = i;
				Position.y = j;

				if (m_Map.count(Position) == 0)
				{
					continue;
				}

				unsigned int LocalNumOfContacts = m_CellHandler.QueryRigidBody(m_CellData, pRB, 
					m_Map[Position], pList, NumOfContacts);

				if (LocalNumOfContacts > 0)
				{
					NumOfContacts = LocalNumOfContacts;
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

unsigned int Senku2D::HashedGrid::Grid::QueryActiveCells(PotentialContactList* pList, const unsigned int& RegisteredNumOfContacts)
{
	unsigned int NumOfContacts = 0;

	NumOfContacts = m_CellHandler.QueryWithSize(m_CellData, m_CellIndex + 1, pList, RegisteredNumOfContacts);

	return NumOfContacts;
}

void Senku2D::HashedGrid::Grid::Clear()
{
	//Clearing Map
	m_Map.clear();
	m_Map.reserve(DEFAULT_NUM_OF_CELLS * 2);

	//Clearing Cell Data
	m_CellHandler.ClearData(m_CellData, m_CellIndex + 1);

	//Resetting Cell Index
	m_CellIndex = 0;
}
