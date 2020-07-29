#include "World.h"

void Senku2D::World::IntegrateAllBodies(const Real& Timestep)
{
	//Go Through the List
	for (size_t i = 0; i < m_RigidBodyList.GetSize(); ++i)
	{
		//Integrate Body
		m_RigidBodyList.GetRigidBody(i)->Integrate(Timestep);
	}
}

Senku2D::World::World()	:
	m_RigidBodyList(RigidBodyList::Get()),
	WorldArena(DEFAULT_WORLD_ARENA_POSITION, DEFAULT_WORLD_ARENA_SIZE)
{

}

Senku2D::World::~World()
{
	//Clearing the List
	m_RigidBodyList.Clear();
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

void Senku2D::World::SetWorldArena(const Vector2 & Position, const Vector2 & Size)
{
	//Setting Scaled Position and Size for the World
	WorldArena.Position = Position;
	WorldArena.Size = Size;
	WorldArena.Position -= Vector2(WorldArena.Size * WORLD_ARENA_SCALE_FACTOR);
	WorldArena.Size *= WORLD_ARENA_SCALE_FACTOR;
}

void Senku2D::World::Update(const Real& Timestep, RigidBodyPairList& CollidingPairsList)
{
	//Update All Bodies
	IntegrateAllBodies(Timestep);

	//Collision Detection
	//
	//Final Potential Contact List
	PotentialContactList FinalPCList(POTENTIAL_CONTACT_LIST_LIMIT);
	//
	//Broad Phase
	//Initializing a Quadtree
	Quadtree m_Quadtree(WorldArena.Position, WorldArena.Size, 0);
	//Inserting All Bodies Into the Quadtree
	BroadPhase::InsertBodiesToQuadtree(&m_Quadtree, m_RigidBodyList);
	//
	//Traversing the Body List
	uint8_t FinalPCListIndex = 0;
	//Total Number of Contacts Found
	unsigned int TotalNumOfPotentialContactsFound = 0;
	for (unsigned int i = 0; i < m_RigidBodyList.GetSize(); ++i)
	{
		//Local Potential Contact List For This Rigid Body
		PotentialContactList PCList(LOCAL_POTENTIAL_CONTACT_LIMIT);

		//Querying a Rigid Body from the QuadTree
		unsigned int NumOfPotentialContacts = BroadPhase::QueryNeighboursFromQuadtree(&m_Quadtree, m_RigidBodyList.GetRigidBody(i), &PCList);
		//
		//Local Potential Contacts Generated!
		
		//Continue if No Contacts Were Found
		if (NumOfPotentialContacts == 0)
		{
			continue;
		}
		//Potential Contacts Were Found
		TotalNumOfPotentialContactsFound += NumOfPotentialContacts;

		//Adding the Potential Contacts to the Final List
		for (unsigned int LocalPCListIndex = 0; LocalPCListIndex < PCList.GetLimit(); ++LocalPCListIndex)
		{
			if (FinalPCListIndex >= POTENTIAL_CONTACT_LIST_LIMIT)
			{
				break;
			}

			if (PCList.GetContact(FinalPCListIndex).RigidBodies[0] != nullptr && PCList.GetContact(FinalPCListIndex).RigidBodies[1] != nullptr)
			{
				FinalPCList.GetContact(FinalPCListIndex).RigidBodies[0] = PCList.GetContact(LocalPCListIndex).RigidBodies[0];
				FinalPCList.GetContact(FinalPCListIndex).RigidBodies[1] = PCList.GetContact(LocalPCListIndex).RigidBodies[1];

				++FinalPCListIndex;
			}
		}
	}

	//Clearing the Quadtree
	m_Quadtree.Clear();

	//If There are No Potential Contacts Then Dont Do Anything
	if (TotalNumOfPotentialContactsFound == 0)
	{
		return;
	}
	//
	//Final Potential Contacts Generated!
	//
	//Narrow Phase Collision Detection
	//Primitive List Contact List
	PotentialContactList PrimitiveTestResultList(POTENTIAL_CONTACT_LIST_LIMIT);
	//Generating Resultant List From Final List
	unsigned int PrimitiveTestResult = NarrowPhase::GeneratePrimitiveTestResultsList(&FinalPCList, &PrimitiveTestResultList);
	//Collision Detected List: Shape Test List
	ContactList ContactPairList(MAX_CONTACTS);
	//Generating Shape Result List
	unsigned int NumOfContactsFound = NarrowPhase::GenerateShapeTestResultsList(&PrimitiveTestResultList, &ContactPairList);
	//
	//Collision Detection Completed!
	//
	if (NumOfContactsFound > 0)
	{
		//Now We Have A List of Actual Colliding Pair of Rigid Bodies
		//
		//
		//Resolving the Collision Pairs
		CollisionResolver _CollisionResolver;
		_CollisionResolver.Resolve(&ContactPairList);
		//
		//Copying the Collision Pair List
		CollidingPairsList.CopyFromContactList(ContactPairList);
	}
	//End Of Physics Update
}
