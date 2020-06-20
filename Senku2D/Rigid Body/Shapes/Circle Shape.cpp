#include "Circle Shape.h"

Senku2D::CircleShape::CircleShape()	:
	m_Radius(0)
{
	m_ShapeType = ShapeType::CIRCLE;
}

Senku2D::CircleShape::~CircleShape()
{
	m_Radius = 0;
}

void Senku2D::CircleShape::Transform(const Vector2& Position, const Matrix2& Rotation_Matrix)
{
	//Setting the Center Position
	SetCenterPosition(Position);

	//Transforming the Center With the Rotation Matrix
	m_CenterPosition = Rotation_Matrix * m_CenterPosition;
}

void Senku2D::CircleShape::SetRadius(const Real& Radius)
{
	//Setting the Radius
	m_Radius = Radius;
	//Setting the Bound Size
	SetBoundSize(Vector2((Real)2 * m_Radius, (Real)2 * m_Radius));
}

const Senku2D::Real& Senku2D::CircleShape::GetRadius() const
{
	return m_Radius;
}
