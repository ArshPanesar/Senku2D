#pragma once
#include "../Potential Contact List.h"

namespace Senku2D
{
	namespace HashedGrid
	{
		//Limits
		const size_t DEFAULT_NUM_OF_CELLS = 256;

		//Cell Position
		struct CellPosition
		{
			int x = 0;
			int y = 0;

			//Operator Equals
			bool operator==(const CellPosition& Other) const;
		};

		//Cell Position Hasher
		/*
		** Uses a Custom Hash Function.
		*/
		struct CellPositionHasher
		{
			size_t operator()(const CellPosition& Position) const;
		};

		//Typedefs
		//CellFlags
		/*
		** A 2-Bit Flag Used to Check the State of a Cell.
		** First Bit - Cell is Not Empty(1) / Empty(0).
		** Second Bit - Cell Has been Checked(1) / Unchecked(0) by a Query.
		*/
		typedef std::bitset<2> CellFlags;

		//Cell Data
		/*
		** Stores Lists of Lists of Rigid Body Pointers and Bitset Flags.
		** Lists of Lists have been used to Optimize Cache Usage.
		*/
		struct CellData
		{
			std::vector<std::vector<RigidBody*>> BodyList;
			std::vector<CellFlags> Flags;
		};
	}
}
