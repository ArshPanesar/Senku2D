#include "Particle Cable.h"

int Senku2D::ParticleCable::FillContact(ParticleContact* _PC, const int& Limit)
{
	//Getting the Current Length of the Cable
	Real Length = CurrentLength();
	
	//Checking if the Cable has been Extended
	if (Length < m_MaxLength)
	{
		return 0;
	}

	//The Cable has been Extended
	//Assign the Contact
	_PC->p_Particles[0] = p_Particles[0];
	_PC->p_Particles[1] = p_Particles[1];

	//Calculate the Normal
	Vector2 Normal = p_Particles[1]->Position - p_Particles[0]->Position;
	Normal.Normalize();
	_PC->m_ContactNormal = Normal;

	//Calculate the Penetration and the Restitution
	_PC->m_Penetration = Length - m_MaxLength;
	_PC->m_Restitution = m_Restitution;

	return 1;
}
