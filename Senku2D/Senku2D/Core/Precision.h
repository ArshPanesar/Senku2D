#pragma once
#include "../pch.h"

//Sqrt Operation on a Real Number
#define Real_Sqrt sqrtf
//Absolute Operator
#define Real_Abs fabsf
//Pow Operator
#define Real_Pow powf
//Sine Function
#define Real_Sin sinf
//Cosine Function
#define Real_Cos cosf
//Exponential Function
#define Real_Exp expf
//Minimum Function
#define Real_Min fminf
//Maximum Function
#define Real_Max fmaxf
//Floor and Ceil FUnctions
#define Real_Floor floorf
#define Real_Ceil ceilf

namespace Senku2D
{
	//Floating Point Precision
	typedef float Real;

	//Unsigned Integer
	typedef uint32_t U32;
	typedef uint16_t U16;
	typedef uint8_t U8;

	//Angle Constants
	const float RADTODEG = 57.2958f;
	const float DEGTORAD = 0.01745f;

	//PI
	const float PI = 22.0f / 7.0f;
}
