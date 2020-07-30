#include "MOI Calculation.h"

using namespace Senku2D;

Real Senku2D::MOICalculation::CalculateBox(BoxShape* Box)
{
	Real MOI = (Real)0;

	//Using Formula ((Length^3) * Breadth) / 12
	//Getting Variables
	Real Length = Box->GetHalfWidth() * (Real)2;
	Real Breadth = Box->GetHalfHeight() * (Real)2;
	Real LengthCubed = Real_Pow(Length, 3);
	//Calculating
	MOI = (LengthCubed * Breadth) / ((Real)12);

	return MOI;
}

Real Senku2D::MOICalculation::CalculateCircle(CircleShape* Circle)
{
	return Real();
}

Real Senku2D::MOICalculation::Calculate(Shape* _Shape)
{
	//Value to Hold
	Real MOI = (Real)0;

	//Casting Based on Shape
	switch (_Shape->GetShapeType())
	{
	case ShapeType::BOX:
		
		//Calculate For Box
		MOI = CalculateBox((BoxShape*)(_Shape));
		break;

	case ShapeType::CIRCLE:
		
		//Calculate Based on Circle
		MOI = CalculateCircle((CircleShape*)(_Shape));
		break;
	}

	return MOI;
}
