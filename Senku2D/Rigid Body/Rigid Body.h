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

		//Linear Velocity of the Body
		Vector2 LinearVelocity;
		Real AngularVelocity;

		//Acceleration
		Vector2 LinearAcceleration;
		Real AngularAcceleration;

		//Angle of Rotation(Or Orientation) in Radians
		Real Angle;

		//A 2x2 Rotation Matrix
		Matrix2 RotationMat;

		//Linear Damping
		Real LinearDamping;
		//Angular Damping
		Real AngularDamping;

		//Inertia of the Rigid Body
		Real MomentOfInertia;

		//Accumulators
		Vector2 ForceAccum;
		Real TorqueAccum;
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

		//Adding Force to Center
		void AddForce(const Vector2& Force);
		//Adding Force to a Point(Supply Point in Local Space)
		void AddForceToPoint(const Vector2& Force, const Vector2& Point);

		//Transforming Coordinates
		//Local to World Coordinates
		void LocalToWorldCoords(Vector2& Coords);
		//World to Local Coords
		void WorldToLocalCoords(Vector2& Coords);
	};
}
