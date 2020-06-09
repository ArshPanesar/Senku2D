#pragma once

//Includes
#include <iostream>


//Logging To Console
template<typename T>
inline void PRT(const T& x)
{
	std::cout << x << std::endl;
}

template<typename T>
inline void PRT2(const T& x, const T& y)
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
