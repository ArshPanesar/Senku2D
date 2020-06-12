#pragma once
#include "../Core/Vector2.h"

namespace Senku2D
{
	//AABB Struct Used for Primitive Collision Tests
	//This AABB Will be Used For All Rigid Bodies
	struct AABB
	{
		//A Top-Left Position
		Vector2 Position;
		//Size - Width and Height
		Vector2 Size;

		//Default Constructor
		AABB();

		//Parameterized AABB Constructor
		AABB(const Vector2& _Position, const Vector2& _Size);

		//Copy Constructor
		AABB(const AABB& Other);

		//Does This AABB Overlap Another AABB?
		bool Overlaps(const AABB& Other);

		//Copy Assignment Operator
		void operator=(const AABB& Other);

		//Checking == Operator
		bool operator==(const AABB& Other) const;

		//Checking != Operator
		bool operator!=(const AABB& Other) const;

		//Destructor
		~AABB();
	};
}
