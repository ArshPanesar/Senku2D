#pragma once
#include "Particle Contact.h"

namespace Senku2D
{
	//A Contact Resolver for Particles
	class ParticleContactResolver
	{
	protected:
		//The Number of Iterations Allowed
		unsigned int m_Iterations;

		//The Number of Iterations Used Up
		unsigned int m_IterationsUsed;
	public:
		//Constructing a Particle Contact Resolver
		ParticleContactResolver(const unsigned int& Iterations);

		//Setting the Iterations
		void SetIterations(const unsigned int& Iterations);

		//Resolve the Contacts
		void ResolveContacts(ParticleContact* ContactArray, const unsigned int& NumOfContacts, const Real& Timestep);
	};
}
