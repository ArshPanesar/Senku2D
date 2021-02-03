#pragma once
#include "../pch.h"

namespace Senku2D
{
	//An Event Interface
	class EventInterface
	{
	private:
		//Redo Static Grid in the World
		bool m_RedoStaticGrid;

	public:
		//Constructor
		EventInterface();
		//Destructor
		~EventInterface();

		//Singleton
		static EventInterface& Get();

		//Setters
		void SetRedoStaticGrid(const bool& Value);

		//Getters
		const bool& ShouldRedoStaticGrid() const;
	};
}
