#include "Particle Spring.h"

Senku2D::ParticleSpring::ParticleSpring(Particle* _Other, const Real& _SC, const Real& _RL)
{
	p_OtherParticle = _Other;
	m_SpringConstant = _SC;
	m_RestLength = _RL;
}

void Senku2D::ParticleSpring::UpdateForce(Particle* _Particle, const Real& Timestep)
{
	//Calculating the Vector of the Spring
	Vector2 Force = _Particle->Position - p_OtherParticle->Position;

	//Calculating the Magnitude of the Force
	Real Mag = Force.Magnitude();
	Mag = Real_Abs(Mag - m_RestLength);
	Mag *= m_SpringConstant;

	//Calculating the Final Force and Applying it
	Force.Normalize();
	Force *= -Mag;
	_Particle->AddForce(Force);
}
