#include "Ray.h"

Senku2D::Ray::Ray()	:
	PointA(),
	PointB()
{

}

Senku2D::Ray::Ray(const Vector2& StartingPoint, const Vector2& EndingPoint)	:
	PointA(StartingPoint),
	PointB(EndingPoint)
{

}

Senku2D::Ray::Ray(const Real& StartX, const Real& StartY, const Real& EndX, const Real& EndY)	:
	PointA(StartX, StartY),
	PointB(EndX, EndY)
{

}

Senku2D::Ray::~Ray()
{
	PointA.Clear();
	PointB.Clear();
}

const Senku2D::Vector2 Senku2D::Ray::GetDirection() const
{
	return (PointB - PointA);
}

void Senku2D::Ray::operator=(const Ray& Other)
{
	PointA = Other.PointA;
	PointB = Other.PointB;
}
