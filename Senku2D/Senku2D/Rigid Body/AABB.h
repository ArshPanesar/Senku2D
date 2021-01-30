#pragma once
#include "../Core/Vector2.h"
#include "Shapes/Box Shape.h"
#include "Shapes/Circle Shape.h"

namespace Senku2D
{
	//AABB Struct 
	/*
	** Used for Primitive Collision Tests by the Engine and
	** Can Also be Used For Creating Boundaries and All Other Uses.
	*/
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

		//Calculating AABB For Different Shapes and Orientations
		static AABB CalculateForShape(const Shape* Shape);
		
		//Clearing the AABB
		void Clear();

		//Destructor
		~AABB();
	};
}
