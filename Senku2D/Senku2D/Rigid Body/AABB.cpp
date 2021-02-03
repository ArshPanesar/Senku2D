#include "AABB.h"

Senku2D::AABB::AABB()	:
	Position(0, 0),
	Size(0, 0)
{

}

Senku2D::AABB::AABB(const Vector2& _Position, const Vector2& _Size)	:
	Position(_Position),
	Size(_Size)
{

}

Senku2D::AABB::AABB(const AABB& Other)
{
	Position = Other.Position;
	Size = Other.Size;
}

bool Senku2D::AABB::Overlaps(const AABB& Other)
{
	if (Position.x < (Other.Position.x + Other.Size.x)
		&& (Position.x + Size.x) > Other.Position.x
		&& Position.y < (Other.Position.y + Other.Size.y)
		&& (Position.y + Size.y) > Other.Position.y)
	{
		return true;
	}

	return false;
}

void Senku2D::AABB::operator=(const AABB& Other)
{
	Position = Other.Position;
	Size = Other.Size;
}

bool Senku2D::AABB::operator==(const AABB& Other) const
{
	if (Position == Other.Position && Size == Other.Size)
	{
		return true;
	}

	return false;
}

bool Senku2D::AABB::operator!=(const AABB& Other) const
{
	if (!(*this == Other))
	{
		return true;
	}

	return false;
}

Senku2D::AABB Senku2D::AABB::CalculateForShape(const Shape* Shape)
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
		MaxY = MinY;
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

void Senku2D::AABB::Clear()
{
	Position.Clear();
	Size.Clear();
}

Senku2D::AABB::~AABB()
{
	Clear();
}
