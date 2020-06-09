#include "Particle Contact.h"

void Senku2D::ParticleContact::Resolve(const Real& Timestep)
{
	ResolveVelocity(Timestep);
}

Senku2D::Real Senku2D::ParticleContact::CalculateSeparatingVelocity() const
{
	//Getting the Relative Velocity
	Vector2 RelativeVelocity = p_Particles[0]->Velocity;
	if (p_Particles[1] != nullptr)
	{
		RelativeVelocity -= p_Particles[1]->Velocity;
	}

	return RelativeVelocity * m_ContactNormal;
}

void Senku2D::ParticleContact::ResolveVelocity(const Real& Timestep)
{
	//Finding the Separating Velocity in the Direction of Contact
	Real SeparatingVelocity = CalculateSeparatingVelocity();

	//Checking Whether the Contact Needs to be Resolved
	if (SeparatingVelocity > 0)
	{
		return;
	}

	//Calculating the new Separating Velocity with Respect to Restitution
	Real NewSeparatingVelocity = SeparatingVelocity * m_Restitution;

	//Getting the Delta Velocity
	Real DeltaVelocity = NewSeparatingVelocity - SeparatingVelocity;

	/*
	Applying the Delta Velocity(Change in Velocity) to Each Particle
	in Proportion to its Inverse Mass. Example: The Particle With Lower 
	Inverse Mass(High Mass) Gets Less Change in Velocity!
	*/
	Real TotalInverseMass = p_Particles[0]->getInverseMass();
	if (p_Particles[1] != nullptr)
	{
		TotalInverseMass += p_Particles[1]->getInverseMass();
	}

	//Checking if Both Particles have Infinite Mass
	//If Yes, then Dont do Anything
	if (TotalInverseMass <= 0)
	{
		return;
	}

	//Calculating the Impulse to Apply
	Real Impulse = DeltaVelocity / TotalInverseMass;

	//Getting the Amount of Impulse Per Inverse Mass
	Vector2 ImpulsePerInvMass = m_ContactNormal * Impulse;

	//Applying the Impulses
	p_Particles[0]->Velocity += ImpulsePerInvMass * p_Particles[0]->getInverseMass();
	//Particle 1 Goes in the Opposite Direction
	p_Particles[1]->Velocity += ImpulsePerInvMass * -p_Particles[1]->getInverseMass();
}
