#pragma once
#include "../../Core/Precision.h"

namespace Senku2D
{
	//Collision Filters
	/*
	** Use these Filters to Control What Should Collide in The World.
	** CategoryBits and MaskBits Should be in the Format 0xXXXX where X can be Either
	** 0, 1, 2, 4, 8 (Powers of 2)
	*/
	struct Filters
	{
		//Sets a Category to Which a Body will Belong to
		/*
		** Default Category Bits For All Bodies is 0x1000. Thus the 4th Bit From the Right
		** is Reserved by Senku2D. Example Usage - AIRCRAFT = 0x0010 (Converts to 16 in 
		** Decimal).
		*/
		U16 CategoryBits = 0x1000;

		//Sets Mask Bits to Which a Body can Collide With
		/*
		** Same Format as Category Bits with 0xFFFF (Default Value) Reserved by The Engine.
		** Use OR on the Category Bits you want This Category to Collide with. 
		** Example Usage - Mask Bits = AIRCRAFT | AIRCRAFT.
		*/
		U16 MaskBits = 0xFFFF;
	};
}
