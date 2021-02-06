#include "Cell Data.h"

size_t Senku2D::HashedGrid::CellPositionHasher::operator()(const CellPosition& Position) const
{
	int x = Position.x;
	int y = Position.y;

	size_t a = (x < 0) ? ((-2 * x) - 1) : (2 * x);
	size_t b = (y < 0) ? ((-2 * y) - 1) : (2 * y);

	size_t n = a * 0x60019 + b * 0xC0001;

	n ^= n >> 15;
	n *= 0x2c1b3c6d;
	n ^= n >> 12;
	n *= 0x297a2d39;
	n ^= n >> 15;

	return n;
}

bool Senku2D::HashedGrid::CellPosition::operator==(const CellPosition& Other) const
{
	if (Other.x == x && Other.y == y)
	{
		return true;
	}

	return false;
}

bool Senku2D::HashedGrid::CellPosition::operator!=(const CellPosition& Other) const
{
	if (!(*this == Other))
	{
		return true;
	}

	return false;
}
