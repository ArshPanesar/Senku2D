#include "Shape Solver.h"

Senku2D::ShapeSolver::ShapeSolver()
{
	//Inserting Shape Pairs To Map
	//
	//Generating All Shape Type Pairs
	ShapeTypePair BoxAndBox(ShapeType::BOX, ShapeType::BOX);
	ShapeTypePair BoxAndCircle(ShapeType::BOX, ShapeType::CIRCLE);
	ShapeTypePair CircleAndBox(ShapeType::CIRCLE, ShapeType::BOX);
	ShapeTypePair CircleAndCircle(ShapeType::CIRCLE, ShapeType::CIRCLE);
	//
	//Inserting All Shape Type Pairs
	m_InternalMap[BoxAndBox] = ShapePairs::BOX_AND_BOX;
	m_InternalMap[BoxAndCircle] = ShapePairs::BOX_AND_CIRCLE;
	m_InternalMap[CircleAndBox] = ShapePairs::BOX_AND_CIRCLE;
	m_InternalMap[CircleAndCircle] = ShapePairs::CIRCLE_AND_CIRCLE;
}

Senku2D::ShapeSolver& Senku2D::ShapeSolver::Get()
{
	static ShapeSolver s_Instance;
	return s_Instance;
}

Senku2D::ShapeSolver::~ShapeSolver()
{
	//Clearing the Map
	m_InternalMap.clear();
}

Senku2D::ShapePairs Senku2D::ShapeSolver::GetShapePair(const ShapeType& ST_1, const ShapeType& ST_2)
{
	ShapeTypePair Pair(ST_1, ST_2);
	return m_InternalMap[Pair];
}
