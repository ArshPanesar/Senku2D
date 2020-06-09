#include "Particle Anchored Spring.h"

Senku2D::ParticleAnchoredSpring::ParticleAnchoredSpring(const Vector2& _Anchor, const Real& _SC, const Real& _RL)
{
	m_AnchorPoint = _Anchor;
	m_SpringConstant = _SC;
	m_RestLength = _RL;
}

void Senku2D::ParticleAnchoredSpring::UpdateForce(Particle* _Particle, const Real& Timestep)
{
	//Calculating the Vector of the Spring
	Vector2 Force = _Particle->Position - m_AnchorPoint;

	//Calculating the Magnitude of the Force
	Real Mag = Force.Magnitude();
	Mag = Real_Abs(Mag - m_RestLength);
	Mag *= m_SpringConstant;

	//Calculating the Final Force and Applying it
	Force.Normalize();
	Force *= -Mag;
	_Particle->AddForce(Force);
}
