#include "Particle Bungee Spring.h"

Senku2D::ParticleBungeeSpring::ParticleBungeeSpring(Particle* _Other, const Real& _SC, const Real& _RL)
{
	p_OtherParticle = _Other;
	m_SpringConstant = _SC;
	m_RestLength = _RL;
}

void Senku2D::ParticleBungeeSpring::UpdateForce(Particle* _Particle, const Real& Timestep)
{
	//Getting the Force Vector
	Vector2 Force = _Particle->Position - p_OtherParticle->Position;

	//Check if Bungee is Compressed
	Real Mag = Force.Magnitude();
	if (Mag <= m_RestLength)
	{
		//Do Nothing
		return;
	}

	//Get the Magnitude of the Spring Force
	Mag = m_SpringConstant * (m_RestLength - Mag);

	//Add and Apply the Force
	Force.Normalize();
	Force *= -Mag;
	_Particle->AddForce(Force);
}
