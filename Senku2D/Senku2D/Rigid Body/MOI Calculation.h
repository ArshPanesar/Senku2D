#pragma once
#include "Shapes/Box Shape.h"
#include "Shapes/Circle Shape.h"

namespace Senku2D
{
	//A Service Class To Calulate Moment of Inertia
	//Calculates Based on Shape of the Rigid Body
	class MOICalculation
	{
	private:
		//Calculate For Box Shape
		static Real CalculateBox(BoxShape* Box);
		//Calculate For Circle Shape
		static Real CalculateCircle(CircleShape* Circle);
	public:
		static Real Calculate(Shape* _Shape);
	};
}
