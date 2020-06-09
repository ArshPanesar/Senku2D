#pragma once
#include "../Particle Force Generator.h"

namespace Senku2D
{
	//A Stiff Spring Force Generator
	/*
	This Spring Force Generator Fakes a Stiff Spring Simulation.
	It Uses a Fixed Anchor Point and the Particle
	*/
	class ParticleStiffSpring : public IParticleForceGenerator
	{
	private:
		//Fixed Anchor in 2D Space
		Vector2 m_Anchor;

		//The Spring Constant
		Real m_SpringConstant;

		//Damping Produced
		Real m_Damping;
	public:
		//Constructing a Stiff Spring
		ParticleStiffSpring(const Vector2& _Anchor, const Real& SC, const Real& Damping);

		//Update Force Override
		void UpdateForce(Particle* _Particle, const Real& Timestep) override;
	};
}
