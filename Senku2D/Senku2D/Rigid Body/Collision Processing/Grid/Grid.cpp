#include "Grid.h"

Senku2D::Grid::Grid(const AABB& Bounds, const Vector2& TileSize)	:
	m_Bounds(Bounds),
	m_TileSize(TileSize),
	m_Matrix(),
	m_DefaultNoBodyValue(0),
	m_RBCurrentIndex(m_DefaultNoBodyValue + 1),
	p_GridBodyList(nullptr)
{
	//Number of Rows and Columns
	m_NumOfCols = (U32)Real_Ceil(Bounds.Size.x / TileSize.x);
	m_NumOfRows = (U32)Real_Ceil(Bounds.Size.y / TileSize.y);

	//Maximum Number of Static Bodies Allowed
	U32 MaxNumOfBodies = m_NumOfCols * m_NumOfRows;
	
	//Allocating Grid Body List
	p_GridBodyList = std::make_unique<GridBodyList>(MaxNumOfBodies);

	//Resizing Matrix
	m_Matrix.resize(m_NumOfRows);
	for (auto& Row : m_Matrix)
	{
		Row.resize(m_NumOfCols);
	}

	//Filling the Matrix With Default Value
	for (auto& Row : m_Matrix)
	{
		for (auto& Col : Row)
		{
			Col = 0;
		}
	}
}

Senku2D::Grid::~Grid()
{
	//Clearing the Matrix
	m_Matrix.clear();
}

void Senku2D::Grid::AddBody(RigidBody* pRB)
{
	//Checking if Rigid Body Overlaps the Bounds of this Grid
	if (m_Bounds.Overlaps(pRB->GetAABB()))
	{
		//Getting Rigid Body Position and Size Relative to the Origin of the Grid
		Vector2 RBPosition = pRB->GetPosition();
		Vector2 RB_RelativePosition = RBPosition - m_Bounds.Position;
		Vector2 RBSize = pRB->GetAABB().Size;
		Vector2 RB_RelativeSize = RB_RelativePosition + RBSize;;

		//Starting Column and Starting Row
		U32 StartingCol = (U32)Real_Floor(RB_RelativePosition.x / m_TileSize.x);
		U32 StartingRow = (U32)Real_Floor(RB_RelativePosition.y / m_TileSize.y);

		//Ending Column and Ending Row(Might Be the Same as Starting Row and Column)
		U32 EndingCol = (U32)Real_Floor(RB_RelativeSize.x / m_TileSize.x);
		U32 EndingRow = (U32)Real_Floor(RB_RelativeSize.y / m_TileSize.y);

		//Asserting that Ending Colmmn and Row Don't Exceed the Max Limit
		assert((EndingCol < m_NumOfCols) && (EndingRow < m_NumOfRows)
			&& "Ending Column and/or Ending Row Exceed the Maximum Limit!");

		//Filling the Matrix with an Index
		for (U32 CurrentRow = StartingRow; CurrentRow <= EndingRow; ++CurrentRow)
		{
			for (U32 CurrentCol = StartingCol; CurrentCol <= EndingCol; ++CurrentCol)
			{
				m_Matrix[CurrentRow][CurrentCol] = m_RBCurrentIndex;
			}
		}

		//Adding the Body to the Grid List at this Index
		p_GridBodyList->AddAtIndex(m_RBCurrentIndex, pRB);

		//Incrementing the Index for the Next Body to be Added
		++m_RBCurrentIndex;
	}
}

Senku2D::U32 Senku2D::Grid::Query(RigidBody* pRB, PotentialContactList* pList)
{
	U32 NumOfPotentialContactsFound = 0;

	if (m_Bounds.Overlaps(pRB->GetAABB()))
	{
		//Getting Rigid Body Position and Size Relative to the Origin of the Grid
		Vector2 RBPosition = pRB->GetPosition();
		Vector2 RB_RelativePosition = RBPosition - m_Bounds.Position;
		Vector2 RBSize = pRB->GetAABB().Size;
		Vector2 RB_RelativeSize = RB_RelativePosition + RBSize;;

		//Starting Column and Starting Row
		U32 StartingCol = (U32)Real_Floor(RB_RelativePosition.x / m_TileSize.x);
		U32 StartingRow = (U32)Real_Floor(RB_RelativePosition.y / m_TileSize.y);

		//Ending Column and Ending Row(Might Be the Same as Starting Row and Column)
		U32 EndingCol = (U32)Real_Floor(RB_RelativeSize.x / m_TileSize.x);
		U32 EndingRow = (U32)Real_Floor(RB_RelativeSize.y / m_TileSize.y);

		//Asserting that Ending Colmmn and Row Don't Exceed the Max Limit
		assert((EndingCol < m_NumOfCols) && (EndingRow < m_NumOfRows)
			&& "Querying Error: Ending Column and/or Ending Row Exceed the Maximum Limit!");

		//Queying the Matrix
		for (U32 CurrentRow = StartingRow; CurrentRow <= EndingRow; ++CurrentRow)
		{
			for (U32 CurrentCol = StartingCol; CurrentCol <= EndingCol; ++CurrentCol)
			{
				U32 RBIndex = m_Matrix[CurrentRow][CurrentCol];
				if (RBIndex != m_DefaultNoBodyValue)
				{
					//A Static Body Might Be Colliding with the Given Rigid Body!
					pList->GetContact(NumOfPotentialContactsFound).RigidBodies[0] = pRB;
					pList->GetContact(NumOfPotentialContactsFound).RigidBodies[1] = p_GridBodyList->GetFromIndex(RBIndex);
					++NumOfPotentialContactsFound;
				}
			}
		}
	}

	return NumOfPotentialContactsFound;
}
