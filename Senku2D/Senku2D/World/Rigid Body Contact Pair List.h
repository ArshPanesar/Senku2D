#pragma once
#include "../Rigid Body/Collision Processing/Contact List.h"

namespace Senku2D
{
	//A Pair of Rigid Bodies
	typedef std::pair<RigidBody*, RigidBody*> RigidBodyPair;

	//Maximum Amount of Contacts Generated
	const unsigned int MAX_CONTACTS = 12;

	//A Rigid Body List That Are in Contact
	/*
	Only Used For Extra Stuff For a Game
	*/
	class RigidBodyPairList
	{
	private:
		//List of Rigid Body Pairs
		std::vector<RigidBodyPair> m_List;

		//Current Available Index
		U32 m_CurrentAvailableIndex;
	public:
		//Constructor
		RigidBodyPairList();
		//Destructor
		~RigidBodyPairList();

		//Copying Data From a Contact List
		void CopyFromContactList(ContactList& List);

		//Clearing the List
		void Clear();

		//Getting Size
		const size_t GetSize() const;
		//Getting A Rigid Body Pair At Some Index
		const RigidBodyPair GetRigidBodyPair(const size_t& Index);
	};
}
