#pragma once
#include "Cell Handler.h"
#include "../../../Core/Ray.h"

namespace Senku2D
{
	namespace HashedGrid
	{
		//Default Cell Size (In Pixels)
		const Real DEFAULT_CELL_WIDTH = 128.0f;
		const Real DEFAULT_CELL_HEIGHT = 128.0f;

		//Spatially Hashed Infinite Grid
		class Grid
		{
		private:
			//Unordered Map
			std::unordered_map<CellPosition, size_t, CellPositionHasher> m_Map;
			
			//Cell Data Storage
			CellData m_CellData;

			//Cell Handler
			CellHandler m_CellHandler;

			//Cell Size
			Vector2 m_CellSize;

			//Cell Index
			size_t m_CellIndex;

		public:
			//Default Constructor
			Grid();
			
			//Destructor
			~Grid();

			//Setting Cell Size
			void SetCellSize(const Real& CellWidth, const Real& CellHeight);

			//Inserting a Body
			void Insert(RigidBody* pRB);

			//Querying A Rigid Body
			/*
			** Only Looks for Potential Contacts Against the Rigid Body Provided and
			** Thus Flags Remain Unchanged.
			** RegisteredNumOfContacts - Number of Contacts Already Registered in the List.
			** This Will Be Used When Querying Multiple Cells For a Body To Avoid Losing
			** Previously Stored Potential Contacts.
			*/
			unsigned int QueryRigidBody(RigidBody* pRB, PotentialContactList* pList,
				const unsigned int& RegisteredNumOfContacts = 0);
			
			//Querying Through Index
			/*
			** This Will Check All Non-Empty Cells For Any Collisions and Fill the Contact List
			*/
			unsigned int QueryActiveCells(PotentialContactList* pList, const unsigned int& RegisteredNumOfContacts = 0);

			//Querying For Ray
			unsigned int QueryRay(const Ray& QueryRay, std::vector<RigidBody*>& RBList);

			//Querying For AABB
			unsigned int QueryAABB(AABB& Box, std::vector<RigidBody*>& RBList);

			//Clearing the Grid
			void Clear();
		};
	}
}
