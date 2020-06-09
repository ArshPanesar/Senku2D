#include "Particle Gravity.h"

Senku2D::ParticleGravity::ParticleGravity(const Vector2& _Gravity)
{
	m_Gravity = _Gravity;
}

void Senku2D::ParticleGravity::UpdateForce(Particle* _Particle, const Real& Timestep)
{
	//No Gravity Applied for Infinite Mass!
	if (_Particle->getInverseMass() == 0)
	{
		return;
	}

	//Applying Gravity
	_Particle->AddForce(m_Gravity * ((Real)1 / _Particle->getInverseMass()));
}
