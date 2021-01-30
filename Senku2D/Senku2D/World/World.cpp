#include "World.h"

void Senku2D::World::IntegrateAllBodies(const Real& Timestep)
{
	//Go Through the List
	for (size_t i = 0; i < m_RigidBodyList.GetDynamicBodyListSize(); ++i)
	{
		//Integrate Body
		m_RigidBodyList.GetRigidBodyFromDynamicList(i)->Integrate(Timestep);
	}
}

Senku2D::World::World()	:
	m_RigidBodyList(),
	FinalPCList(DEFAULT_POTENTIAL_CONTACT_LIST_LIMIT),
	PrimitiveTestResultList(DEFAULT_MAX_CONTACTS),
	ContactPairList(DEFAULT_MAX_CONTACTS)
{

}

Senku2D::World::World(const size_t& PotentialContactsLimit, const size_t& ContactsLimit)	:
	m_RigidBodyList(),
	FinalPCList(PotentialContactsLimit),
	PrimitiveTestResultList(ContactsLimit),
	ContactPairList(ContactsLimit)
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
	//Total Number of Contacts Found
	uint32_t TotalNumOfPotentialContactsFound = 0;
	//

	//Checking Every Body Against the Other
	/*
	size_t NumOfDynamicBodies = m_RigidBodyList.GetDynamicBodyListSize();
	size_t NumOfStaticBodies = m_RigidBodyList.GetStaticBodyListSize();
	size_t NumOfContacts = 0;
	if (NumOfDynamicBodies == 0)
	{
		return;
	}

	for (size_t i = 0; i < NumOfDynamicBodies; ++i)
	{
		for (U8 j = 0; j < NumOfStaticBodies; ++j)
		{
			if (NumOfContacts < FinalPCList.GetLimit())
			{
				FinalPCList.GetContact(NumOfContacts).RigidBodies[0] = m_RigidBodyList.GetRigidBodyFromDynamicList(i);
				FinalPCList.GetContact(NumOfContacts).RigidBodies[1] = m_RigidBodyList.GetRigidBodyFromStaticList(j);
				++NumOfContacts;
			}
			else
			{
				break;
			}
		}
	}
	//
	TotalNumOfPotentialContactsFound = NumOfContacts;

	*/

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
		&FinalPCList, &PrimitiveTestResultList, 0);
	
	//Collision Detected List: Shape Test List
	ContactPairList.Clear();
	//Generating Shape Result List
	unsigned int NumOfContactsFound = NarrowPhase::GenerateShapeTestResultsList(
		&PrimitiveTestResultList, &ContactPairList, 0);
	
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
