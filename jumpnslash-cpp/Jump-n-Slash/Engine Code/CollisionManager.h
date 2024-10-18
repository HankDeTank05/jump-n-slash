#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <iostream>
#include <vector>
#include <list>

#include "CollisionTestPairCommand.h"
#include "CollisionTestSelfCommand.h"

// forward declarations
class CollisionGroup;
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

	using CollisionGroupCollection = std::vector<CollisionGroup*>;
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
		CollisionGroup* pGroup1 = collisionGroupCollection[GetTypeID<C1>()];
		CollisionGroup* pGroup2 = collisionGroupCollection[GetTypeID<C2>()];

		CollisionDispatch<C1, C2>* pDispatch = new CollisionDispatch<C1, C2>();

		colTestCmdList.push_back(new CollisionTestPairCommand(pGroup1, pGroup2, pDispatch));
	}

	template <typename C>
	void SetCollisionSelf()
	{
		CollisionGroup* pGroup = collisionGroupCollection[GetTypeID<C>()];

		CollisionDispatch<C, C>* pDispatch = new CollisionDispatch<C, C>();

		colTestCmdList.push_back(new CollisionTestSelfCommand(pGroup, pDispatch));
	}

	//template <typename C>
	//void SetCollisionMap(LevelMap* pLevelMap)
	//{
	//	CollisionGroup* pGroup = collisionGroupCollection[GetTypeID<C>()];
	//	colTestCmdList.push_back(new CollisionTestMapCommand(pLevelMap, pGroup));
	//}
	void ComputeData();
	void ProcessCollisions();

	CollisionGroup* GetCollisionGroup();

private:
	void SetGroupForTypeID(JNSTypeID id);

public:
	static const JNSTypeID JNSID_UNDEFINED = -1;

private: // member varables
	CollisionGroupCollection collisionGroupCollection;
	CollisionTestCommandList colTestCmdList;
};

#endif