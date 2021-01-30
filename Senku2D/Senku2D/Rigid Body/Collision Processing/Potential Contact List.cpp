#include "Potential Contact List.h"

Senku2D::PotentialContactList::PotentialContactList(const size_t& Limit) :
	m_Limit(Limit),
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

Senku2D::PotentialRigidBodyContact& Senku2D::PotentialContactList::GetContact(const size_t& Index)
{
	//Index Should Not Exceed Limit
	assert(Index < m_Limit);
	return m_InternalList[Index];
}

void Senku2D::PotentialContactList::Clear()
{
	for (auto& itr : m_InternalList)
	{
		itr.RigidBodies[0] = nullptr;
		itr.RigidBodies[1] = nullptr;
	}
}

const size_t Senku2D::PotentialContactList::GetLimit() const
{
	return m_Limit;
}
