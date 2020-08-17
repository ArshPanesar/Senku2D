#pragma once
#include "Grid Body List.h"
#include "../Potential Contact List.h"

namespace Senku2D
{
	//A Grid Class
	/*
	Use This For Creating Grids of Static Bodies for Faster Collision Detection.
	*/
	class Grid
	{
	private:
		//Bounds
		AABB m_Bounds;

		//Tile Size
		Vector2 m_TileSize;

		//Grid Matrix
		std::vector<std::vector<U32>> m_Matrix;
		U32 m_NumOfRows;
		U32 m_NumOfCols;

		//Default No Body Value
		const U32 m_DefaultNoBodyValue;

		//Body List for this Grid
		std::unique_ptr<GridBodyList> p_GridBodyList;

		//Current Index of Rigid Body
		U32 m_RBCurrentIndex;

	public:
		//Constructor
		Grid(const AABB& Bounds, const Vector2& TileSize);
		//Destructor
		~Grid();

		//Adding a Static Body to the Grid
		void AddBody(RigidBody* pRB);

		//Querying the Grid For Collisions with the Given Rigid Body
		U32 Query(RigidBody* pRB, PotentialContactList* pList);
	};
}
