#pragma once
#include "../Rigid Body.h"

namespace Senku2D
{
	//A Quadtree for Collision Processing
	class Quadtree
	{
	private:
		//This Quadtree's Own Bounds
		AABB m_Bounds;

		//Total Number of Rigid Bodies Allowed in a Quad
		static const int MAX_RIGID_BODIES_ALLOWED = 4;
		//Number of Current Rigid Bodies in this Quad
		int m_CurrentNumOfBodies;

		//Rigid Body Array
		RigidBody* m_Bodies[MAX_RIGID_BODIES_ALLOWED];

		//Children Quads
		Quadtree* m_ChildrenQuads[4];
	public:
		//Default Constructor
		Quadtree();

		//Destructor
		~Quadtree();
	};
}
