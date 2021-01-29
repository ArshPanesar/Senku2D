#pragma once
#include "Potential Contact.h"

namespace Senku2D
{
	//A Struct for Holding Contact Data
	struct Contact
	{
		//Contact Point in World Coordinates
		Vector2 ContactPoint;

		//Contact Normal
		Vector2 ContactNormal;

		//Amount of Penetration
		Real Penetration = 0.0f;
	};
}

