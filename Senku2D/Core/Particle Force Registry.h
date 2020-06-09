#pragma once
#include "Particle Force Generator.h"
#include <vector>

namespace Senku2D
{
	//Maximum Number of Registrations
	const uint16_t MAX_REGISTRATIONS = 1000;

	//A Central Registry for Particles and the Particle Force Generators Acting on them
	class ParticleForceRegistry
	{
	protected:
		//Registration Struct
		//Keeps Track of the Particle and its Particle Force Generator
		struct ParticleForceRegistration
		{
			//The Particle
			Particle* p_Particle;
			//The Force Generator
			IParticleForceGenerator* p_ParticleGen;

			//Equals Operator
			bool operator==(const ParticleForceRegistration& Other);

			//Default Constructor
			ParticleForceRegistration();
			//Copy Constructor
			ParticleForceRegistration(const ParticleForceRegistration& Other);

			//Copy Assignment Operator
			ParticleForceRegistration operator=(const ParticleForceRegistration& Other);
		};

		//The Registry Type
		typedef std::vector<ParticleForceRegistration> Registry;

		//The Registrations
		Registry m_Registrations;
	public:
		//Constructor
		ParticleForceRegistry();

		//Adding a Particle and a Force Generator
		void Add(Particle* _Particle, IParticleForceGenerator* _ForceGen);

		//Removing a Particle and Force Generator
		void Remove(Particle* _Particle, IParticleForceGenerator* _ForceGen);

		//Clears the Registry
		void Clear();

		//Updates All the Particles Through their Registered Force Generators
		void UpdateForces(const Real& Timestep);
	};
}
