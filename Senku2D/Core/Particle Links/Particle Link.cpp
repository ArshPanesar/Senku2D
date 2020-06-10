#include "Particle Link.h"

Senku2D::Real Senku2D::IParticleLink::CurrentLength() const
{
	//Getting the Relative Position
	Vector2 RelativePosition = p_Particles[0]->Position - p_Particles[1]->Position;
	return RelativePosition.Magnitude();
}
