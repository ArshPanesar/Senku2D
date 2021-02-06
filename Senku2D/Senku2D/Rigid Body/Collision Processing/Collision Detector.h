#pragma once
#include "Collision Data.h"
//Shapes
#include "../Shapes/Box Shape.h"
#include "../Shapes/Circle Shape.h"
//Ray
#include "../../Core/Ray.h"

namespace Senku2D
{
	//A Collision Detector Class
	/*
	This Collision Detector Class Provides Services to Figure Out Collisions
	Between Rigid Bodies. All Functions Are Static So There is No Need to Instantiate
	This Class.

	WARNING: The Collision Detector Class Assumes that The Shape Tests Called are
	For the Correct Shapes! This Class Will NOT Check the Rigid Bodies' Shape.
	*/
	class CollisionDetector
	{
	public:
		//Collision Detection Algorithms
		//Circle and Circle
		static bool CircleAndCircle(PotentialRigidBodyContact* Contact, CollisionData* CollData);
		//Box and Box
		static bool BoxAndBox(PotentialRigidBodyContact* Contact, CollisionData* CollData);
		//Box and Circle
		static bool BoxAndCircle(PotentialRigidBodyContact* Contact, CollisionData* CollData);

		//Ray Intersection Tests
		static bool ShapeAndRayIntersectionTest(Shape* p_Shape, Ray* p_Ray, const Real& Angle);
		static bool CircleAndPoint(CircleShape* p_Circle, Vector2* p_Point);
		static bool CircleAndRay(CircleShape* p_Circle, Ray* p_Ray);
		static bool BoxAndPoint(BoxShape* p_Box, Vector2* p_Point, const Real& BoxAngle);
		static bool BoxAndRay(BoxShape* p_Box, Ray* p_Ray, const Real& BoxAngle);
	};

	//SAT Collision Test Helpers
	struct SAT
	{
		struct Projection
		{
			Real min, max;

			bool overlaps(Projection& interval)
			{
				return !(this->min > interval.max || interval.min > this->max);
			}

			Real getOverlap(Projection& interval) {
				// make sure they overlap
				if (this->overlaps(interval))
				{
					return((Real_Min(this->max, interval.max)) - (Real_Max(this->min, interval.min)));
				}
				return 0;
			}
		};

		static Projection project(const Vector2& norm_axis, const Vector2* vertices, Vector2& CP)
		{
			Real min = norm_axis.DotProduct(vertices[0]);
			CP = vertices[0];
			Real max = min;

			for (int i = 1; i < 4; i++) {
				// NOTE: the axis must be normalized to get accurate projections
				Real p = norm_axis.DotProduct(vertices[i]);
				if (p < min)
				{
					min = p;
					CP = vertices[i];
				}
				else if (p > max)
				{
					max = p;
					CP = vertices[i];
				}
			}

			Projection proj;
			proj.min = min;
			proj.max = max;

			return proj;
		};
	};
}

