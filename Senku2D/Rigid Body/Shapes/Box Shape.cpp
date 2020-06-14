#include "Box Shape.h"

using namespace Senku2D;

Senku2D::BoxShape::BoxShape()	:
	m_HalfHeight(0),
	m_HalfWidth(0)
{
	//Setting the Vertices to Default
	for (unsigned int i = 0; i < 4; ++i)
	{
		m_Vertices[i] = Vector2();
	}
}

Senku2D::BoxShape::~BoxShape()
{
	//Clearing the Vertices
	for (unsigned int i = 0; i < 4; ++i)
	{
		m_Vertices[i].Clear();
	}

	//Reseting the Half Width and Height
	m_HalfHeight = 0;
	m_HalfWidth = 0;
}

void Senku2D::BoxShape::Transform(const Vector2& Position, const Matrix2& Rotation_Matrix)
{
	//Setting the Center Position
	SetCenterPosition(Position);

	//Rotating the Vertices of the Box
	for (unsigned int i = 0; i < 4; ++i)
	{
		m_Vertices[i] = Rotation_Matrix * m_Vertices[i];
	}
	//Rotating the Center
	m_CenterPosition = Rotation_Matrix * m_CenterPosition;
}

void Senku2D::BoxShape::SetBox(const Real& Width, const Real& Height)
{
	//Setting the Half Widths and Height
	m_HalfWidth = Width / (Real)2;
	m_HalfHeight = Height / (Real)2;

	//Setting the Vertices
	SetVertices();
}

void Senku2D::BoxShape::SetVertices()
{
	//Setting Vertices in Local Coordinates
	m_Vertices[0] = Vector2(-m_HalfWidth, -m_HalfHeight);
	m_Vertices[1] = Vector2(m_HalfWidth, -m_HalfHeight);
	m_Vertices[2] = Vector2(m_HalfWidth, m_HalfHeight);
	m_Vertices[3] = Vector2(-m_HalfWidth, m_HalfHeight);
}

const Real Senku2D::BoxShape::GetHalfWidth() const
{
	return m_HalfWidth;
}

const Real Senku2D::BoxShape::GetHalfHeight() const
{
	return m_HalfHeight;
}

const Vector2 Senku2D::BoxShape::GetVertex(const int& Index) const
{
	if (Index < 4)
	{
		return m_Vertices[Index];
	}
	
	return m_Vertices[3];
}


const Vector2* Senku2D::BoxShape::GetVertices() const
{
	return m_Vertices;
}
