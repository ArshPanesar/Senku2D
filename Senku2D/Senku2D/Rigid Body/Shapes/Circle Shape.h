#pragma once
#include "Shape.h"

namespace Senku2D
{
	//A Circle Shape Class
	class CircleShape : public Shape
	{
	private:
		//Radius of the Circle
		Real m_Radius;
	public:
		//Constructor
		CircleShape();
		//Destructor
		~CircleShape();

		//Transform Function Override
		void Transform(const Vector2& Position, const Matrix2& Rotation_Matrix) override;

		//Setting Radius for the Circle
		void SetRadius(const Real& Radius);

		//Getting Radius
		const Real& GetRadius() const;
	};
}
