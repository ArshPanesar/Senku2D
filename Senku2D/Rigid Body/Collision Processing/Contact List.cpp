#include "Contact List.h"

Senku2D::ContactList::ContactList(const size_t& Limit)	:
	m_Limit(Limit)
{
	//Reserving Memory
	m_InternalList.resize(m_Limit);
}

Senku2D::ContactList::~ContactList()
{
	//Clearing the List
	m_InternalList.clear();
}

Senku2D::CollisionData& Senku2D::ContactList::GetContactData(const size_t& Index)
{
	//Asserting that the Index Be Less than the Limit
	assert(Index < m_Limit);

	return m_InternalList[Index];
}

void Senku2D::ContactList::Clear()
{
	m_InternalList.clear();
	m_InternalList.resize(m_Limit);
}

const size_t Senku2D::ContactList::GetLimit() const
{
	return m_InternalList.size();
}
