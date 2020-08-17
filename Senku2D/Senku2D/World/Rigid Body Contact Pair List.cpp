#include "Rigid Body Contact Pair List.h"

Senku2D::RigidBodyPairList::RigidBodyPairList()	:
	m_CurrentAvailableIndex(0)
{
	//Reserving Memory
	m_List.reserve(MAX_CONTACTS);
}

Senku2D::RigidBodyPairList::~RigidBodyPairList()
{
	//Clearing the List
	m_List.clear();
}

void Senku2D::RigidBodyPairList::CopyFromContactList(ContactList& List)
{
	for (size_t i = m_CurrentAvailableIndex; i < List.GetLimit(); ++i)
	{
		CollisionData* CollData = List.GetContactData(i);
		RigidBody* Bodies[2] = {
			CollData->_Bodies.RigidBodies[0],
			CollData->_Bodies.RigidBodies[1]
		};

		if (Bodies[0] != nullptr && Bodies[1] != nullptr)
		{
			m_List.push_back(RigidBodyPair(Bodies[0], Bodies[1]));
		}
	}
}

const size_t Senku2D::RigidBodyPairList::GetSize() const
{
	return m_List.size();
}

const Senku2D::RigidBodyPair Senku2D::RigidBodyPairList::GetRigidBodyPair(const size_t& Index)
{
	assert(Index < GetSize());

	return m_List[Index];
}
