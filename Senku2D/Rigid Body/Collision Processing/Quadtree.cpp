#include "Quadtree.h"

Senku2D::Quadtree::Quadtree(const Vector2& Position, const Vector2& Size, const int& Level)	:
	m_CurrentAmountOfBodies(0),
	m_RigidBodyList(),
	m_ChildQuads(),
	m_CurrentLevel(Level)
{
	//Getting the Position and Size
	m_Position = Position;
	m_Size = Size;

	//Building the AABB for This Quad
	m_Rect.Position = Position;
	m_Rect.Size = Size;

	//Reserving Size for Rigid Body Pointer Container
	if (Level == m_MaxLevels)
	{
		m_RigidBodyList.reserve(10);
	}
	else
	{
		m_RigidBodyList.reserve(4);
	}

	//Setting the Children Quads to nullptr
	for (unsigned int i = 0; i < 4; ++i)
	{
		m_ChildQuads[i] = nullptr;
	}
}

void Senku2D::Quadtree::Subdivide()
{
	//Dividing the Quadtree
	//Allocating Memory on the Heap(Sorry C++ Gods)
	m_ChildQuads[0] = new Quadtree(Vector2(m_Position.x, m_Position.y), Vector2(m_Size.x / 2.0f, m_Size.y / 2.0f), m_CurrentLevel + 1);
	m_ChildQuads[1] = new Quadtree(Vector2(m_Position.x + m_Size.x / 2.0f, m_Position.y), Vector2(m_Size.x / 2.0f, m_Size.y / 2.0f), m_CurrentLevel + 1);
	m_ChildQuads[2] = new Quadtree(Vector2(m_Position.x + m_Size.x / 2.0f, m_Position.y + m_Size.y / 2.0f), Vector2(m_Size.x / 2.0f, m_Size.y / 2.0f), m_CurrentLevel + 1);
	m_ChildQuads[3] = new Quadtree(Vector2(m_Position.x, m_Position.y + m_Size.y / 2.0f), Vector2(m_Size.x / 2.0f, m_Size.y / 2.0f), m_CurrentLevel + 1);
}

void Senku2D::Quadtree::Insert(RigidBody* _RigidBody)
{
	//First Checking if this AABB Intersects the Passed Down Rigid Body
	if (!m_Rect.Overlaps(_RigidBody->GetAABB()))
	{
		return;
	}

	//If We are At The Deepest Level Node
	if (m_CurrentLevel == m_MaxLevels)
	{
		//Then Add All Remaining Bodies Here
		//Regardless of the Max Bodies Allowed
		m_RigidBodyList.push_back(_RigidBody);

		//Still Increase the Counter of How Many Rigid Bodies are There
		++m_CurrentAmountOfBodies;

		//Break Out
		return;
	}
	
	//Add the Rigid Body to the List for this Sub-Node
	if (m_CurrentAmountOfBodies < m_MaxBodiesAllowed && m_ChildQuads[0] == nullptr)
	{
		//Add the Bodies to the List
		m_RigidBodyList.push_back(_RigidBody);

		//Increase the Counter of How Many Rigid Bodies are There
		++m_CurrentAmountOfBodies;

		//Break Out
		return;
	}

	//If Child Quads Dont Exist
	if (m_ChildQuads[0] == nullptr)
	{
		//Then Subdivide
		Subdivide();
	}

	//Add the Rigid Body Pointer to the Quad that Fits
	for (unsigned int i = 0; i < 4; ++i)
	{
		m_ChildQuads[i]->Insert(_RigidBody);
	}
}

void Senku2D::Quadtree::Query(RigidBody* _RigidBody, PotentialRigidBodyContact* Contacts, const unsigned int& Limit)
{
	//Check if This Quad Intersects the Given Rigid Body
	if (m_Rect.Overlaps(_RigidBody->GetAABB()))
	{
		//Check if This Quad Has Children
		if (m_ChildQuads[0] == nullptr)
		{
			//Fill the Contact List
			for (unsigned int i = 0; i < Limit; ++i)
			{
				Contacts[i].RigidBodies[0] = _RigidBody;
				Contacts[i].RigidBodies[1] = m_RigidBodyList[i];
			}
			//Break Out
			return;
		}

		//Get the Child Quad Which Contains This Rigid Body
		for (unsigned int i = 0; i < 4; ++i)
		{
			m_ChildQuads[i]->Query(_RigidBody, Contacts, Limit);
		}
	}
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
			//Clearing the Children
			m_ChildQuads[i]->Clear();
			//Deleting Memory(See I took care of it, NO REASON TO WORRY)
			delete m_ChildQuads[i];
		}
	}

	//Reseting the ChildQuads
	for (unsigned int i = 0; i < 4; ++i)
	{
		m_ChildQuads[i] = nullptr;
	}
}
