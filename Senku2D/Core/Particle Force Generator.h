#pragma once
#include "Particle.h"

namespace Senku2D
{
	//A Particle Force Generator Can Add A Force to One or More Particles
	class IParticleForceGenerator
	{
	public:
		//Pure Virtual Function
		//Updating Force Every Frame on a Particle
		virtual void UpdateForce(Particle* _Particle, const Real& Timestep) = 0;;
	};
}