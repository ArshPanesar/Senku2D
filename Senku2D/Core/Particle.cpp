#include "Particle.h"

void Senku2D::Particle::SetInverseMass(const Real& InvMass)
{
	m_InverseMass = InvMass;
}

void Senku2D::Particle::SetMass(const Real& Mass)
{
	if (Mass != 0)
	{
		m_InverseMass = ((Real)1 / Mass);
	}
}

void Senku2D::Particle::Integrate(const Real& Timestep)
{
	//Update the Linear Position of the Particle
	Position.AddScaledVector(Velocity, Timestep);

	//Update the Acceleration from the Force
	Vector2 ResultingAcc = Acceleration;
	ResultingAcc.AddScaledVector(ForceAccum, m_InverseMass);

	//Update Linear Velocity from the Resulting Acceleration
	Velocity.AddScaledVector(ResultingAcc, Timestep);

	//Impose Drag on Particle's Velocity
	Velocity *= Real_Pow(Damping, Timestep);
}
