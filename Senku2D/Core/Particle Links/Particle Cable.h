#pragma once
#include "Particle Link.h"

namespace Senku2D
{
	//A Cable Link
	//A Cable Link Will Allow Particles to be Close to Each other
	//But Not Far Apart
	class ParticleCable : public IParticleLink
	{
	public:
		//The Maximum Length of the Cable
		Real m_MaxLength;
		
		//The Restitution(Bounciness) of the Cable
		Real m_Restitution;

	public:
		//Fill Contact Override
		int FillContact(ParticleContact* _PC, const int& Limit) override;
	};
}

