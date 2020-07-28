#pragma once
#include "../Rigid Body.h"

namespace Senku2D
{
	/*
	A Structure for Holding Pointers to Two Rigid Bodies
	That Might Potentially be in Contact
	*/
	struct PotentialRigidBodyContact
	{
		//Pointers to Two Rigid Bodies That Might be in Contact
		RigidBody* RigidBodies[2];
	};

}

