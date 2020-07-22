#pragma once

//Includes
#include <iostream>
#include <vector>

namespace Senku2D
{

	//Logging To Console
	//
	template<typename T>
	inline void PRT(const T& x)
	{
		std::cout << x << std::endl;
	}
	//
	template<typename T1, typename T2>
	inline void PRT2(const T1& x, const T2& y)
	{
		std::cout << x << "\t" << y << std::endl;
	}
	//

	//Angle Constants
	const float RADTODEG = 57.2958f;
	const float DEGTORAD = 0.01745f;
}