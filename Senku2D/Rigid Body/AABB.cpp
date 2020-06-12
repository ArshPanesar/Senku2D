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

Senku2D::AABB::~AABB()
{
	Position.Clear();
	Size.Clear();
}
