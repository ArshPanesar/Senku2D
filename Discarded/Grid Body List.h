#pragma once
#include "../../../Rigid Body/Rigid Body.h"

namespace Senku2D
{
	//A Storage Class For All Static Bodies in a Grid
	/*
	This List Class is Used Internally By Every Grid To Keep Track of All
	The Static Type Rigid Bodies Added to the Grid
	*/
	class GridBodyList
	{
	private:
		//Rigid Body Pointer List
		std::vector<RigidBody*> m_List;

		//Number of Bodies
		U32 m_NumOfBodies;
	public:
		//Constructor
		GridBodyList();
		//Parameterized Constructor
		GridBodyList(const U32& NumOfBodies);
		//Destructor
		~GridBodyList();

		//Resetting the List
		void Reset(const U32& NumOfBodies);

		//Clearing the List
		void Clear();

		//Adding a Rigid Body Pointer At an Index
		void AddAtIndex(const U32& Index, RigidBody* pRB);

		//Getting a Rigid Body Pointer From an Index
		RigidBody* GetFromIndex(const U32& Index);
	};
}
