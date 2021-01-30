#pragma once
#include "../../Shapes/Shape.h"

namespace Senku2D
{
	//A Pair of Shape Types Typedef
	typedef std::pair<ShapeType, ShapeType> ShapeTypePair;

	//Maximum Number of Shape Pairs That Can Exist
	const unsigned int NUM_OF_SHAPE_PAIRS = 3;

	//Shape Pair Enum
	enum class ShapePairs
	{
		BOX_AND_BOX = 0,
		BOX_AND_CIRCLE,
		CIRCLE_AND_CIRCLE
	};

	//A Shape Solver Class
	/*
	This Class Generates a Map of Pair of Shape Types To a Shape Pair Enum.
	*/
	class ShapeSolver
	{
	private:
		//Internal Shape Pair Map
		std::map<ShapeTypePair, ShapePairs> m_InternalMap;

		//Constructor
		ShapeSolver();
	public:
		//Singleton
		static ShapeSolver& Get();

		//Destructor
		~ShapeSolver();

		//Getting the Shape Pair
		ShapePairs GetShapePair(const ShapeType& ST_1, const ShapeType& ST_2);
	};
}
