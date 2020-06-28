#pragma once
#include "Potential Contact.h"
#include <assert.h>

namespace Senku2D
{
	
	//A List of Potential Contacts of a Fixed Size(Limit)
	class PotentialContactList
	{
	private:
		//Fixed Size
		const uint8_t m_Limit;

		//Internal Array
		std::vector<PotentialRigidBodyContact> m_InternalList;

	public:
		//Constructor
		PotentialContactList(const uint8_t& Limit);
		//Destructor
		~PotentialContactList();

		//Getting A Specific Contact By A Given Index From the List
		PotentialRigidBodyContact& GetContact(const uint8_t& Index);

		//Clearing the List
		void Clear();

		//Getting Size
		const uint8_t GetLimit() const;
	};
}
