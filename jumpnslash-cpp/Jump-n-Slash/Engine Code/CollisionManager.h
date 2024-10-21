#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <iostream>
#include <vector>
#include <list>

#include "CollisionTestPairCommand.h"
#include "CollisionTestSelfCommand.h"
#include "CollisionDispatch.h"

// forward declarations
class CollisionObjectGroup;
class CollisionTestCommand;

class CollisionManager
{
public:
	CollisionManager();
	CollisionManager(const CollisionManager& cm) = delete;
	CollisionManager& operator=(const CollisionManager& cm) = delete;
	virtual ~CollisionManager();

public:
	using JNSTypeID = int;

private:
	static JNSTypeID TypeIDNextNumber; // TODO: set in .cpp

	using CollisionObjectGroupCollection = std::vector<CollisionObjectGroup*>;
	using CollisionTestCommandList = std::list<CollisionTestCommand*>;

public:
	template <typename C>
	JNSTypeID GetTypeID()
	{
		static JNSTypeID typeID = TypeIDNextNumber++;

		SetGroupForTypeID(typeID);

		// TODO: uncomment the next line if you're having trouble with collision detection
		//std::cout << "Type ID: " << typeID << std::endl;
		return typeID;
	}

	template <typename C1, typename C2>
	void SetCollisionPair()
	{
		CollisionObjectGroup* pGroup1 = collObjGroupCollection[GetTypeID<C1>()];
		CollisionObjectGroup* pGroup2 = collObjGroupCollection[GetTypeID<C2>()];

		CollisionDispatch<C1, C2>* pDispatch = new CollisionDispatch<C1, C2>();

		colTestCmdList.push_back(new CollisionTestPairCommand(pGroup1, pGroup2, pDispatch));
	}

	template <typename C>
	void SetCollisionSelf()
	{
		CollisionObjectGroup* pGroup = collObjGroupCollection[GetTypeID<C>()];

		CollisionDispatch<C, C>* pDispatch = new CollisionDispatch<C, C>();

		colTestCmdList.push_back(new CollisionTestSelfCommand(pGroup, pDispatch));
	}

	//template <typename C>
	//void SetCollisionMap(LevelMap* pLevelMap)
	//{
	//	CollisionObjectGroup* pGroup = collObjGroupCollection[GetTypeID<C>()];
	//	colTestCmdList.push_back(new CollisionTestMapCommand(pLevelMap, pGroup));
	//}
	void ComputeData();
	void ProcessCollisions();

	CollisionObjectGroup* GetObjectGroup(JNSTypeID id);

private:
	void SetGroupForTypeID(JNSTypeID id);

public:
	static const JNSTypeID JNSID_UNDEFINED = -1;

private: // member varables
	CollisionObjectGroupCollection collObjGroupCollection;
	CollisionTestCommandList colTestCmdList;
};

#endif