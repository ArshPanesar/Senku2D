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

		//Getting Inverse of a 2x2 Matrix
		static Matrix2 GetInverse(const Matrix2& Mat2);

		//Getting Transpose of a 2x2 Matrix
		static Matrix2 GetTranspose(const Matrix2& Mat2);

		//Set This Matrix to its Inverse
		void Invert();

		//Transpose This Matrix
		void Transpose();

		//Getting the Determinant of This Matrix
		static Real GetDeterminant(const Matrix2& Mat2);

		//Getting the Determinant of This Matrix
		Real Determinant() const;

		//Operator Overloads
		//= For Assigning
		void operator=(const Matrix2& Mat2);

		//* For Multiplying with a Vector
		Vector2 operator*(const Vector2& Vec) const;

		//* For Multiplying with another 2x2 Matrix
		Matrix2 operator*(const Matrix2& Mat2) const;

		//* For Multiplying By a Constant
		Matrix2 operator*(const Real& Num) const;

		//*= For Multiplying By a Constant
		void operator*=(const Real& Num);
	};

}
