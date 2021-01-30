#pragma once
#include "Collision Data.h"

namespace Senku2D
{
	//Maximum Amount of Contacts Generated
	const size_t DEFAULT_MAX_CONTACTS = 256;

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
		CollisionData* GetContactData(const size_t& Index);

		//Clearing the List
		void Clear();
		
		//Getting Size
		const size_t GetLimit() const;
	};
}
