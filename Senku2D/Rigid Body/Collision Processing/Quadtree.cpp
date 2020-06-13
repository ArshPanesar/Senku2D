#include "Quadtree.h"

Senku2D::Quadtree::Quadtree(const Vector2& Position, const Vector2& Size)	:
	m_CurrentAmountOfBodies(0),
	m_RigidBodyList()
{
	//Getting the Position and Size
	m_Position = Position;
	m_Size = Size;

	//Building the AABB for This Quad
	m_Rect.Position = Position;
	m_Rect.Size = Size;

	//Setting the Children Quads to nullptr
	for (unsigned int i = 0; i < 4; ++i)
	{
		m_ChildQuads[i] = nullptr;
	}
}

void Senku2D::Quadtree::Subdivide()
{
	//Dividing the Quadtree
	m_ChildQuads[0] = std::make_unique<Quadtree>(Vector2(m_Position.x, m_Position.y), Vector2(m_Size.x / 2.0f, m_Size.y / 2.0f));
	m_ChildQuads[1] = std::make_unique<Quadtree>(Vector2(m_Position.x + m_Size.x / 2.0f, m_Position.y), Vector2(m_Size.x / 2.0f, m_Size.y / 2.0f));
	m_ChildQuads[2] = std::make_unique<Quadtree>(Vector2(m_Position.x + m_Size.x / 2.0f, m_Position.y + m_Size.y / 2.0f), Vector2(m_Size.x / 2.0f, m_Size.y / 2.0f));
	m_ChildQuads[3] = std::make_unique<Quadtree>(Vector2(m_Position.x, m_Position.y + m_Size.y / 2.0f), Vector2(m_Size.x / 2.0f, m_Size.y / 2.0f));
}

void Senku2D::Quadtree::Insert(RigidBody* _RigidBody)
{

}

void Senku2D::Quadtree::Clear()
{
	//Clearing the Rigid Body List
	for (unsigned int i = 0; i < 4; ++i)
	{
		m_RigidBodyList[i] = nullptr;
	}

	//Clearing the Children
	for (unsigned int i = 0; i < 4; ++i)
	{
		if (m_ChildQuads[i] != nullptr)
		{
			m_ChildQuads[i]->Clear();
		}
	}
}
