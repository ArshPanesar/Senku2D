#pragma once
#include "../Core/Matrix2.h"
#include "AABB.h"
#include "Shapes/Shape.h"
#include "MOI Calculation.h"
#include "../World/Event Interface.h"
#include "Collision Processing/Collision Filters.h"

namespace Senku2D
{
	//Body Type(Dynamic By Default)
	enum class BodyType
	{
		STATIC,
		DYNAMIC
	};

	//A Rigid Body
	class RigidBody
	{
	private:
		//Inverse Mass of the Rigid Body
		Real m_InverseMass;

		//Position(In World Coordinates)
		Vector2 m_Position;

		//Linear Velocity of the Body
		Vector2 m_LinearVelocity;
		//Angular Velocity of the Body
		Real m_AngularVelocity;

		//Linear Acceleration
		Vector2 m_LinearAcceleration;
		//Angular Acceleration
		Real m_AngularAcceleration;

		//Angle of Rotation(Or Orientation) in Radians
		Real m_Angle;

		//A 2x2 Rotation Matrix
		Matrix2 m_RotationMat;

		//Linear Damping
		Real m_LinearDamping;
		//Angular Damping
		Real m_AngularDamping;

		//Inertia of the Rigid Body
		Real m_MomentOfInertia;

		//Accumulators
		Vector2 m_ForceAccum;
		Real m_TorqueAccum;

		//Bounding Box
		AABB m_BoundingBox;

		//Shape
		Shape* m_Shape;

		//Void Pointer to Hold the User Data
		void* m_VoidPointerUserData;

		//Body Type
		BodyType m_BodyType;

		//Restitution
		Real m_Restitution;

		//Filters
		Filters m_Filters;
	public:
		//Default Constructor
		RigidBody();
		
		//Destructor
		~RigidBody();

		//Integrating
		void Integrate(const Real& Timestep);
		
		//Setters
		//Setting Mass
		void SetInverseMass(const Real& InvMass);
		void SetMass(const Real& Mass);
		//Setting Position
		void SetPosition(const Vector2& Position);
		//Setting Linear Velocity
		void SetLinearVelocity(const Vector2& Velocity);
		//Setting Angular Velocity
		void SetAngularVelocity(const Real& Velocity);
		//Setting Linear Acceleration
		void SetLinearAcceleration(const Vector2& Acc);
		//Setting Angular Acceleration
		void SetAngularAcceleration(const Real& Acc);
		//Setting Angle In Radians
		void SetAngle(const Real& Angle);
		//Setting Linear Damping
		void SetLinearDamping(const Real& LD);
		//Setting Angular Damping
		void SetAngularDamping(const Real& AD);
		//Setting Moment of Inertia
		void SetMomentOfInertia(const Real& MOI);
		//Setting the Shape
		void SetShape(Shape* _Shape);
		//Setting BodyType
		void SetBodyType(const BodyType& BT);
		//Setting Restitution
		void SetRestitution(const Real& Restitution);
		//Setting Collision Filters
		void SetCollisionFilters(const Filters& CollisionFilters);

		//Clear Accumulators
		void ClearAccumulators();

		//Adding Force to Center
		void AddForce(const Vector2& Force);
		//Adding Force to a Point in Local Space (Where Origin is Center of Body)
		void AddForceToPoint(const Vector2& Force, const Vector2& Point);

		//Overlaps Some AABB
		bool Overlaps(const AABB& _Rect);

		//Getters
		const Real GetInverseMass() const;
		const Vector2 GetPosition() const;
		const Vector2 GetLinearVelocity() const;
		const Real GetAngularVelocity() const;
		const Vector2 GetLinearAcceleration() const;
		const Real GetAngularAcceleration () const;
		const Real GetAngle() const;
		const Real GetLinearDamping() const;
		const Real GetAngularDamping() const;
		const Real GetMomentOfInertia() const;
		const AABB GetAABB() const;
		const Matrix2 GetRotationMatrix() const;
		Shape* GetShape();
		const BodyType GetBodyType() const;
		const Real GetRestitution() const;
		const Filters GetCollisionFilters() const;
		
		//Transforming Coordinates
		//Local to World Coordinates
		void LocalToWorldCoords(Vector2& Coords);
		//World to Local Coords
		void WorldToLocalCoords(Vector2& Coords);

		//Setting User Data
		void SetUserData(void* Data);

		//Getting User Data
		void* GetUserData();
	};
}
