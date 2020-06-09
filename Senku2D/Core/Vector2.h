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
		Real Magnitude() const;

		//Squared Magintude of the Vector
		Real SquaredMagnitude() const;

		//Normalizing a Vector
		void Normalize();

		//Adding a Scaled Vector
		void AddScaledVector(const Vector2& Vec, const Real& Scale);

		//Component Product
		Vector2 GetComponentProduct(const Vector2& Vec);
		void UpdateComponentProduct(const Vector2& Vec);

		//Dot Product
		Real DotProduct(const Vector2& Vec) const;

		//Cross Product(Since You Cant Do a Cross Product in 2D Space, This Simply Returns the Would be Z Component)
		Real CrossProduct(const Vector2& Vec) const;

		//Operator Overloading
		//*= Operator
		void operator*=(const Real& Value);

		//* Operator
		//With Scalar Value
		Vector2 operator*(const Real& Value);
		//With Another Vector(Dot Product)
		Real operator*(const Vector2& Vec);

		//+= Operator
		void operator+=(const Vector2& Vec);

		//+ Operator
		Vector2 operator+(const Vector2& Vec);

		//-= Operator
		void operator-=(const Vector2& Vec);

		//- Operator
		Vector2 operator-(const Vector2& Vec);
	};
}
