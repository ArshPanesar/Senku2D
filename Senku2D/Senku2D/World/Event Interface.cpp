#include "Event Interface.h"

Senku2D::EventInterface::EventInterface()	:
	m_RedoStaticGrid(false)
{

}

Senku2D::EventInterface::~EventInterface()
{
	m_RedoStaticGrid = false;
}

Senku2D::EventInterface& Senku2D::EventInterface::Get()
{
	static EventInterface s_Instance;
	return s_Instance;
}

void Senku2D::EventInterface::SetRedoStaticGrid(const bool& Value)
{
	m_RedoStaticGrid = Value;
}

const bool& Senku2D::EventInterface::ShouldRedoStaticGrid() const
{
	return m_RedoStaticGrid;
}
