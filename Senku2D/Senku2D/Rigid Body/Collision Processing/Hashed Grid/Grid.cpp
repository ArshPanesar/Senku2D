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

unsigned int Senku2D::HashedGrid::Grid::QueryRay(const Ray& QueryRay, std::vector<RigidBody*>& RBList)
{
	unsigned int NumOfBodies = 0;

	//Start and End Positions
	CellPosition CurrentPosition, EndPosition;
	CurrentPosition.x = (int)(QueryRay.PointA.x / m_CellSize.x);
	CurrentPosition.y = (int)(QueryRay.PointA.y / m_CellSize.y);
	EndPosition.x = (int)(QueryRay.PointB.x / m_CellSize.x);
	EndPosition.y = (int)(QueryRay.PointB.y / m_CellSize.y);

	//Step Direction
	CellPosition Step;
	Step.x = ((CurrentPosition.x < EndPosition.x) ? 1 : ((CurrentPosition.x > EndPosition.x) ? -1 : 0));
	Step.y = ((CurrentPosition.y < EndPosition.y) ? 1 : ((CurrentPosition.y > EndPosition.y) ? -1 : 0));
	
	//Calculating tx and ty
	Real MinX = m_CellSize.x * Real_Floor(QueryRay.PointA.x / m_CellSize.x), MaxX = MinX + m_CellSize.x;
	Real tx = ((QueryRay.PointA.x < QueryRay.PointB.x) ? (MaxX - QueryRay.PointA.x) : (QueryRay.PointA.x - MinX)) / Real_Abs(QueryRay.PointB.x - QueryRay.PointA.x);
	Real MinY = m_CellSize.y * Real_Floor(QueryRay.PointA.y / m_CellSize.y), MaxY = MinY + m_CellSize.y;
	Real ty = ((QueryRay.PointA.y < QueryRay.PointB.y) ? (MaxY - QueryRay.PointA.y) : (QueryRay.PointA.y - MinY)) / Real_Abs(QueryRay.PointB.y - QueryRay.PointA.y);

	//Calculating DeltaX and DeltaY
	Real DeltatX = m_CellSize.x / Real_Abs(QueryRay.PointB.x - QueryRay.PointA.x);
	Real DeltatY = m_CellSize.y / Real_Abs(QueryRay.PointB.y - QueryRay.PointA.y);

	//Visiting Each Cell
	while (true)
	{
		if (m_Map.count(CurrentPosition) != 0)
		{
			NumOfBodies += 
				m_CellHandler.QueryForRay(m_CellData, m_Map[CurrentPosition], RBList);
		}

		if (CurrentPosition == EndPosition)
		{
			break;
		}

		// tx smallest, step in x
		if (tx < ty)
		{
			tx += DeltatX;
			CurrentPosition.x += Step.x;
		}
		// ty smallest, step in y
		else
		{
			ty += DeltatY;
			CurrentPosition.y += Step.y;
		}
	}

	return NumOfBodies;
}

unsigned int Senku2D::HashedGrid::Grid::QueryAABB(AABB& Box, std::vector<RigidBody*>& RBList)
{
	unsigned int NumOfBodies = 0;

	CellPosition StartPosition, EndPosition;
	StartPosition.x = (int)(Box.Position.x / m_CellSize.x);
	StartPosition.y = (int)(Box.Position.y / m_CellSize.y);
	EndPosition.x = (int)((Box.Position.x + Box.Size.x) / m_CellSize.x);
	EndPosition.y = (int)((Box.Position.y + Box.Size.y) / m_CellSize.y);

	CellPosition CurrentPosition;
	for (int i = StartPosition.x; i <= EndPosition.x; ++i)
	{
		for (int j = StartPosition.y; j <= EndPosition.y; ++j)
		{
			CurrentPosition.x = i;
			CurrentPosition.y = j;

			if (m_Map.count(CurrentPosition) > 0)
			{
				NumOfBodies += m_CellHandler.QueryForAABB(m_CellData, m_Map[CurrentPosition],
					RBList, Box);
			}
		}
	}

	return NumOfBodies;
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
