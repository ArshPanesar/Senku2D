#pragma once
#include "Shape Solver.h"
#include "../Potential Contact List.h"

namespace Senku2D
{
	//A Narrow Phase Collision Detection Service Class
	class NarrowPhase
	{
	public:
		//Primitive AABB Test: Generates a New List of Possible Collisions
		//And Returns the Number of New Potential Contacts Generated
		unsigned int GeneratePrimitiveTestResultsList(PotentialContactList* OldContacts, PotentialContactList* NewContacts);

		//Shape Test: Generates a List of Actual Collisions Taking Place
		//And Returns the Number of Actual Collisions

	};
}
