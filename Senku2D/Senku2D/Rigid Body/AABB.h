#pragma once
#include "../Core/Vector2.h"
#include "Shapes/Box Shape.h"
#include "Shapes/Circle Shape.h"

namespace Senku2D
{
	//AABB Struct Used for Primitive Collision Tests
	//This AABB Will be Used For All Rigid Bodies
	struct AABB
	{
		//A Top-Left Position
		Vector2 Position;
		//Size - Width and Height
		Vector2 Size;

		//Default Constructor
		AABB();

		//Parameterized AABB Constructor
		AABB(const Vector2& _Position, const Vector2& _Size);

		//Copy Constructor
		AABB(const AABB& Other);

		//Does This AABB Overlap Another AABB?
		bool Overlaps(const AABB& Other);

		//Copy Assignment Operator
		void operator=(const AABB& Other);

		//Checking == Operator
		bool operator==(const AABB& Other) const;

		//Checking != Operator
		bool operator!=(const AABB& Other) const;

		//Calculating AABB For Different Shapes and Orientations
		static inline AABB CalculateForShape(const Shape* Shape)
		{
			AABB Bounds;

			switch (Shape->GetShapeType())
			{
			case ShapeType::BOX:
			{
				//Getting Necessary Variables
				const BoxShape& Box = *(BoxShape*)Shape;
				
				/*
				Get All Vertices and Find the Min X Coord, Max X Coord,
				Min Y Coord and Max Y Coord.
				Your AABB will be:
				Position(MinX, MinY) & Size(MaxX - MinX, MaxY - MinY)
				*/
				Real MinX, MinY, MaxX, MaxY;

				//Finding Minimums and Maximums
				MinX = Box.GetVertex(0).x;
				MinY = Box.GetVertex(0).y;
				MaxX = MinX;
				MaxY = MaxX;
				for (unsigned int i = 1; i < 4; ++i)
				{
					MinX = Real_Min(MinX, Box.GetVertex(i).x);
					MinY = Real_Min(MinY, Box.GetVertex(i).y);
					MaxX = Real_Max(MaxX, Box.GetVertex(i).x);
					MaxY = Real_Max(MaxY, Box.GetVertex(i).y);
				}

				//Filling the AABB
				Bounds.Position = Vector2(MinX, MinY);
				Bounds.Size = Vector2(MaxX - MinX, MaxY - MinY);
			}
				break;

			case ShapeType::CIRCLE:

				Bounds.Position = Vector2(Shape->GetCenterPosition()) - (Vector2(Shape->GetBoundSize()) / (Real)2);
				Bounds.Size = Shape->GetBoundSize();
				break;
			}

			return Bounds;
		}

		//Clearing the AABB
		void Clear();

		//Destructor
		~AABB();
	};
}
