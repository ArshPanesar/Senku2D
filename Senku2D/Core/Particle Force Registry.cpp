#include "Particle Force Registry.h"

Senku2D::ParticleForceRegistry::ParticleForceRegistry()
{
	//Reserving Memory
	m_Registrations.reserve(MAX_REGISTRATIONS);
}

void Senku2D::ParticleForceRegistry::Add(Particle* _Particle, IParticleForceGenerator* _ForceGen)
{
	//Setting the Pointers
	ParticleForceRegistration PFR;
	PFR.p_Particle = _Particle;
	PFR.p_ParticleGen = _ForceGen;

	//Pushing it to the Registry
	m_Registrations.push_back(PFR);
}

void Senku2D::ParticleForceRegistry::Remove(Particle* _Particle, IParticleForceGenerator* _ForceGen)
{
	//Setting the Pointers
	ParticleForceRegistration PFR;
	PFR.p_Particle = _Particle;
	PFR.p_ParticleGen = _ForceGen;

	//Finding the Registration
	for (auto itr = m_Registrations.begin(); itr != m_Registrations.end(); ++itr)
	{
		if (*itr == PFR)
		{
			//Remove the Registration
			m_Registrations.erase(itr);
			break;
		}
	}
}

void Senku2D::ParticleForceRegistry::Clear()
{
	m_Registrations.clear();
}

void Senku2D::ParticleForceRegistry::UpdateForces(const Real& Timestep)
{
	//Updating Particle Forces
	for (auto itr = m_Registrations.begin(); itr != m_Registrations.end(); ++itr)
	{
		itr->p_ParticleGen->UpdateForce(itr->p_Particle, Timestep);
	}
}

bool Senku2D::ParticleForceRegistry::ParticleForceRegistration::operator==(const ParticleForceRegistration& Other)
{
	if (p_Particle == Other.p_Particle && p_ParticleGen == Other.p_ParticleGen)
	{
		return true;
	}

	return false;
}

Senku2D::ParticleForceRegistry::ParticleForceRegistration::ParticleForceRegistration()	:
	p_Particle(nullptr),
	p_ParticleGen(nullptr)
{

}

Senku2D::ParticleForceRegistry::ParticleForceRegistration::ParticleForceRegistration(const ParticleForceRegistration& Other)
{
	p_Particle = Other.p_Particle;
	p_ParticleGen = Other.p_ParticleGen;
}

Senku2D::ParticleForceRegistry::ParticleForceRegistration Senku2D::ParticleForceRegistry::ParticleForceRegistration::operator=(const ParticleForceRegistration& Other)
{
	p_Particle = Other.p_Particle;
	p_ParticleGen = Other.p_ParticleGen;

	return *this;
}
