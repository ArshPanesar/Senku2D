#pragma once
#include "Collision Data.h"
//Shapes
#include "../Shapes/Box Shape.h"
#include "../Shapes/Circle Shape.h"

namespace Senku2D
{
	//A Collision Detector Class
	/*
	This Collision Detector Class Provides Services to Figure Out Collisions
	Between Rigid Bodies. All Functions Are Static So There is No Need to Instantiate
	This Class.
	*/
	class CollisionDetector
	{
	public:
		//Collision Detection Algorithms
		//Circle and Circle
		static bool CircleAndCircle(CollisionData* CollData);
		//Box and Box
		static bool BoxAndBox(CollisionData* CollData);
		//Box and Circle
		static bool BoxAndCircle(CollisionData* CollData);
	};
}

