#pragma once
#include "Vector2.h"
//Pow Operator
#define Real_Pow powf

namespace Senku2D
{
	//A Particle is Just a Point in Space
	class Particle
	{
	private:
		//Inverse Mass of the Particle
		//We Use Inverse Mass to Prevent Divide by 0 Errors
		//0 Inverse Mass Means Infinite Mass and Vice-Versa
		//I Made it Private Since it is Easy to Confuse Between Mass and Inverse Mass
		//Thus Setters Have been Provided
		Real m_InverseMass;

	public:
		//A Position for the Particle
		Vector2 Position;

		//A Velocity for the Particle
		Vector2 Velocity;

		//An Accelaration for the Particle
		//(Primarily Used for Accelaration Due to Gravity)
		Vector2 Acceleration;

		//Damping(Drag Force: Trying to Stop the Particle from Moving)
		//Damping is Required to Remove the Instability Caused by the Force Integrator
		//Values Will Range from 0-1, 0 Meaning Velocity Will be 0, 1 Meaning Velocity Will Remain the Same
		Real Damping;

		//Force Accumulated to be Applied in the Next Iteration Simulation
		Vector2 ForceAccum;

		//Setting Inverse Mass
		void SetInverseMass(const Real& InvMass);
		//Setting Mass
		void SetMass(const Real& Mass);

		//Integrator
		//Basically Integrates Position and Velocity Using a Timestep
		void Integrate(const Real& Timestep);

	};
}
