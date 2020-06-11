#pragma once
#include "../Core/Matrix2.h"

namespace Senku2D
{
	//A Rigid Body
	class RigidBody
	{
	public:
		//Inverse Mass of the Rigid Body
		Real InverseMass;

		//Position(In World Coordinates)
		Vector2 Position;

		//Velocity of the Body
		Vector2 Velocity;

		//Acceleration
		Vector2 Acceleration;

		//Angle of Rotation(Or Orientation) in Radians
		Real Angle;

		//A 2x2 Rotation Matrix
		Matrix2 RotationMat;

		//Linear Damping
		Real LinearDamping;
		//Angular Damping
		Real AngularDamping;

		//Accumulators
		Vector2 ForceAccum;
		Vector2 TorqueAccum;
	public:
		//Default Constructor
		RigidBody();

		//Calculate Rotation Matrix
		void CalculateRotationMatrix();

		//Integrating
		void Integrate(const Real& Timestep);

		//Setting Mass
		void SetInverseMass(const Real& InvMass);
		void SetMass(const Real& Mass);

		//Clear Accumulators
		void ClearAccumulators();
	};
}
