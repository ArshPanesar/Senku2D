#include "Quadtree.h"

Senku2D::Quadtree::Quadtree()	:
	m_Bounds(),
	m_CurrentNumOfBodies(4)
{

}

Senku2D::Quadtree::~Quadtree()
{
	m_CurrentNumOfBodies = 0;
}
