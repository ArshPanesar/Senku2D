#include "Collision Detector.h"

bool Senku2D::CollisionDetector::CircleAndCircle(PotentialRigidBodyContact* _Contact, CollisionData* CollData)
{
	//Getting the Shapes
	CircleShape* pCircle1 = (CircleShape*)_Contact->RigidBodies[0]->GetShape();
	CircleShape* pCircle2 = (CircleShape*)_Contact->RigidBodies[1]->GetShape();

	//Getting Positions
	Vector2 Position1 = _Contact->RigidBodies[0]->GetPosition();
	Vector2 Position2 = _Contact->RigidBodies[1]->GetPosition();

	//Checking Collision Between the Circles
	//Getting Their Centers
	Vector2 Center1 = pCircle1->GetCenterPosition();
	Vector2 Center2 = pCircle2->GetCenterPosition();
	//Getting The Vector Between the Centers
	Vector2 VectorBetweenCenters = Center1 - Center2;
	//Getting Squared Distance
	Real Dist = VectorBetweenCenters.Magnitude();
	//Getting the Squared Radii
	Real Radius1 = pCircle1->GetRadius();
	Real Radius2 = pCircle2->GetRadius();

	//Checking if the Squared Distance is Less than the Sum of Squared Radii
	if (Dist < (Radius1 + Radius2))
	{
		//Collision Happened
		//Fill the Contact Data
		Contact* pContact = &CollData->_Contact;
		
		//Contact Normal
		VectorBetweenCenters.Normalize();
		pContact->ContactNormal = VectorBetweenCenters;

		//Penetration
		Real Penetration = (Radius1 + Radius2) - Dist;
		pContact->Penetration = Penetration;

		//Fill Contact
		CollData->_Bodies = *_Contact;

		return true;
	}

	return false;
}

bool Senku2D::CollisionDetector::BoxAndBox(PotentialRigidBodyContact* _Contact, CollisionData* CollData)
{
	//Getting the Box Shapes
	Shape* sBox1 = _Contact->RigidBodies[0]->GetShape();
	Shape* sBox2 = _Contact->RigidBodies[1]->GetShape();
	BoxShape& pBox1 = *(BoxShape*)(sBox1);
	BoxShape& pBox2 = *(BoxShape*)(sBox2);

	//Getting Positions and Rotation Matrices
	Vector2 Position1 = _Contact->RigidBodies[0]->GetPosition();
	Vector2 Position2 = _Contact->RigidBodies[1]->GetPosition();
	
	//Getting the Vertices
	const Vector2* pVertices1 = pBox1.GetVertices();
	const Vector2* pVertices2 = pBox2.GetVertices();

	//Getting Centers
	const Vector2 Center1 = pBox1.GetCenterPosition();
	const Vector2 Center2 = pBox2.GetCenterPosition();

	//SAT Collision Detection
	//Axis for Both Boxes
	Vector2 Axis1[4];
	Vector2 Axis2[4];

	//Filling Axis For the First Box
	for (unsigned int i = 0; i < 4; ++i)
	{
		//Getting the Vertices
		Vector2 CurrentVertex = pVertices1[i];
		Vector2 NextVertex = pVertices1[i == 3 ? 0 : i + 1];

		//Getting the Edge
		Vector2 Edge = NextVertex - CurrentVertex;
		Vector2 Normal = Vector2(-Edge.y, Edge.x);
		Normal.Normalize();

		//Adding it to the Axis
		Axis1[i] = Normal;
	}

	//Filling Axis For the Second Box
	for (unsigned int i = 0; i < 4; ++i)
	{
		//Getting the Vertices
		Vector2 CurrentVertex = pVertices2[i];
		Vector2 NextVertex = pVertices2[i == 3 ? 0 : i + 1];

		//Getting the Edge
		Vector2 Edge = NextVertex - CurrentVertex;
		Vector2 Normal = Vector2(-Edge.y, Edge.x);
		Normal.Normalize();
		
		//Adding it to the Axis
		Axis2[i] = Normal;
	}

	//Correcting the Main Axis
	Vector2 VectorBetweenCenters = Position1 - Position2;
	//Starting Overlap
	Real Overlap = VectorBetweenCenters.SquaredMagnitude();
	//Main Axis of Collision
	Vector2 MainAxis;
	//Contact Point
	Vector2 ContactPoint;

	//Checking for Collision
	//First Box
	for (int i = 0; i < 4; i++)
	{
		Vector2 Axis = Axis1[i];
		// project both shapes onto the axis
		SAT::Projection p1 = SAT::project(Axis, pVertices1, ContactPoint);
		SAT::Projection p2 = SAT::project(Axis, pVertices2, ContactPoint);

		// do the projections overlap?
		if (!p1.overlaps(p2))
		{
			// then we can guarantee that the shapes do not overlap
			return false;
		}
		else
		{
			Real o = p1.getOverlap(p2);
			if (o < Overlap)
			{
				Overlap = o;
				MainAxis = Axis;
			}
		}
	}
	//Second Box
	for (int i = 0; i < 4; i++)
	{
		Vector2 Axis = Axis2[i];
		// project both shapes onto the axis
		SAT::Projection p1 = SAT::project(Axis, pVertices1, ContactPoint);
		SAT::Projection p2 = SAT::project(Axis, pVertices2, ContactPoint);

		// do the projections overlap?
		if (!p1.overlaps(p2))
		{
			// then we can guarantee that the shapes do not overlap
			return false;
		}
		else
		{
			Real o = p1.getOverlap(p2);
			if (o < Overlap)
			{
				Overlap = o;
				MainAxis = Axis;
			}
		}
	}

	//Collision Happened!
	//Fill Contact
	CollData->_Bodies = *_Contact;

	//Fill the Contact Info
	Contact* pContact = &CollData->_Contact;

	if (VectorBetweenCenters.DotProduct(MainAxis) < (Real)0)
	{
		MainAxis = MainAxis * -1;
	}

	//Contact Normal
	pContact->ContactNormal = MainAxis;

	//Penetration
	pContact->Penetration = Overlap;
	
	return true;
}

bool Senku2D::CollisionDetector::BoxAndCircle(PotentialRigidBodyContact* _Contact, CollisionData* CollData)
{
	const BoxShape* Box = nullptr;
	const CircleShape* Circle = nullptr;
	Real Angle;

	if (_Contact->RigidBodies[0]->GetShape()->GetShapeType() == ShapeType::CIRCLE)
	{
		Circle = (CircleShape*)_Contact->RigidBodies[0]->GetShape();
		Box = (BoxShape*)_Contact->RigidBodies[1]->GetShape();
		Angle = _Contact->RigidBodies[1]->GetAngle();
	}
	else
	{
		Circle = (CircleShape*)_Contact->RigidBodies[1]->GetShape();
		Box = (BoxShape*)_Contact->RigidBodies[0]->GetShape();
		Angle = _Contact->RigidBodies[0]->GetAngle();
	}

	//Calculate Rotation Matrix (In Negative Angles)
	Matrix2 RotationMat;
	RotationMat.Data[0] = Real_Cos(-Angle);
	RotationMat.Data[1] = -Real_Sin(-Angle);
	RotationMat.Data[2] = Real_Sin(-Angle);
	RotationMat.Data[3] = Real_Cos(-Angle);

	//Converting Circle Center's World Coordinates to the Box's Local Coordinates
	Vector2 BoxCenter = Box->GetCenterPosition();
	Vector2 CircleCenter = (RotationMat * (Circle->GetCenterPosition() - BoxCenter)) + BoxCenter;
	
	//Closest Point on Rectangle From the Circle's Center
	Vector2 ClosestPoint;
	
	if (CircleCenter.x < (BoxCenter.x - Box->GetHalfWidth()))
	{
		ClosestPoint.x = (BoxCenter.x - Box->GetHalfWidth());
	}
	else if (CircleCenter.x > ((BoxCenter.x + Box->GetHalfWidth())))
	{
		ClosestPoint.x = (BoxCenter.x + Box->GetHalfWidth());
	}
	else
	{
		ClosestPoint.x = CircleCenter.x;
	}

	if (CircleCenter.y < (BoxCenter.y - Box->GetHalfHeight()))
	{
		ClosestPoint.y = BoxCenter.y - Box->GetHalfHeight();
	}
	else if (CircleCenter.y > (BoxCenter.y + Box->GetHalfHeight()))
	{
		ClosestPoint.y = (BoxCenter.y + Box->GetHalfHeight());
	}
	else
	{
		ClosestPoint.y = CircleCenter.y;
	}

	Real Dist = Vector2(CircleCenter - ClosestPoint).Magnitude();
	
	if (Dist > Circle->GetRadius())
	{
		return false;
	}
	
	//Bodies
	CollData->_Bodies.RigidBodies[0] = _Contact->RigidBodies[0];
	CollData->_Bodies.RigidBodies[1] = _Contact->RigidBodies[1];

	//Penetration
	CollData->_Contact.Penetration = Circle->GetRadius() - Dist;
	//Contact Normal
	RotationMat.Invert();
	CollData->_Contact.ContactNormal = RotationMat * Vector2(CircleCenter - ClosestPoint);
	CollData->_Contact.ContactNormal.Normalize();
	
	return true;
}

bool Senku2D::CollisionDetector::ShapeAndRayIntersectionTest(Shape* p_Shape, Ray* p_Ray, const Real& Angle)
{
	switch (p_Shape->GetShapeType())
	{
	case ShapeType::BOX:
		return BoxAndRay((BoxShape*)p_Shape, p_Ray, Angle);
	case ShapeType::CIRCLE:
		return CircleAndRay((CircleShape*)p_Shape, p_Ray);
	}

	return false;
}

bool Senku2D::CollisionDetector::CircleAndPoint(CircleShape* p_Circle, Vector2* p_Point)
{
	//Getting Distance Between Center and Point
	Vector2 DistBetweenCenterAndPoint = p_Circle->GetCenterPosition() - (*p_Point);

	if (DistBetweenCenterAndPoint.SquaredMagnitude() <
		(p_Circle->GetRadius() * p_Circle->GetRadius()))
	{
		return true;
	}

	return false;
}

bool Senku2D::CollisionDetector::CircleAndRay(CircleShape* p_Circle, Ray* p_Ray)
{
	//Getting End Points
	Vector2& PointA = p_Ray->PointA;
	Vector2& PointB = p_Ray->PointB;

	//Checking Corners
	if (CircleAndPoint(p_Circle, &PointA) || CircleAndPoint(p_Circle, &PointB))
	{
		return true;
	}

	//Getting Vector From Closest End Point
	Vector2 CenterToClosestPoint = p_Circle->GetCenterPosition() - PointA;
	Vector2 ClosestPoint = PointA;
	Real Direction = 1;
	if (Vector2(p_Circle->GetCenterPosition() - PointB).SquaredMagnitude()
		< CenterToClosestPoint.SquaredMagnitude())
	{
		CenterToClosestPoint = p_Circle->GetCenterPosition() - PointB;
		ClosestPoint = PointB;
		Direction = -1;
	}

	//Angle with Ray's Direction Should Not Be Greater than 90 Degrees
	if (CenterToClosestPoint.DotProduct(p_Ray->GetDirection() * Direction) < 0)
	{
		return false;
	}

	//Projecting Vector CenterToClosestPoint to Ray's Direction to Get the Projection Point
	Vector2 ProjectedPoint = ClosestPoint + 
		(p_Ray->GetDirection() * Direction * (CenterToClosestPoint.DotProduct(p_Ray->GetDirection() * Direction) /
			(p_Ray->GetDirection().SquaredMagnitude())));
	
	if (CircleAndPoint(p_Circle, &ProjectedPoint))
	{
		return true;
	}

	return false;
}

bool Senku2D::CollisionDetector::BoxAndPoint(BoxShape* p_Box, Vector2* p_Point, const Real& BoxAngle)
{
	//Rotation Matrix
	Matrix2 RotationMat;
	RotationMat.Data[0] = Real_Cos(BoxAngle);
	RotationMat.Data[1] = -Real_Sin(BoxAngle);
	RotationMat.Data[2] = Real_Sin(BoxAngle);
	RotationMat.Data[3] = Real_Cos(BoxAngle);

	//Rotating The Point
	Vector2 NewPoint = RotationMat * (*p_Point - p_Box->GetCenterPosition()) + p_Box->GetCenterPosition();

	//Checking Intersection
	Vector2 Position(p_Box->GetCenterPosition().x - p_Box->GetHalfWidth(), p_Box->GetCenterPosition().y - p_Box->GetHalfHeight());
	Vector2 Size(p_Box->GetHalfWidth() * 2, p_Box->GetHalfHeight() * 2);
	//
	if (Position.x < (NewPoint.x)
		&& (Position.x + Size.x) > NewPoint.x
		&& Position.y < (NewPoint.y)
		&& (Position.y + Size.y) > NewPoint.y)
	{
		return true;
	}

	return false;
}

bool Senku2D::CollisionDetector::BoxAndRay(BoxShape* p_Box, Ray* p_Ray, const Real& BoxAngle)
{
	//Checking Corners
	if (BoxAndPoint(p_Box, &p_Ray->PointA, BoxAngle) ||
		BoxAndPoint(p_Box, &p_Ray->PointB, BoxAngle))
	{
		return true;
	}

	//Getting Vector From Closest End Point
	Vector2 CenterToClosestPoint = p_Box->GetCenterPosition() - p_Ray->PointA;
	Vector2 ClosestPoint = p_Ray->PointA;
	Real Direction = 1;
	if (Vector2(p_Box->GetCenterPosition() - p_Ray->PointB).SquaredMagnitude()
		< CenterToClosestPoint.SquaredMagnitude())
	{
		CenterToClosestPoint = p_Box->GetCenterPosition() - p_Ray->PointB;
		ClosestPoint = p_Ray->PointB;
		Direction = -1;
	}

	//Angle with Ray's Direction Should Not Be Greater than 90 Degrees
	if (CenterToClosestPoint.DotProduct(p_Ray->GetDirection() * Direction) < 0)
	{
		return false;
	}

	//Projecting Vector CenterToClosestVertex to Ray's Direction to Get the Projection Point
	for (unsigned int i = 0; i < 4; ++i)
	{
		Vector2 CornerToClosestVertex = p_Box->GetVertex(i) - ClosestPoint;
		Vector2 ProjectedPoint = ClosestPoint +
			(p_Ray->GetDirection() * Direction * (CornerToClosestVertex.DotProduct(p_Ray->GetDirection() * Direction) /
				(p_Ray->GetDirection().SquaredMagnitude())));

		if (BoxAndPoint(p_Box, &ProjectedPoint, -BoxAngle))
		{
			return true;
		}
	}

	return false;
}
