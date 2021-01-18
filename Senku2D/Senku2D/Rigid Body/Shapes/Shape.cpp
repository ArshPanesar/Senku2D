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

void Senku2D::Shape::SetShapeType(const ShapeType& ST)
{
	m_ShapeType = ST;
}

void Senku2D::Shape::SetBoundSize(const Vector2& Size)
{
	m_BoundSize = Size;
}

const Senku2D::Vector2 Senku2D::Shape::GetCenterPosition() const
{
	return m_CenterPosition;
}

const Senku2D::ShapeType Senku2D::Shape::GetShapeType() const
{
	return m_ShapeType;
}

const Senku2D::Vector2 Senku2D::Shape::GetBoundSize() const
{
	return m_BoundSize;
}
