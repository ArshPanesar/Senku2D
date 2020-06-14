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
	return true;
}

bool Senku2D::CollisionDetector::BoxAndCircle(CollisionData* CollData)
{
	return true;
}
