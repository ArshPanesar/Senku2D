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

Senku2D::CollisionData* Senku2D::ContactList::GetContactData(const size_t& Index)
{
	//Asserting that the Index Be Less than the Limit
	assert(Index < m_Limit);
	return &m_InternalList[Index];
}

void Senku2D::ContactList::Clear()
{
	for (auto& itr : m_InternalList)
	{
		itr._Bodies.RigidBodies[0] = nullptr;
		itr._Bodies.RigidBodies[1] = nullptr;

		itr._Contact.ContactNormal = Vector2();
		itr._Contact.ContactPoint = Vector2();
		itr._Contact.Penetration = 0.0f;
	}
}

const size_t Senku2D::ContactList::GetLimit() const
{
	return m_Limit;
}
