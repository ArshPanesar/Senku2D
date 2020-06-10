#include "Particle Contact Resolver.h"

Senku2D::ParticleContactResolver::ParticleContactResolver(const unsigned int& Iterations)
{
	m_Iterations = Iterations;
	m_IterationsUsed = 0;
}

void Senku2D::ParticleContactResolver::SetIterations(const unsigned int& Iterations)
{
	m_Iterations = Iterations;
}

void Senku2D::ParticleContactResolver::ResolveContacts(ParticleContact* ContactArray, const unsigned int& NumOfContacts, const Real& Timestep)
{
	//Reset the Iterations Used
	m_IterationsUsed = 0;

	//Running the Loop
	while (m_IterationsUsed < m_Iterations)
	{
		//Find the Contact with the Largest Closing Velocity
		Real Max = 0;
		unsigned int MaxIndex = NumOfContacts;
		for (unsigned int i = 0; i < NumOfContacts; ++i)
		{
			Real SepVel = ContactArray[i].CalculateSeparatingVelocity();
			if (SepVel < Max)
			{
				Max = SepVel;
				MaxIndex = i;
			}
		}

		//Resolve this Largest Contact
		ContactArray[MaxIndex].Resolve(Timestep);

		//Iterations Used
		++m_IterationsUsed;
	}
}
