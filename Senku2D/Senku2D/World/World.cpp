#include "World.h"

void Senku2D::World::IntegrateAllBodies(const Real& Timestep)
{
	//Go Through the List
	const size_t& Size = m_RigidBodyList.GetDynamicBodyListSize();
	for (size_t i = 0; i < Size; ++i)
	{
		//Integrate Body
		m_RigidBodyList.GetRigidBodyFromDynamicList(i)->Integrate(Timestep);
	}
}

Senku2D::World::World()	:
	m_RigidBodyList(),
	FinalPCList(DEFAULT_POTENTIAL_CONTACT_LIST_LIMIT),
	PrimitiveTestResultList(DEFAULT_POTENTIAL_CONTACT_LIST_LIMIT),
	ContactPairList(DEFAULT_MAX_CONTACTS),
	DynamicGrid(),
	StaticGrid(),
	rRebuildStaticGrid(EventInterface::Get().ShouldRedoStaticGrid())
{

}

Senku2D::World::World(const size_t& PotentialContactsLimit, const size_t& ContactsLimit)	:
	m_RigidBodyList(),
	FinalPCList(PotentialContactsLimit),
	PrimitiveTestResultList(ContactsLimit),
	ContactPairList(ContactsLimit),
	DynamicGrid(),
	StaticGrid(),
	rRebuildStaticGrid(EventInterface::Get().ShouldRedoStaticGrid())
{

}

Senku2D::World::~World()
{
	//Clearing the List
	m_RigidBodyList.Clear();
}

void Senku2D::World::SetCellDivisionSize(const Real& CellWidth, const Real& CellHeight)
{
	StaticGrid.SetCellSize(CellWidth, CellHeight);
	DynamicGrid.SetCellSize(CellWidth, CellHeight);

	//Rebuild Static Grid with New Cell Size
	//Clearing the Grid
	StaticGrid.Clear();
	//Inserting Static Body to Respective Hashed Grid
	BroadPhase::InsertStaticBodiesToGrid(&StaticGrid, &m_RigidBodyList);
}

void Senku2D::World::AddBody(RigidBody* rRB)
{
	m_RigidBodyList.Add(rRB);
}

void Senku2D::World::DestroyBody(RigidBody* rRB)
{
	if (!rRB->IsDestroyed())
	{
		rRB->Destroy();
		m_RigidBodyList.Remove(rRB);
	}
}

void Senku2D::World::Update(const Real& Timestep, RigidBodyPairList& CollidingPairsList)
{
	//Timer
	/*
	auto t1 = std::chrono::high_resolution_clock::now();
	auto t2 = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

	PRT(duration);
	*/

	//Update All Bodies
	IntegrateAllBodies(Timestep);
	
	//Clearing the List
	CollidingPairsList.Clear();

	//Collision Detection
	//
	//Final Potential Contact List
	FinalPCList.Clear();
	
	//Broad Phase
	//
	//Clearing the Grid for Current Frame
	DynamicGrid.Clear();
	
	//Inserting Dynamic Bodies to Hashed Grid For this and the Next Frame
	BroadPhase::InsertDynamicBodiesToGrid(&DynamicGrid, &m_RigidBodyList);
	
	//Rebuilding Static Grid if Needed
	if (rRebuildStaticGrid)
	{
		//Clearing the Grid
		StaticGrid.Clear();

		//Inserting Static Body to Respective Hashed Grid
		BroadPhase::InsertStaticBodiesToGrid(&StaticGrid, &m_RigidBodyList);

		EventInterface::Get().SetRedoStaticGrid(false);
	}
	
	//Querying Each Active Cell
	unsigned int TotalNumOfPotentialContactsFound = BroadPhase::QueryDynamicBodiesUsingGrid(&DynamicGrid, &FinalPCList);	
	//Querying Static vs Dynamic
	TotalNumOfPotentialContactsFound += BroadPhase::QueryStaticBodiesUsingGrid(&StaticGrid, &m_RigidBodyList, &FinalPCList, TotalNumOfPotentialContactsFound);
	
	//
	//If There are No Potential Contacts Then Dont Do Anything
	if (TotalNumOfPotentialContactsFound == 0)
	{
		return;
	}
	//

	//Final Potential Contacts Generated!
	//
	//Narrow Phase Collision Detection
	PrimitiveTestResultList.Clear();
	//Generating Resultant List From Final List
	unsigned int PrimitiveTestResult = NarrowPhase::GeneratePrimitiveTestResultsList(
		&FinalPCList, &PrimitiveTestResultList, TotalNumOfPotentialContactsFound);
	
	//Collision Detected List: Shape Test List
	ContactPairList.Clear();
	//Generating Shape Result List
	unsigned int NumOfContactsFound = NarrowPhase::GenerateShapeTestResultsList(
		&PrimitiveTestResultList, &ContactPairList, PrimitiveTestResult);
	
	//Collision Detection Completed!
	//
	if (NumOfContactsFound > 0)
	{
		//Now We Have A List of Actual Colliding Pair of Rigid Bodies
		//Resolving the Collision Pairs
		_CollisionResolver.Resolve(&ContactPairList, Timestep);
		
		//Copying the Collision Pair List
		CollidingPairsList.CopyFromContactList(ContactPairList);
	}
	//End Of Physics Update
}

unsigned int Senku2D::World::RayCast(Ray& QueryRay, RigidBody** BodiesFound, const size_t& Size)
{
	unsigned int NumOfBodies = 0;
	
	//Local List of Rigid Body Pointers
	std::vector<RigidBody*> RBList;
	RBList.reserve(Size * 2);
	
	//Querying
	NumOfBodies = DynamicGrid.QueryRay(QueryRay, RBList);
	NumOfBodies += StaticGrid.QueryRay(QueryRay, RBList);

	if (NumOfBodies == 0)
	{
		return 0;
	}

	//Removing Duplicates
	for (size_t i = 0; i < RBList.size() - 1; ++i)
	{
		if (RBList[i] != nullptr)
		{
			for (size_t j = i + 1; j < RBList.size(); ++j)
			{
				if (RBList[i] == RBList[j])
				{
					RBList[j] = nullptr;
				}
			}
		}
	}

	//Checking Intersection with Ray
	for (size_t i = 0; i < RBList.size(); ++i)
	{
		if (RBList[i] == nullptr)
		{
			continue;
		}

		if (!(CollisionDetector::ShapeAndRayIntersectionTest(RBList[i]->GetShape(),
			&QueryRay, RBList[i]->GetAngle())))
		{
			RBList[i] = nullptr;
		}
	}

	//Sorting (Bubble Sort)
	Real iDist = 0.0f, jDist = 0.0f;
	for (size_t i = 0; i < RBList.size() - 1; ++i)
	{
		if (RBList[i] == nullptr)
		{
			continue;
		}

		//Calculating Distance
		iDist = Vector2(RBList[i]->GetPosition() - QueryRay.PointA).SquaredMagnitude();

		for (size_t j = i + 1; j < RBList.size(); ++j)
		{
			if (RBList[j] == nullptr)
			{
				continue;
			}

			//Calculating Distance
			jDist = Vector2(RBList[j]->GetPosition() - QueryRay.PointA).SquaredMagnitude();

			if (jDist < iDist)
			{
				//Swapping
				RigidBody* Temp = RBList[j];
				RBList[j] = RBList[i];
				RBList[i] = Temp;
			}
		}
	}
	
	//Copying the Sorted List
	NumOfBodies = 0;
	for (size_t i = 0; i < RBList.size(); ++i)
	{
		if (RBList[i] != nullptr)
		{
			BodiesFound[NumOfBodies] = RBList[i];
			++NumOfBodies;

			if (NumOfBodies == Size)
			{
				break;
			}
		}
	}

	return NumOfBodies;
}
