#pragma once
#include "Shape.h"

namespace Senku2D
{
	//A Box Shape Class
	//This Shape Will be Used for Both Rectangles and Squares
	class BoxShape : public Shape
	{
	private:
		//Vertices of the Box
		Vector2 m_Vertices[4];

		//Half Width and Half Height of the Box
		Real m_HalfWidth;
		Real m_HalfHeight;

		//Setting Vertices
		void SetVertices();
	public:
		//Constructor
		BoxShape();
		//Destructor
		~BoxShape();

		//Transform Override
		void Transform(const Vector2& Position, const Matrix2& Rotation_Matrix) override;

		//Setters
		void SetBox(const Real& Width, const Real& Height);
		
		//Operator=


		//Getters
		const Real GetHalfWidth() const;
		const Real GetHalfHeight() const;
		const Vector2 GetVertex(const int& Index) const;
		const Vector2* GetVertices() const;
	};
}

