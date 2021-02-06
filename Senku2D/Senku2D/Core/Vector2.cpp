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

Senku2D::Real Senku2D::Vector2::Magnitude() const
{
	return Real_Sqrt(x * x + y * y);
}

Senku2D::Real Senku2D::Vector2::SquaredMagnitude() const
{
	return(x * x + y * y);
}

void Senku2D::Vector2::Normalize()
{
	Real Mag = Magnitude();

	if (Mag > 0)
	{
		(*this) *= ((Real)1 / Mag);
	}
}

Senku2D::Vector2 Senku2D::Vector2::GetComponentProduct(const Vector2& Vec)
{
	return Vector2(x * Vec.x, y * Vec.y);
}

void Senku2D::Vector2::UpdateComponentProduct(const Vector2& Vec)
{
	x *= Vec.x;
	y *= Vec.y;
}

Senku2D::Real Senku2D::Vector2::DotProduct(const Vector2& Vec) const
{
	return (x * Vec.x + y * Vec.y);
}

Senku2D::Real Senku2D::Vector2::CrossProduct(const Vector2& Vec) const
{
	return (x * Vec.y - y * Vec.x);
}

void Senku2D::Vector2::operator*=(const Real& Value)
{
	x *= Value;
	y *= Value;
}

Senku2D::Vector2 Senku2D::Vector2::operator*(const Real& Value) const
{
	return Vector2(x * Value, y * Value);
}

Senku2D::Real Senku2D::Vector2::operator*(const Vector2& Vec) const
{
	return (x * Vec.x + y * Vec.y);
}

Senku2D::Vector2 Senku2D::Vector2::operator/(const Real& Value) const
{
	Vector2 Vec(*this);
	if (Value != 0)
	{
		Vec.x /= Value;
		Vec.y /= Value;
	}

	return Vec;
}

void Senku2D::Vector2::operator/=(const Real& Value)
{
	*this = *this / Value;
}

void Senku2D::Vector2::operator+=(const Vector2& Vec)
{
	x += Vec.x;
	y += Vec.y;
}

Senku2D::Vector2 Senku2D::Vector2::operator+(const Vector2& Vec) const
{
	return Vector2(x + Vec.x, y + Vec.y);
}

void Senku2D::Vector2::operator-=(const Vector2& Vec)
{
	x -= Vec.x;
	y -= Vec.y;
}

Senku2D::Vector2 Senku2D::Vector2::operator-(const Vector2& Vec) const
{
	return Vector2(x - Vec.x, y - Vec.y);
}

bool Senku2D::Vector2::operator==(const Vector2& Vec) const
{
	if (x == Vec.x && y == Vec.y)
	{
		return true;
	}
	return false;
}

bool Senku2D::Vector2::operator!=(const Vector2& Vec) const
{
	if (!(*this == Vec))
	{
		return true;
	}

	return false;
}

void Senku2D::Vector2::Clear()
{
	x = 0;
	y = 0;
}
