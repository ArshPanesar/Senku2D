#include "Particle Stiff Spring.h"

Senku2D::ParticleStiffSpring::ParticleStiffSpring(const Vector2& _Anchor, const Real& SC, const Real& Damping)
{
	m_Anchor = _Anchor;
	m_SpringConstant = SC;
	m_Damping = Damping;
}

void Senku2D::ParticleStiffSpring::UpdateForce(Particle* _Particle, const Real& Timestep)
{
	//Check that the Particle Does Not have Infinite Mass
	if (_Particle->getInverseMass() == 0)
	{
		return;
	}

	//Getting the Relative Position of the Particle to the Anchor
	Vector2 Position = _Particle->Position;
	Position -= m_Anchor;

	//Calculate the Consants and Check Whether They are in Bounds
	Real Gamma = 0.5f * Real_Sqrt(4 * m_SpringConstant - m_Damping * m_Damping);
	if (Gamma == 0.0f)
	{
		return;
	}
	Vector2 C = Position * (m_Damping / (2.0f * Gamma)) + _Particle->Velocity * (1.0f / Gamma);


	//Calculate the Target Position
	Vector2 Target = Position * Real_Cos(Gamma * Timestep) + C * Real_Sin(Gamma * Timestep);
	Target *= Real_Exp(-0.5f * Timestep * m_Damping);

	//Calculating the Resulting Acceleration
	Vector2 Acc = (Target - Position) * (1.0f / Timestep * Timestep) - _Particle->Velocity * Timestep;

	//Applying the Force
	_Particle->AddForce(Acc * (1.0f / _Particle->getInverseMass()));
}
