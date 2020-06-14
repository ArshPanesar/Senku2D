#include "Collision Detector.h"

bool Senku2D::CollisionDetector::CircleAndCircle(CollisionData* CollData)
{
	//Getting the Shapes
	CircleShape* pCircle1 = (CircleShape*)CollData->_Bodies.RigidBodies[0]->GetShape();
	CircleShape* pCircle2 = (CircleShape*)CollData->_Bodies.RigidBodies[1]->GetShape();

	//Getting Positions
	Vector2 Position1 = CollData->_Bodies.RigidBodies[0]->GetPosition();
	Vector2 Position2 = CollData->_Bodies.RigidBodies[1]->GetPosition();

	//Getting Rotation Matrices
	Matrix2 RotMat1 = CollData->_Bodies.RigidBodies[0]->GetRotationMatrix();
	Matrix2 RotMat2 = CollData->_Bodies.RigidBodies[1]->GetRotationMatrix();

	//Transforming the Circles
	pCircle1->Transform(Position1, RotMat1);
	pCircle2->Transform(Position2, RotMat2);

	//Checking Collision Between the Circles
	//Getting Their Centers
	Vector2 Center1 = pCircle1->GetCenterPosition();
	Vector2 Center2 = pCircle2->GetCenterPosition();
	//Getting The Vector Between the Centers
	Vector2 VectorBetweenCenters = Center1 - Center2;
	//Getting Squared Distance
	Real Dist_Sq = VectorBetweenCenters.SquaredMagnitude();
	//Getting the Squared Radii
	Real RadiusSq1 = Real_Pow(pCircle1->GetRadius(), 2);
	Real RadiusSq2 = Real_Pow(pCircle2->GetRadius(), 2);

	//Checking if the Squared Distance is Less than the Sum of Squared Radii
	if (Dist_Sq < (RadiusSq1 + RadiusSq2))
	{
		//Collision Happened
		//Fill the Contact Data
		Contact* pContact = &CollData->_Contact;
		
		//Contact point
		Vector2 ContactPoint = Center1 + (VectorBetweenCenters * Real_Sqrt(RadiusSq1));
		pContact->ContactPoint = ContactPoint;

		//Contact Normal
		VectorBetweenCenters.Normalize();
		pContact->ContactNormal = VectorBetweenCenters;

		//Penetration
		Real Penetration = Real_Sqrt((RadiusSq1 + RadiusSq2) - Dist_Sq);
		pContact->Penetration = Penetration;

		return true;
	}

	return false;
}

bool Senku2D::CollisionDetector::BoxAndBox(CollisionData* CollData)
{
	//Getting the Box Shapes
	Shape* sBox1 = CollData->_Bodies.RigidBodies[0]->GetShape();
	Shape* sBox2 = CollData->_Bodies.RigidBodies[1]->GetShape();
	BoxShape pBox1 = *(BoxShape*)(sBox1);
	BoxShape pBox2 = *(BoxShape*)(sBox2);

	//Getting Positions and Rotation Matrices
	Vector2 Position1 = CollData->_Bodies.RigidBodies[0]->GetPosition();
	Vector2 Position2 = CollData->_Bodies.RigidBodies[1]->GetPosition();
	Matrix2 RotMat1 = CollData->_Bodies.RigidBodies[0]->GetRotationMatrix();
	Matrix2 RotMat2 = CollData->_Bodies.RigidBodies[1]->GetRotationMatrix();

	//Transforming the Shapes
	pBox1.Transform(Position1, RotMat1);
	pBox2.Transform(Position2, RotMat2);

	//Getting the Vertices
	const Vector2* pVertices1 = pBox1.GetVertices();
	const Vector2* pVertices2 = pBox2.GetVertices();

	//Getting Centers
	const Vector2 Center1 = pBox1.GetCenterPosition();
	const Vector2 Center2 = pBox2.GetCenterPosition();

	//SAT Collision Detection
	//Axis for Both Boxes
	Vector2 Axis1[2];
	Vector2 Axis2[2];

	//Filling Axis For the First Box
	for (unsigned int i = 0; i < 2; ++i)
	{
		//Getting the Vertices
		Vector2 CurrentVertex = pVertices1[i];
		Vector2 NextVertex = pVertices1[i + 1];

		//Getting the Edge
		Vector2 Edge = NextVertex - CurrentVertex;
		Vector2 Normal = Vector2(-Edge.y, Edge.x);
		Normal.Normalize();

		//Adding it to the Axis
		Axis1[i] = Normal;
	}

	//Filling Axis For the Second Box
	for (unsigned int i = 0; i < 2; ++i)
	{
		//Getting the Vertices
		Vector2 CurrentVertex = pVertices2[i];
		Vector2 NextVertex = pVertices2[i + 1];

		//Getting the Edge
		Vector2 Edge = NextVertex - CurrentVertex;
		Vector2 Normal = Vector2(-Edge.y, Edge.x);
		Normal.Normalize();

		//Adding it to the Axis
		Axis2[i] = Normal;
	}

	//Starting Overlap
	Real Overlap = (Real)10;
	//Main Axis of Collision
	Vector2 MainAxis;
	//Contact Point
	Vector2 ContactPoint;

	//Checking for Collision
	//First Box
	for (int i = 0; i < 2; i++)
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
			float o = p1.getOverlap(p2);
			if (o < Overlap)
			{
				Overlap = o;
				MainAxis = Axis;
			}
		}
	}
	//Second Box
	for (int i = 0; i < 2; i++)
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
			float o = p1.getOverlap(p2);
			if (o < Overlap)
			{
				Overlap = o;
				MainAxis = Axis;
			}
		}
	}

	//Collision Happened!
	//Fill the Contact Info
	Contact* pContact = &CollData->_Contact;

	//Contact Point
	pContact->ContactPoint = ContactPoint;

	//Contact Normal
	pContact->ContactNormal = MainAxis;

	//Penetration
	pContact->Penetration = Overlap;

	return true;
}

bool Senku2D::CollisionDetector::BoxAndCircle(CollisionData* CollData)
{
	return false;
}
