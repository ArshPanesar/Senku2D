#include "Shape.h"

Senku2D::Shape::Shape()	:
	m_CenterPosition((Real)0, (Real)0),
	m_ShapeType(ShapeType::BOX)
{

}

Senku2D::Shape::~Shape()
{
	m_CenterPosition.Clear();
}

void Senku2D::Shape::SetCenterPosition(const Vector2& Position)
{
	m_CenterPosition = Position;
}

void Senku2D::Shape::SetShapeType(const ShapeType& ST)
{
	m_ShapeType = ST;
}

const Senku2D::Vector2 Senku2D::Shape::GetCenterPosition() const
{
	return m_CenterPosition;
}

const Senku2D::ShapeType Senku2D::Shape::GetShapeType() const
{
	return m_ShapeType;
}
