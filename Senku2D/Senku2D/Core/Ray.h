#pragma once
#include "Vector2.h"

namespace Senku2D
{
	//A Ray Class
	/*
	** A Ray is a Line that has a Starting Point and an Ending Point.
	** Rays can be used for World Querying.
	*/
	class Ray
	{
	public:
		//Starting Point
		Vector2 PointA;
		//Ending Point
		Vector2 PointB;

	public:
		//Default Constructor
		Ray();
		//Parameterized Contructors
		Ray(const Vector2& StartingPoint, const Vector2& EndingPoint);
		Ray(const Real& StartX, const Real& StartY, const Real& EndX, const Real& EndY);

		//Destructor
		~Ray();

		//Getting Direction of Line
		const Vector2 GetDirection() const;

		//Operator Overloading
		//Operator=
		void operator=(const Ray& Other);
	};
}

