#include "Rigid Body.h"

Senku2D::RigidBody::RigidBody()	:
	Angle(0),
	BoundingBox()
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
	Position.AddScaledVector(LinearVelocity, Timestep);
	Angle += AngularVelocity * Timestep;
	
	//Update the Acceleration from the Force
	Vector2 ResultingAcc = LinearAcceleration;
	ResultingAcc.AddScaledVector(ForceAccum, InverseMass);
	//Update Angular Acceleration from Torque
	Real ResultingAngularAcc = AngularAcceleration;
	ResultingAngularAcc += TorqueAccum * ((Real)1 / MomentOfInertia);
	
	//Update Linear Velocity from the Resulting Acceleration
	LinearVelocity.AddScaledVector(ResultingAcc, Timestep);
	//Update the Angular Velocity
	AngularVelocity += ResultingAngularAcc * Timestep;

	//Impose Drag on Particle's Velocity
	LinearVelocity *= Real_Pow(LinearDamping, Timestep);
	AngularVelocity *= Real_Pow(AngularDamping, Timestep);

	//Calculate Rotation Matrix
	CalculateRotationMatrix();

	//Calculate AABB
	CalculateAABB();

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
	TorqueAccum = 0;
}

void Senku2D::RigidBody::AddForce(const Vector2& Force)
{
	ForceAccum += Force;
}

void Senku2D::RigidBody::AddForceToPoint(const Vector2& Force, const Vector2& Point)
{
	//Accumulating Linear Force
	AddForce(Force);
	//Accumulating Torque
	Vector2 Rotated_Point = RotationMat * Point;
	TorqueAccum = Rotated_Point.CrossProduct(Force);
}

void Senku2D::RigidBody::CalculateAABB()
{
	BoundingBox.Position = Position - (BoundingBox.Size / (Real)2);
}

void Senku2D::RigidBody::LocalToWorldCoords(Vector2& Coords)
{
	Coords = Vector2(Coords.x + Position.x, Coords.y + Position.y);
}

void Senku2D::RigidBody::WorldToLocalCoords(Vector2& Coords)
{
	Coords = Vector2(Position.x - Coords.x, Position.y - Coords.y);
}
