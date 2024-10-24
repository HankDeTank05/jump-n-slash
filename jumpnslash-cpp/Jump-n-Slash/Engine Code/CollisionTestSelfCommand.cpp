#include "CollisionTestSelfCommand.h"

#include "CollisionObjectGroup.h"
#include "CollisionObject.h"
#include "CollisionVolume.h"
#include "Math.h"

#include "../Game Code/DebugFlags.h"

CollisionTestSelfCommand::CollisionTestSelfCommand(CollisionObjectGroup* _pGroup,
	CollisionDispatchBase* _pColDispatch, CollisionDispatchBase* _pNoColDispatch)
	: pGroup(_pGroup),
	pColDispatch(_pColDispatch),
	pNoColDispatch(_pNoColDispatch)
{
	// do nothing
}

CollisionTestSelfCommand::~CollisionTestSelfCommand()
{
	delete pNoColDispatch;
	delete pColDispatch;
}

void CollisionTestSelfCommand::Execute()
{
	const CollisionObjectGroup::CollisionObjectList& list = pGroup->GetCollisionObjectList();

	for (auto it1 = list.begin(); it1 != list.end(); it1++)
	{
		// this syntax is stupid, but it works
		// found here: https://cplusplus.com/forum/beginner/13379/
		auto it2 = it1;
		for (++it2; it2 != list.end(); it2++)
		{
			assert(it1 != it2);
			assert((*it1) != (*it2));

			const CollisionVolume& cv1 = (*it1)->GetCollisionVolume();
			const CollisionVolume& cv2 = (*it2)->GetCollisionVolume();

			if (Math::Intersect(cv1, cv2))
			{
				if (DEBUG_COLLISION)
				{
					cv1.DebugView(sf::Color::Red);
					cv2.DebugView(sf::Color::Red);
				}

				pColDispatch->ProcessCallbacks(*it1, *it2);
			}
			else
			{
				if (DEBUG_COLLISION)
				{
					cv1.DebugView(sf::Color::Blue);
					cv2.DebugView(sf::Color::Blue);
				}

				pNoColDispatch->ProcessCallbacks(*it1, *it2);
			}
		}
	}
}
