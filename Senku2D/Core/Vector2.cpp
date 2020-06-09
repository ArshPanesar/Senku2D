#include "Vector2.h"

Senku2D::Vector2::Vector2()	:
	x(0),
	y(0)
{

}

Senku2D::Vector2::Vector2(const Real& _x, const Real& _y)	:
	x(_x),
	y(_y)
{
	
}

void Senku2D::Vector2::Invert()
{
	x = -x;
	y = -y;
}
