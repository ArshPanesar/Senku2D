#pragma once
#include "Vector2.h"

namespace Senku2D
{
	//A 3x3 Matrix
	/*
	This will be Useful for Displaying Rotations and Position
	Aka A Transform Matrix!
	*/
	class Matrix3
	{
	public:
		//A 9 Element Array of Real Type Data
		Real Data[9];

		//Default Constructor
		Matrix3();

		//Copy Constructor
		Matrix3(const Matrix3& Other);

		//Operator Overloading
		//* Multiplying with Another 3x3 Matrix
		Matrix3 operator*(const Matrix3& Mat3);

		//= Operator for Assigning To Another Matrix
		void operator=(const Matrix3& Mat3);
	};

}