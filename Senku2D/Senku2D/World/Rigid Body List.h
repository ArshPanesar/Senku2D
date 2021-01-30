#pragma once
#include "../Rigid Body/Rigid Body.h"

namespace Senku2D
{
	//A Global Rigid Body List to be used by the Physics World
	/*
	** This Class Acts as the List of All Non-Destroyed Rigid Bodies
	** The List is only of Pointers to Rigid Bodies! When a Rigid Body's Constructor
	** is Called its Pointer Gets Added to the List. When its Destructor is Called(Or
	** if it is Destroyed Manually Due to Say Game Logic), its Pointer Gets Removed 
	** from the List, while Calling the Destructor Does Nothing!
	*/
	class RigidBodyList
	{
	private:
		//Internal List of Pointers to the Rigid Bodies
		std::vector<RigidBody*> m_StaticBodyList;
		std::vector<RigidBody*> m_DynamicBodyList;
		//Maximum Rigid Bodies Allowed
		const uint16_t m_MaxBodiesAllowed;

	public:
		//Constructor
		RigidBodyList();
		//Destructor
		~RigidBodyList();

		//Adding a Body to the List
		void Add(RigidBody* pRB);
		//Removing a Body from the List
		void Remove(RigidBody* pRB);
		//Clearing the List
		void Clear();

		//Getting the Current Size of the List
		const size_t GetStaticBodyListSize() const;
		const size_t GetDynamicBodyListSize() const;
		//Getting the Rigid Body Pointer
		RigidBody* GetRigidBodyFromStaticList(const size_t& Index);
		RigidBody* GetRigidBodyFromDynamicList(const size_t& Index);
	};
}

