#include "Rigid Body.h"

using namespace Senku2D;

Senku2D::RigidBody::RigidBody()	:
	m_InverseMass(1),
	m_Position(),
	m_LinearVelocity(),
	m_AngularVelocity(0),
	m_LinearAcceleration(),
	m_AngularAcceleration(0),
	m_Angle(0),
	m_RotationMat(),
	m_LinearDamping(0.99f),
	m_AngularDamping(0.75f),
	m_MomentOfInertia((Real)100),
	m_ForceAccum(),
	m_TorqueAccum(0),
	m_BoundingBox(),
	m_Shape(nullptr),
	m_IsDestroyed(false),
	m_VoidPointerUserData(nullptr),
	m_BodyType(BodyType::DYNAMIC),
	m_Restitution(0.1f)
{
	//Calculate the Rotation Matrix
	m_RotationMat.Data[0] = Real_Cos(m_Angle);
	m_RotationMat.Data[1] = -Real_Sin(m_Angle);
	m_RotationMat.Data[2] = Real_Sin(m_Angle);
	m_RotationMat.Data[3] = Real_Cos(m_Angle);

	//Set AABB Position and Size
	m_BoundingBox.Position = m_Position;
	m_BoundingBox.Size = Vector2(1.0f, 1.0f);
}

Senku2D::RigidBody::~RigidBody()
{
	//Removing from the List if Not Already Destroyed
	if (!m_IsDestroyed)
	{
		Destroy();
	}
}

void Senku2D::RigidBody::Integrate(const Real& Timestep)
{
	//Update the Linear Position of the Particle
	m_Position.AddScaledVector(m_LinearVelocity, Timestep);
	m_Position.AddScaledVector(m_LinearAcceleration, Timestep * Timestep * 0.5f);

	//Update the Acceleration from the Force
	Vector2 ResultingAcc = m_LinearAcceleration;
	ResultingAcc.AddScaledVector(m_ForceAccum, m_InverseMass);

	//Update Linear Velocity from the Resulting Acceleration
	m_LinearVelocity.AddScaledVector(ResultingAcc, Timestep * 0.5f);
	
	//Calculating Angle
	m_Angle += m_AngularVelocity * Timestep;
	
	//Update Angular Acceleration from Torque
	Real ResultingAngularAcc = m_AngularAcceleration;
	ResultingAngularAcc += m_TorqueAccum / m_MomentOfInertia;
	
	//Update the Angular Velocity
	m_AngularVelocity += ResultingAngularAcc * Timestep;

	//Impose Drag on Particle's Velocity
	m_LinearVelocity *= Real_Pow(m_LinearDamping, Timestep);
	m_AngularVelocity *= Real_Pow(m_AngularDamping, Timestep);

	//Calculate Rotation Matrix
	m_RotationMat.Data[0] = Real_Cos(m_Angle);
	m_RotationMat.Data[1] = -Real_Sin(m_Angle);
	m_RotationMat.Data[2] = Real_Sin(m_Angle);
	m_RotationMat.Data[3] = Real_Cos(m_Angle);
	
	//Transform Shape
	m_Shape->Transform(m_Position, m_RotationMat);
	
	//Setting AABB Position
	m_BoundingBox = AABB::CalculateForShape(m_Shape);

	//Clear the Accumulator
	ClearAccumulators();
}


void Senku2D::RigidBody::SetInverseMass(const Real& InvMass)
{
	m_InverseMass = InvMass;
}

void Senku2D::RigidBody::SetMass(const Real& Mass)
{
	if (Mass != 0)
	{
		m_InverseMass = ((Real)1 / Mass);
	}
	else
	{
		m_InverseMass = 0;
	}
}

void Senku2D::RigidBody::SetPosition(const Vector2& Position)
{
	Vector2 ChangeInPosition = m_Position - Position;
	m_Position = Position;
	
	//Resetting Static Grid Incase of Static Body
	if (m_BodyType == BodyType::STATIC && (ChangeInPosition.SquaredMagnitude() > 0))
	{
		//Transform Shape
		if (m_Shape != nullptr)
		{
			m_Shape->Transform(m_Position, m_RotationMat);

			//Setting AABB Position
			m_BoundingBox = AABB::CalculateForShape(m_Shape);
		}

		//Redo Static Grid
		EventInterface::Get().SetRedoStaticGrid(true);
	}
}

void Senku2D::RigidBody::SetLinearVelocity(const Vector2& Velocity)
{
	m_LinearVelocity = Velocity;
}

void Senku2D::RigidBody::SetAngularVelocity(const Real& Velocity)
{
	m_AngularVelocity = Velocity;
}

void Senku2D::RigidBody::SetLinearAcceleration(const Vector2& Acc)
{
	m_LinearAcceleration = Acc;
}

void Senku2D::RigidBody::SetAngularAcceleration(const Real& Acc)
{
	m_AngularAcceleration = Acc;
}

void Senku2D::RigidBody::SetAngle(const Real& Angle)
{
	m_Angle = Angle;
}

void Senku2D::RigidBody::SetLinearDamping(const Real& LD)
{
	m_LinearDamping = LD;
}

void Senku2D::RigidBody::SetAngularDamping(const Real& AD)
{
	m_AngularDamping = AD;
}

void Senku2D::RigidBody::SetMomentOfInertia(const Real& MOI)
{
	m_MomentOfInertia = MOI;
}

void Senku2D::RigidBody::SetShape(Shape* _Shape)
{
	//Setting the Shape
	m_Shape = _Shape;
	//Setting Center Position
	m_Shape->Transform(m_Position, m_RotationMat);

	//Setting AABB Position
	m_BoundingBox = AABB::CalculateForShape(m_Shape);

	//Calculating Moment of Inertia
	m_MomentOfInertia = MOICalculation::Calculate(m_Shape);
}

void Senku2D::RigidBody::SetBodyType(const BodyType& BT)
{
	m_BodyType = BT;
}

void Senku2D::RigidBody::SetRestitution(const Real& Restitution)
{
	m_Restitution = Restitution;
}

void Senku2D::RigidBody::SetCollisionFilters(const Filters& CollisionFilters)
{
	m_Filters.CategoryBits = CollisionFilters.CategoryBits;
	m_Filters.MaskBits = CollisionFilters.MaskBits;
}

void Senku2D::RigidBody::Destroy()
{
	//Body Will Not be Updated Anymore
	m_IsDestroyed = true;
}

void Senku2D::RigidBody::ClearAccumulators()
{
	m_ForceAccum.Clear();
	m_TorqueAccum = 0;
}

void Senku2D::RigidBody::AddForce(const Vector2& Force)
{
	m_ForceAccum += Force;
}

void Senku2D::RigidBody::AddForceToPoint(const Vector2& Force, const Vector2& Point)
{
	//Accumulating Linear Force
	AddForce(Force);
	//Accumulating Torque
	m_TorqueAccum = Point.CrossProduct(Force);
}

bool Senku2D::RigidBody::Overlaps(const AABB& _Rect)
{
	if (m_BoundingBox.Overlaps(_Rect))
	{
		return true;
	}

	return false;
}

const Real Senku2D::RigidBody::GetInverseMass() const
{
	return m_InverseMass;
}

const Vector2 Senku2D::RigidBody::GetPosition() const
{
	return m_Position;
}

const Vector2 Senku2D::RigidBody::GetLinearVelocity() const
{
	return m_LinearVelocity;
}

const Real Senku2D::RigidBody::GetAngularVelocity() const
{
	return m_AngularVelocity;
}

const Vector2 Senku2D::RigidBody::GetLinearAcceleration() const
{
	return m_LinearAcceleration;
}

const Real Senku2D::RigidBody::GetAngularAcceleration() const
{
	return m_AngularAcceleration;
}

const Real Senku2D::RigidBody::GetAngle() const
{
	return m_Angle;
}

const Real Senku2D::RigidBody::GetLinearDamping() const
{
	return m_LinearDamping;
}

const Real Senku2D::RigidBody::GetAngularDamping() const
{
	return m_AngularDamping;
}

const Real Senku2D::RigidBody::GetMomentOfInertia() const
{
	return m_MomentOfInertia;
}

const AABB Senku2D::RigidBody::GetAABB() const
{
	return m_BoundingBox;
}

const Matrix2 Senku2D::RigidBody::GetRotationMatrix() const
{
	return m_RotationMat;
}

Shape* Senku2D::RigidBody::GetShape()
{
	return m_Shape;
}

const bool Senku2D::RigidBody::IsDestroyed() const
{
	return m_IsDestroyed;
}

const BodyType Senku2D::RigidBody::GetBodyType() const
{
	return m_BodyType;
}

const Real Senku2D::RigidBody::GetRestitution() const
{
	return m_Restitution;
}

const Filters Senku2D::RigidBody::GetCollisionFilters() const
{
	return m_Filters;
}

void Senku2D::RigidBody::LocalToWorldCoords(Vector2& Coords)
{
	Coords = Vector2(Coords.x + m_Position.x, Coords.y + m_Position.y);
}

void Senku2D::RigidBody::WorldToLocalCoords(Vector2& Coords)
{
	Coords = Vector2(m_Position.x - Coords.x, m_Position.y - Coords.y);
}

void Senku2D::RigidBody::SetUserData(void* Data)
{
	m_VoidPointerUserData = Data;
}

void* Senku2D::RigidBody::GetUserData()
{
	return m_VoidPointerUserData;
}
