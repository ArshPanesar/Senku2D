#pragma once
#include "Vector2.h"

namespace Senku2D
{
	//A Particle
	/*
	** A Particle Uses the Same Integrator as the Rigid Body but has No Rotation.
	** This Class Can be Used for Particle Effects In-Game and Such.
	*/
	class Particle
	{
	private:
		//Inverse Mass of the Particle
		//We Use Inverse Mass to Prevent Divide by 0 Errors
		//0 Inverse Mass Means Infinite Mass and Vice-Versa
		//I Made it Private Since it is Easy to Confuse Between Mass and Inverse Mass
		//Thus Setters Have been Provided
		Real m_InverseMass;

		//A Position for the Particle
		Vector2 m_Position;

		//A Velocity for the Particle
		Vector2 m_Velocity;

		//An Accelaration for the Particle
		//(Primarily Used for Accelaration Due to Gravity)
		Vector2 m_Acceleration;

		//Damping(Drag Force: Trying to Stop the Particle from Moving)
		//Damping is Required to Remove the Instability Caused by the Force Integrator
		//Values Will Range from 0-1, 0 Meaning Velocity Will be 0, 1 Meaning Velocity Will Remain the Same
		Real m_Damping;

		//Force Accumulated to be Applied in the Next Iteration Simulation
		Vector2 m_ForceAccum;
	public:
		//Default Constructor
		Particle();

		//Setting Inverse Mass
		void SetInverseMass(const Real& InvMass);
		//Setting Mass
		void SetMass(const Real& Mass);
		//Setting Position
		void SetPosition(const Vector2& Position);
		//Setting Velocity
		void SetVelocity(const Vector2& Velocity);
		//Setting Acceleration
		void SetAcceleration(const Vector2& Acc);
		//Setting Damping
		void SetDamping(const Real& Damping);

		//Adding a Force to the Accumulator
		void AddForce(const Vector2& Force);

		//Integrator
		//Basically Integrates Position and Velocity Using a Timestep
		void Integrate(const Real& Timestep);

		//Getters
		const Real GetInverseMass() const;
		const Vector2 GetPosition() const;
		const Vector2 GetVelocity() const;
		const Vector2 GetAcceleration() const;
		const Real GetDamping() const;

		//Clear the Force Accumulator
		void ClearAccumulator();
	};
}
