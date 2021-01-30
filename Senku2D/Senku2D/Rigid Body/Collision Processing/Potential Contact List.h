#pragma once
#include "Potential Contact.h"

namespace Senku2D
{
	
	//A List of Potential Contacts of a Fixed Size(Limit)
	class PotentialContactList
	{
	private:
		//Fixed Capacity
		const size_t m_Limit;
		
		//Internal Array
		std::vector<PotentialRigidBodyContact> m_InternalList;

	public:
		//Constructor
		PotentialContactList(const size_t& Limit);
		//Destructor
		~PotentialContactList();

		//Getting A Specific Contact By A Given Index From the List
		PotentialRigidBodyContact& GetContact(const size_t& Index);

		//Clearing the List
		void Clear();

		//Getting Limit
		const size_t GetLimit() const;
	};
}
