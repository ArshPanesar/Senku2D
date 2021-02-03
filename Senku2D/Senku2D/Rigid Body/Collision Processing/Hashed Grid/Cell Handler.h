#pragma once
#include "Cell Data.h"

namespace Senku2D
{
	namespace HashedGrid
	{
		//Cell Handler
		/*
		** A Class to Handle Cell Operations Such as Adding a Body to a Cell,
		** Clearing a Cell's Data, Allocating/Deallocating Memory for Cell Data etc.
		*/
		class CellHandler
		{
		private:
			//Reserve Size for Number of Bodies in a Cell
			const size_t m_NumOfBodies;

		public:
			const size_t EmptyBitFlag;
			const size_t CheckedBitFlag;

		public:
			//Constructor
			CellHandler(CellData& CD);
			//Destructor
			~CellHandler();

			//Adding Data to a Cell
			void AddData(CellData& CD, RigidBody* pRB, const size_t& Index);

			//Querying a Rigid Body From a Cell
			unsigned int QueryRigidBody(CellData& CD, RigidBody* pRB, const size_t& Index,
				PotentialContactList* pList, const unsigned int& RegisteredNumOfContacts = 0);
			
			//Querying Through Size (Index + 1)
			unsigned int QueryWithSize(CellData& CD, const size_t& Size, 
				PotentialContactList* pList, const unsigned int& RegisteredNumOfContacts = 0);

			//Clearing a Cell
			void ClearData(CellData& CD, const size_t& Size);
		};
	}
}
