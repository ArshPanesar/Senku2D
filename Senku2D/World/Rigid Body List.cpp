#include "Rigid Body List.h"

Senku2D::RigidBodyList::RigidBodyList()	:
	m_MaxBodiesAllowed(100),
	m_InternalList()
{
	//Reserving Memory for the List
	m_InternalList.reserve(m_MaxBodiesAllowed);
}

Senku2D::RigidBodyList::~RigidBodyList()
{
	//Clearing the List
	Clear();
}

Senku2D::RigidBodyList& Senku2D::RigidBodyList::Get()
{
	static RigidBodyList s_Instance;
	return s_Instance;
}

void Senku2D::RigidBodyList::Add(RigidBody* pRB)
{
	m_InternalList.push_back(pRB);
}

void Senku2D::RigidBodyList::Remove(RigidBody* pRB)
{
	auto itr = m_InternalList.begin();
	for (size_t i = 0; i < m_InternalList.size(); ++i)
	{
		//Comparing Addresses
		if (pRB == m_InternalList[i])
		{
			//Erasing from the Vector
			m_InternalList.erase(itr);
			break;
		}

		//Incrementing Iterator Position
		++itr;
	}
}

void Senku2D::RigidBodyList::Clear()
{
	m_InternalList.clear();
}

const size_t Senku2D::RigidBodyList::GetSize() const
{
	return m_InternalList.size();
}

Senku2D::RigidBody* Senku2D::RigidBodyList::GetRigidBody(const size_t& Index)
{
	if (Index >= GetSize())
	{
		return nullptr;
	}

	return m_InternalList[Index];
}
