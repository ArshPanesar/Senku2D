#pragma once
#include "../Particle.h"

namespace Senku2D
{
	//A Particle Contact Class
	/*
	This Class Holds the Contact Information of Two Particles in Contact,
	And Resolves Them
	*/
	class ParticleContact
	{
	public:
		//The Two Particles in Contact
		Particle* p_Particles[2];

		//Coefficient of Restitution
		Real m_Restitution;

		//The Contact Normal of the Particles
		Vector2 m_ContactNormal;
	protected:
		//Resolving the Contact
		void Resolve(const Real& Timestep);

		//Calculating the Separating Velocity of this Contact
		Real CalculateSeparatingVelocity() const;
	private:
		//Handling the Impulse Calculations for this Collision
		void ResolveVelocity(const Real& Timestep);
	};
}
