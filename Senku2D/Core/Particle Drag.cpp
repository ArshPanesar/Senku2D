#include "Particle Drag.h"

Senku2D::ParticleDrag::ParticleDrag(const Real& _K1, const Real& _K2)
{
	m_K1 = _K1;
	m_K2 = _K2;
}

void Senku2D::ParticleDrag::UpdateForce(Particle* _Particle, const Real& Timestep)
{
	//Getting the Velocity of the Particle
	//Storing it in the Force(Drag) to be Applied
	Vector2 Force = _Particle->Velocity;

	//Getting the Drag Coefficient
	Real DragCoeff = Force.Magnitude();
	DragCoeff = m_K1 * DragCoeff + m_K2 * DragCoeff * DragCoeff;

	//Normalize the Force and Apply It
	Force.Normalize();
	Force *= -DragCoeff;
	_Particle->AddForce(Force);
}
