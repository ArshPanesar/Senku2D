#pragma once

//Includes
#include <iostream>
#include <vector>

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

template<typename T>
inline void PRTERR(const T& x)
{
	std::cerr << x << std::endl;
}

template<typename T>
inline void PRTERR2(const T& x, const T& y)
{
	std::cerr << x << "\t" << y << std::endl;
}

template<typename T>
inline void PRTARR(T& arr, int size)
{
	for (unsigned int i = 0; i < size; ++i)
	{
		PRT(arr[i], ", ");
	}
}

//Angle Constants
const float RADTODEG = 57.2958f;
const float DEGTORAD = 0.01745f;
