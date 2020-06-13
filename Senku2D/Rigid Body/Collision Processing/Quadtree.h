#pragma once
#include "Potential Contact.h"

namespace Senku2D
{
	//A Quadtree Data Structure for Broad Phase Collision Detection
	/*
	This Quadtree Holds Direct Pointers to Rigid Bodies. The Maximum Amount of
	Rigid Bodies a Quad Can Hold Before it Splits is By Default = 4.
	*/
	class Quadtree
	{
	private:
		//AABB For the Quad Itself
		AABB m_Rect;

		//Position of This Quad
		Vector2 m_Position;
		//Size of This Quad
		Vector2 m_Size;

		//Maximum Amount of Rigid Bodies Allowed
		const int m_MaxBodiesAllowed = 4;
		//Current Amount of Bodies Placed
		int m_CurrentAmountOfBodies;

		//Array of Pointers to the Rigid Bodies Stored in this Quad
		RigidBody* m_RigidBodyList[4];
		
		//Child Quads
		std::unique_ptr<Quadtree> m_ChildQuads[4];
	public:
		//Constructor
		Quadtree(const Vector2& Position, const Vector2& Size);

		//Subdividing the Quadtree
		void Subdivide();

		//Insert a Rigid Body in the Quadtree
		void Insert(RigidBody* _RigidBody);

		//Clearing the Quadtree
		void Clear();
	};
}
