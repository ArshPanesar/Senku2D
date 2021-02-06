#include "Particle.h"

Senku2D::Particle::Particle()	:
	m_InverseMass(0),
	m_Position(),
	m_Velocity(),
	m_Acceleration(),
	m_Damping(0),
	m_ForceAccum()
{

}

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

void Senku2D::Particle::SetPosition(const Vector2& Position)
{
	m_Position = Position;
}

void Senku2D::Particle::SetVelocity(const Vector2& Velocity)
{
	m_Velocity = Velocity;
}

void Senku2D::Particle::SetAcceleration(const Vector2& Acc)
{
	m_Acceleration = Acc;
}

void Senku2D::Particle::SetDamping(const Real& Damping)
{
	m_Damping = Damping;
}

void Senku2D::Particle::AddForce(const Vector2& Force)
{
	m_ForceAccum = Force;
}

void Senku2D::Particle::Integrate(const Real& Timestep)
{
	//Update the Linear Position of the Particle
	m_Position.AddScaledVector(m_Velocity, Timestep);
	m_Position.AddScaledVector(m_Acceleration, Timestep * Timestep * 0.5f);

	//Update the Acceleration from the Force
	Vector2 ResultingAcc = m_Acceleration;
	ResultingAcc.AddScaledVector(m_ForceAccum, m_InverseMass);

	//Update Linear Velocity from the Resulting Acceleration
	m_Velocity.AddScaledVector(ResultingAcc, Timestep * 0.5f);

	//Impose Drag on Particle's Velocity
	m_Velocity *= Real_Pow(m_Damping, Timestep);

	//Clear the Accumulator
	ClearAccumulator();
}

const Senku2D::Real Senku2D::Particle::GetInverseMass() const
{
	return m_InverseMass;
}

const Senku2D::Vector2 Senku2D::Particle::GetPosition() const
{
	return m_Position;
}

const Senku2D::Vector2 Senku2D::Particle::GetVelocity() const
{
	return m_Velocity;
}

const Senku2D::Vector2 Senku2D::Particle::GetAcceleration() const
{
	return m_Acceleration;
}

const Senku2D::Real Senku2D::Particle::GetDamping() const
{
	return m_Damping;
}

void Senku2D::Particle::ClearAccumulator()
{
	m_ForceAccum.Clear();
}
