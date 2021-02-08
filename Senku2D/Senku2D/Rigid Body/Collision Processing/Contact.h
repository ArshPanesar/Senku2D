#pragma once
#include "Potential Contact.h"

namespace Senku2D
{
	//A Struct for Holding Contact Data
	struct Contact
	{
		//Contact Normal
		Vector2 ContactNormal;

		//Amount of Penetration
		Real Penetration = 0.0f;
	};
}

