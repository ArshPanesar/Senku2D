#include "Rigid Body List.h"

using namespace Senku2D;

Senku2D::RigidBodyList::RigidBodyList() :
	m_MaxBodiesAllowed(96),
	m_StaticBodyList(),
	m_DynamicBodyList()
{
	//Reserving Memory for the List
	m_StaticBodyList.reserve(m_MaxBodiesAllowed);
	m_DynamicBodyList.reserve(m_MaxBodiesAllowed);
}

Senku2D::RigidBodyList::~RigidBodyList()
{
	//Clearing the List
	Clear();
}


void Senku2D::RigidBodyList::Add(RigidBody* pRB)
{
	switch (pRB->GetBodyType())
	{
	case BodyType::STATIC:

		m_StaticBodyList.push_back(pRB);
		break;
	case BodyType::DYNAMIC:

		m_DynamicBodyList.push_back(pRB);
		break;
	}
}

void Senku2D::RigidBodyList::Remove(RigidBody* pRB)
{
	if (pRB->GetBodyType() == BodyType::STATIC)
	{
		auto itr = std::find(m_StaticBodyList.begin(), m_StaticBodyList.end(), pRB);
		m_StaticBodyList.erase(itr);
	}
	else if(pRB->GetBodyType() ==  BodyType::DYNAMIC)
	{
		auto itr = std::find(m_DynamicBodyList.begin(), m_DynamicBodyList.end(), pRB);
		m_DynamicBodyList.erase(itr);
	}
}

void Senku2D::RigidBodyList::Clear()
{
	m_StaticBodyList.clear();
	m_DynamicBodyList.clear();
}

const size_t Senku2D::RigidBodyList::GetStaticBodyListSize() const
{
	return m_StaticBodyList.size();
}

const size_t Senku2D::RigidBodyList::GetDynamicBodyListSize() const
{
	return m_DynamicBodyList.size();
}

RigidBody* Senku2D::RigidBodyList::GetRigidBodyFromStaticList(const size_t& Index)
{
	assert(Index >= GetStaticBodyListSize());

	return m_StaticBodyList[Index];
}

RigidBody* Senku2D::RigidBodyList::GetRigidBodyFromDynamicList(const size_t& Index)
{
	assert(Index >= GetDynamicBodyListSize());

	return m_DynamicBodyList[Index];
}
