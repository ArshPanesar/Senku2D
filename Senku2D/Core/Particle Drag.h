#pragma once
#include "Particle Force Generator.h"

namespace Senku2D
{
	//A Force Generator for Drag
	//We Use a Complex Formula to Calculate Drag for the Particle
	class ParticleDrag :public IParticleForceGenerator
	{
	private:
		//Drag Coefficient
		Real m_K1;
		//Squared Drag Coefficient
		Real m_K2;
	public:
		//Constructing a Drag Generator
		ParticleDrag(const Real& _K1, const Real& _K2);

		//Update Force Override
		void UpdateForce(Particle* _Particle, const Real& Timestep) override;
	};
}
