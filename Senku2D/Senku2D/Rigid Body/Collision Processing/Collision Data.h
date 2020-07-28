#pragma once
#include "Contact.h"

namespace Senku2D
{
	/*
	A Structure for Holding the Collision Data for a Pair of Rigid Bodies
	And Their Contact Information
	*/
	struct CollisionData
	{
		//Contact Info
		Contact _Contact;

		//Potential Contact Between Two Rigid Bodies
		PotentialRigidBodyContact _Bodies;
	};
}
