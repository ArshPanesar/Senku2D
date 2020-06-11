#pragma once
#include "Vector2.h"

namespace Senku2D
{
	//A 2x2 Matrix
	/*
	This will be Useful for Displaying Rotations,
	Can Also be Used for Inertia Tensors for 2D
	*/
	class Matrix2
	{
	public:
		//A 4 Element Array of Real Type Data
		Real Data[4];

		//Default Constructor
		Matrix2();

		//Copy Constructor
		Matrix2(const Matrix2& Other);

		//Operator Overloads
		//= For Assigning
		void operator=(const Matrix2& Mat2);

		//* For Multiplying with a Vector
		Vector2 operator*(const Vector2& Vec) const;

		//* For Multiplying with another 2x2 Matrix
		Matrix2 operator*(const Matrix2& Mat2) const;
	};

}
