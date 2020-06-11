#include "Rigid Body.h"

Senku2D::RigidBody::RigidBody()	:
	Angle(0)
{
	//Calculate the Rotation Matrix
	CalculateRotationMatrix();
}

void Senku2D::RigidBody::CalculateRotationMatrix()
{
	RotationMat.Data[0] = Real_Cos(Angle);
	RotationMat.Data[1] = -Real_Sin(Angle);
	RotationMat.Data[2] = Real_Sin(Angle);
	RotationMat.Data[3] = Real_Cos(Angle);
}

void Senku2D::RigidBody::Integrate(const Real& Timestep)
{
	//Update the Linear Position of the Particle
	Position.AddScaledVector(Velocity, Timestep);

	//Update the Acceleration from the Force
	Vector2 ResultingAcc = Acceleration;
	ResultingAcc.AddScaledVector(ForceAccum, InverseMass);

	//Update Linear Velocity from the Resulting Acceleration
	Velocity.AddScaledVector(ResultingAcc, Timestep);

	//Impose Drag on Particle's Velocity
	Velocity *= Real_Pow(LinearDamping, Timestep);

	//Clear the Accumulator
	ClearAccumulators();
}

void Senku2D::RigidBody::SetInverseMass(const Real& InvMass)
{
	InverseMass = InvMass;
}

void Senku2D::RigidBody::SetMass(const Real& Mass)
{
	if (Mass != 0)
	{
		InverseMass = ((Real)1 / Mass);
	}
}

void Senku2D::RigidBody::ClearAccumulators()
{
	ForceAccum.Clear();
	TorqueAccum.Clear();
}
