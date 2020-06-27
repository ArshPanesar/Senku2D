#pragma once
#include "Potential Contact.h"

namespace Senku2D
{
	//Fixed Limit of Potential Contacts That Can be Generated
	const uint8_t POTENTIAL_CONTACT_LIST_LIMIT = 2;

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
		PotentialContactList();
		//Destructor
		~PotentialContactList();

		//Getting A Specific Contact By A Given Index From the List
		PotentialRigidBodyContact* GetContact(const uint8_t Index);

		//Getting Size
		const uint8_t GetLimit() const;
	};
}
