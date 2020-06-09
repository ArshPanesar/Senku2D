#pragma once
#include "../Particle Force Generator.h"

namespace Senku2D
{
	//An Anchored Spring Generator
	/*
	This Spring Force Generator will Generate a Spring Force for a Particle
	with Respect to a Point in 2D Space - An Anchor
	*/
	class ParticleAnchoredSpring : public IParticleForceGenerator
	{
	private:
		//An Anchor for the Spring
		Vector2 m_AnchorPoint;

		//A Spring Constant
		Real m_SpringConstant;

		//Rest Length for the Spring
		Real m_RestLength;
	public:
		//Constructing an Anchored Spring for a Particle
		ParticleAnchoredSpring(const Vector2& _Anchor, const Real& _SC, const Real& _RL);
	
		//Update Force Override
		void UpdateForce(Particle* _Particle, const Real& Timestep) override;
	};
}
