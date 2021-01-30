#pragma once
#include "../Rigid Body/Collision Processing/Contact List.h"

namespace Senku2D
{
	//A Pair of Rigid Bodies
	typedef std::pair<RigidBody*, RigidBody*> RigidBodyPair;

	//A Rigid Body List For those in Contact
	/*
	** Can be Used For Doing Special Effects In-Game For a
	** Particular Collision!
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
		/*
		This Function is Only Used by the the Update Function in World Class and
		Should not be Used Anywhere Else in Any Game Code!
		*/
		void CopyFromContactList(ContactList& List);

		//Clearing the List
		void Clear();

		//Getting Size
		const size_t GetSize() const;
		//Getting A Rigid Body Pair At An Index
		const RigidBodyPair GetRigidBodyPair(const size_t& Index);
	};
}
