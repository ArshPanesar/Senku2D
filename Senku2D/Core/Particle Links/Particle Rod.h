#pragma once
#include "Particle Link.h"

namespace Senku2D
{
	//A Rod Link
	/*
	A Rod Link Between Particles will Not Allow Any Movement Further or Apart
	The Rod will keep the Particles Fixed
	*/
	class ParticleRod : public IParticleLink
	{
	public:
		//The Length of the Rod
		Real m_Length;

	public:
		//Fill Contact Override
		int FillContact(ParticleContact* _PC, const int& Limit) override;
	};
}
