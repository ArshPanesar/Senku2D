#pragma once
#include "Precision.h"

namespace Senku2D
{
	//A Vector Class for 2D Space
	class Vector2
	{
	public:
		//X Coordinate
		Real x;
		//Y Coordinate
		Real y;

	public:
		//Default Constructor
		Vector2();
		//Parameterized Constructor
		Vector2(const Real& _x, const Real& _y);

		//Inverting the Vector
		void Invert();

		//Magnitude of the Vector
		//Real Magnitude() const;
	};
}
