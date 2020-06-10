#pragma once
#include "../Particle Collision Processing/Particle Contact.h"

namespace Senku2D
{
	//A Link Between Two Particles
	/*
	This Class will Initiate a Link Between Two Particles, and Will
	Resolve the Link Using the Contact Resolution
	*/
	class IParticleLink
	{
	public:
		//A Pair of Particles to be Linked
		Particle* p_Particles[2];

	protected:
		//The Current Length of the Link
		Real CurrentLength() const;

	public:
		//Filling the Contact Information to the Particle Link
		//This Function will Take a Particle Contact and a Limit which is
		//Basically the Number of Contacts with Other Particles(Zero or One)
		//This Function Will Return a 0 if the Link Was Not Broken, and 1 if it did
		virtual int FillContact(ParticleContact* _PC, const int& Limit) = 0;
	};
}
