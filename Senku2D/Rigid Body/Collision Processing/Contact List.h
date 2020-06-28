#pragma once
#include "Collision Data.h"
#include <assert.h>

namespace Senku2D
{
	
	//A Rigid Body Contact List With a Fixed Limit
	class ContactList
	{
	private:
		//Fixed Limit for the List
		const size_t m_Limit;

		//Internal List
		std::vector<CollisionData> m_InternalList;
	public:
		//Constructor
		ContactList(const size_t& Limit);
		//Destructor
		~ContactList();

		//Accessing a Contact
		CollisionData& GetContactData(const size_t& Index);

		//Clearing the List
		void Clear();
		
		//Getting Size
		const size_t GetLimit() const;
	};
}
