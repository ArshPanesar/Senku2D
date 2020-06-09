#pragma once
#include "Particle Force Generator.h"

namespace Senku2D
{
	//A Gravity Generator
	class ParticleGravity : public IParticleForceGenerator
	{
	private:
		//Gravity to Apply
		Vector2 m_Gravity;
	public:
		//Constructing the Generator with a Given Gravity
		ParticleGravity(const Vector2& _Gravity);

		//Update Force Override
		void UpdateForce(Particle* _Particle, const Real& Timestep) override;
	};
}
