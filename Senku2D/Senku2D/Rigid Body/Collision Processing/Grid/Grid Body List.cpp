#include "Grid Body List.h"

using namespace Senku2D;

Senku2D::GridBodyList::GridBodyList(const U32& NumOfBodies) :
	m_MaxNumberOfBodies(NumOfBodies)
{
	//Resizing the List
	m_List.resize(m_MaxNumberOfBodies);

	//Filling the List with Null Values
	for (auto& itr : m_List)
	{
		itr = nullptr;
	}
}

Senku2D::GridBodyList::~GridBodyList()
{
	//Clearing the List
	m_List.clear();
}

void Senku2D::GridBodyList::AddAtIndex(const U32& Index, RigidBody* pRB)
{
	assert(Index >= m_MaxNumberOfBodies);
	m_List[Index] = pRB;
}

RigidBody* Senku2D::GridBodyList::GetFromIndex(const U32& Index)
{
	assert(Index >= m_MaxNumberOfBodies);
	return m_List[Index];
}
