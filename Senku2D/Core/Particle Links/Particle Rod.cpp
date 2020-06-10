#include "Particle Rod.h"

int Senku2D::ParticleRod::FillContact(ParticleContact* _PC, const int& Limit)
{
	//Getting the Current Length
	Real CurrentLen = CurrentLength();

	//Check if the Rod has been Extended From Any Side
	if (CurrentLen == m_Length)
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
	
	//The Normal Depends on Whether the Rod has Been Extended or Compressed
	//Extended
	if (CurrentLen > m_Length)
	{
		_PC->m_ContactNormal = Normal;
		_PC->m_Penetration = CurrentLen - m_Length;
	}
	//Compressed
	else if (CurrentLen < m_Length)
	{
		_PC->m_ContactNormal = Normal * -1;
		_PC->m_Penetration = m_Length - CurrentLen;
	}

	//Always 0 Restitution(No Bounciness)
	_PC->m_Restitution = 0;

	return 1;
}
