#include "Particle Contact.h"

void Senku2D::ParticleContact::Resolve(const Real& Timestep)
{
	ResolveVelocity(Timestep);
	ResolveInterpenetration(Timestep);
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

	//Checking the Velocity Build-Up Due to Acceleration that Happened in the Previous Frame
	Vector2 AccInPrevFrame = p_Particles[0]->Acceleration;
	if (p_Particles[1] != nullptr)
	{
		AccInPrevFrame -= p_Particles[1]->Acceleration;
	}
	Real AccCausedSepVel = AccInPrevFrame * m_ContactNormal * Timestep;

	//If the Acceleration Caused a Velocity Build-Up,
	//Remove it from the Separating Velocity
	//This is to Ensure that Resting Collision Doesnt Cause Problems
	if (AccCausedSepVel < 0)
	{
		NewSeparatingVelocity += m_Restitution * AccCausedSepVel;

		//Make Sure that Separating Velocity Is Not Negative
		if (NewSeparatingVelocity < 0)
		{
			NewSeparatingVelocity = 0;
		}
	}

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
	if (p_Particles[1] != nullptr)
	{
		p_Particles[1]->Velocity += ImpulsePerInvMass * -p_Particles[1]->getInverseMass();
	}
}

void Senku2D::ParticleContact::ResolveInterpenetration(const Real& Timestep)
{
	//Checking if there is A Penetration
	if (m_Penetration <= 0)
	{
		return;
	}

	//Getting the Total Inverse Mass
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

	//Finding the Penetration Resolution with Proportionate Inv Mass
	Vector2 MovePerInvMass = m_ContactNormal * (-m_Penetration / TotalInverseMass);

	//Applying the Penetration Resolution
	p_Particles[0]->Position += MovePerInvMass * p_Particles[0]->getInverseMass();
	if (p_Particles[1] != nullptr)
	{
		p_Particles[1]->Position += MovePerInvMass * p_Particles[1]->getInverseMass();
	}

}
