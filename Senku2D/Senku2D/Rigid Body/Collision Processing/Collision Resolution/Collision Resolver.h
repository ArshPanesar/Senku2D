#pragma once
#include "../Contact List.h"

namespace Senku2D
{
	//This Serves as a Service Class to Resolve Collisions From a Contact List
	class CollisionResolver
	{
	private:
		//Resolve Penetration
		void ResolvePenetration(ContactList* pContactList);
		
		//Resolve Velocity
		void ResolveVelocity(ContactList* pContactList, const Real& Timestep);
		//Calculating Separating Velocity
		Real CalculateSeparatingVelocity(CollisionData* CD);

		//Coefficient of Restitution
		Real Restitution;

	public:
		//Constructor
		CollisionResolver();
		//Destructor
		~CollisionResolver();
		
		//Resolve Collisions
		void Resolve(ContactList* pContactList, const Real& Timestep);
	};
}
