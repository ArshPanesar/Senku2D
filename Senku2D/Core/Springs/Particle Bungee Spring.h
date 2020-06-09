#pragma once
#include "../Particle Force Generator.h"

namespace Senku2D
{
	//A Bungee Spring Generator
	/*
	This Spring Force Generator Creates a Force when the Spring is Extended,
	And Doesnt do Anything When it gets Pulled Together
	*/
	class ParticleBungeeSpring : public IParticleForceGenerator
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
		ParticleBungeeSpring(Particle* _Other, const Real& _SC, const Real& _RL);

		//Update Force Override
		void UpdateForce(Particle* _Particle, const Real& Timestep) override;
	};

}

