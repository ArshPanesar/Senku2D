#pragma once
#include "Potential Contact List.h"

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
		static const int m_MaxBodiesAllowed = 4;
		//Maximum Amount of Levels Allowed
		static const int m_MaxLevels = 4;

		//Current Amount of Bodies Placed
		int m_CurrentAmountOfBodies;
		//Current Level of Node
		int m_CurrentLevel;

		//Array of Pointers to the Rigid Bodies Stored in this Quad
		std::vector<RigidBody*> m_RigidBodyList;
		
		//Child Quads
		Quadtree* m_ChildQuads[4];
	public:
		//Constructor
		Quadtree(const Vector2& Position, const Vector2& Size, const int& Level);

		//Resetting the Quadtree With a New Position and Size
		//Must Only Be Called After Clearing The Entire Quadtree First!
		void Reset(const Vector2& Position, const Vector2& Size);

		//Subdividing the Quadtree
		void Subdivide();

		//Insert a Rigid Body in the Quadtree
		void Insert(RigidBody* _RigidBody);

		//Query the Quadtree and Find the Neighbours of the Passed Down Rigid Body
		//Additionaly Pass Down a Contact List that Can be Filled Upto the Provided Limit
		unsigned int Query(RigidBody* _RigidBody, PotentialContactList* Contacts);

		//Clearing the Quadtree
		void Clear();
	};
}
