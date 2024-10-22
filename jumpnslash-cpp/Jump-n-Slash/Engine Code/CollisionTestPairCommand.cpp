#include "CollisionTestPairCommand.h"

#include "CollisionObjectGroup.h"
#include "CollisionObject.h"
#include "CollisionVolume.h"
#include "Math.h"

#include "../Game Code/DebugFlags.h"

CollisionTestPairCommand::CollisionTestPairCommand(CollisionObjectGroup* _pGroup1,
	CollisionObjectGroup* _pGroup2, CollisionDispatchBase* _pDispatch)
	: pGroup1(_pGroup1),
	pGroup2(_pGroup2),
	pDispatch(_pDispatch)
{
	// do nothing?
}

CollisionTestPairCommand::~CollisionTestPairCommand()
{
	delete pDispatch;
}

void CollisionTestPairCommand::Execute()
{
	CollisionObjectGroup::CollisionObjectList list1 = pGroup1->GetCollisionObjectList();
	CollisionObjectGroup::CollisionObjectList list2 = pGroup2->GetCollisionObjectList();

	// TODO: add tiered collision testing

	for (CollisionObjectGroup::CollisionObjectList::iterator it1 = list1.begin(); it1 != list1.end(); it1++)
	{
		for (CollisionObjectGroup::CollisionObjectList::iterator it2 = list2.begin(); it2 != list2.end(); it2++)
		{
			const CollisionVolume& cv1 = (*it1)->GetCollisionVolume();
			const CollisionVolume& cv2 = (*it2)->GetCollisionVolume();

			if (Math::Intersect(cv1, cv2) == true)
			{
				if (DEBUG_COLLISION)
				{
					cv1.DebugView(sf::Color::Red);
					cv2.DebugView(sf::Color::Red);
				}

				pDispatch->ProcessCallbacks(*it1, *it2);
			}
			else
			{
				if (DEBUG_COLLISION)
				{
					cv1.DebugView(sf::Color::Blue);
					cv2.DebugView(sf::Color::Blue);
				}
			}
		}
	}
}
