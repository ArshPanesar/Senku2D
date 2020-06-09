#pragma once
#include "../Particle Force Generator.h"

namespace Senku2D
{
	//A Basic Spring Force Generator
	/*
	This Basic Spring Force Generator Works by Considering Two Particles Joined
	at the End Together by the Spring
	*/
	class ParticleSpring : public IParticleForceGenerator
	{
	private:
		//Particle at the Other End of the Spring
		Particle* p_OtherParticle;

		//Spring Constant
		Real m_SpringConstant;

		//Resting Length of the Spring
		Real m_RestLength;

	public:
		//Construct a Particle Spring Generator
		ParticleSpring(Particle* _Other, const Real& _SC, const Real& _RL);

		//Update Force Override
		void UpdateForce(Particle* _Particle, const Real& Timestep) override;
	};
}
