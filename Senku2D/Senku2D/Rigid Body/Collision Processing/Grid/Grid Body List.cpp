#include "Grid Body List.h"

using namespace Senku2D;

Senku2D::GridBodyList::GridBodyList()	:
	m_List(),
	m_MaxNumberOfBodies(0)
{

}

Senku2D::GridBodyList::GridBodyList(const U32& NumOfBodies) :
	m_MaxNumberOfBodies(NumOfBodies)
{
	//Resizing the List
	Reset(NumOfBodies);

	//Filling the List with Null Values
	for (auto& itr : m_List)
	{
		itr = nullptr;
	}
}

Senku2D::GridBodyList::~GridBodyList()
{
	//Clearing the List
	Clear();
}

void Senku2D::GridBodyList::Reset(const U32& NumOfBodies)
{
	Clear();
	m_List.resize(NumOfBodies);
}

void Senku2D::GridBodyList::Clear()
{
	m_List.clear();
}

void Senku2D::GridBodyList::AddAtIndex(const U32& Index, RigidBody* pRB)
{
	assert(Index < m_MaxNumberOfBodies);
	m_List[Index] = pRB;
}

RigidBody* Senku2D::GridBodyList::GetFromIndex(const U32& Index)
{
	assert(Index < m_MaxNumberOfBodies);
	return m_List[Index];
}
