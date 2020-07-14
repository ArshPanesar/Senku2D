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

	public:
		//Constructor
		CollisionResolver();
		//Destructor
		~CollisionResolver();
		
		//Resolve Collisions
		void Resolve(ContactList* pContactList);
	};
}
