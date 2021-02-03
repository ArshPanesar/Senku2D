#pragma once

//Includes
#include <vector>
#include <assert.h>
#include <map>
#include <unordered_map>
#include <bitset>

//Debug Only For Testing
#ifdef _DEBUG
#include <iostream>
#include <chrono>

namespace Senku2D
{
	//Logging To Console
	template<typename T>
	inline void PRT(const T& x)
	{
		std::cout << x << std::endl;
	}
	template<typename T1, typename T2>
	inline void PRT2(const T1& x, const T2& y)
	{
		std::cout << x << "\t" << y << std::endl;
	}
}

#endif
