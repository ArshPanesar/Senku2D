#include "Potential Contact List.h"

Senku2D::PotentialContactList::PotentialContactList()	:
	m_Limit(POTENTIAL_CONTACT_LIST_LIMIT),
	m_InternalList()
{
	//Resize the List to the Given Limit
	m_InternalList.resize(m_Limit);
}

Senku2D::PotentialContactList::~PotentialContactList()
{
	//Clear the List
	m_InternalList.clear();
}

Senku2D::PotentialRigidBodyContact* Senku2D::PotentialContactList::GetContact(const uint8_t Index)
{
	//Index Should Not Exceed Limit
	if (Index < m_Limit)
	{
		return &m_InternalList[Index];
	}

	return nullptr;
}

void Senku2D::PotentialContactList::Clear()
{
	m_InternalList.clear();
	m_InternalList.resize(m_Limit);
}

const uint8_t Senku2D::PotentialContactList::GetLimit() const
{
	return m_Limit;
}
