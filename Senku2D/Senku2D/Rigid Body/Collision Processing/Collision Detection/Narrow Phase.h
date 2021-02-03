#pragma once
#include "Shape Solver.h"
#include "../Potential Contact List.h"
#include "../Contact List.h"
#include "../Collision Detector.h"

namespace Senku2D
{
	//A Narrow Phase Collision Detection Service Class
	class NarrowPhase
	{
	private:
		static bool CheckCollision(const ShapePairs& CurrentShapePair, 
			PotentialRigidBodyContact& rPRBC, CollisionData* pCollData);

	public:
		//Primitive AABB Test: Generates a New List of Possible Collisions
		//And Returns the Number of New Potential Contacts Generated
		static unsigned int GeneratePrimitiveTestResultsList(
			PotentialContactList* OldContacts, PotentialContactList* NewContacts,
			const uint32_t& NumOfPotentialContacts);

		//Shape Test: Generates a List of Actual Collisions Taking Place
		//And Returns the Number of Actual Collisions
		static unsigned int GenerateShapeTestResultsList(
			PotentialContactList* PotentialContacts, ContactList* CList, 
			const uint32_t& NumOfPotentialContacts);
	};
}
