#pragma once
#include "../../Core/Matrix2.h"

namespace Senku2D
{
	//Enumeration for the Type of Existing Shapes
	enum class ShapeType
	{
		CIRCLE = 0,
		BOX
	};

	//A Base Shape Class for All the Existing Shapes in the Physics Engine
	class Shape
	{
	protected:
		//Type of Shape
		ShapeType m_ShapeType;

		//Center Position of This Shape in World Coordinates
		Vector2 m_CenterPosition;
		
		//Bounds Size of the Shape
		Vector2 m_BoundSize;
	public:
		//Constructor
		Shape();
		//Destructor
		virtual ~Shape();

		//Pure Virtual Function
		//Transform the Shape According to the Rigid Body's Attributes
		virtual void Transform(const Vector2& Position, const Matrix2& Rotation_Matrix) = 0;

		//Setting Center Position(In World Coordinates)
		void SetCenterPosition(const Vector2& Position);
		//Setting the Shape Type
		void SetShapeType(const ShapeType& ST);
		//Setting the Bound Size
		void SetBoundSize(const Vector2& Size);

		//Getting Center Position(In World Coordinates)
		const Vector2 GetCenterPosition() const;
		//Getting the Shape Type
		const ShapeType GetShapeType() const;
		//Getting Bound Size
		const Vector2 GetBoundSize() const;
	};
}

