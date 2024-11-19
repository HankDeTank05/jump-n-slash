#ifndef COLLISION_OBJECT_H
#define COLLISION_OBJECT_H

// library includes
#include <SFML/Graphics/Sprite.hpp>

// engine includes
#include "CollisionManager.h"
#include "CollisionObjectGroup.h"
#include "RegistrationState.h"
#include "SceneAttorney.h"
#include "SceneManager.h"

// forward declarations
class CollisionRegistrationCommand;
class CollisionDeregistrationCommand;
class CollisionVolume;
class Sprite;

class CollisionObject
{
public:
	CollisionObject();
	CollisionObject(const CollisionObject& co) = delete;
	CollisionObject& operator=(const CollisionObject& co) = delete;
	virtual ~CollisionObject();

	// TODO: docs for CollisionObject::GetCollisionVolume
	const CollisionVolume& GetCollisionVolume();


protected:
	enum class VolumeType
	{
		BSphere,
		AABB
	};

	// TODO: docs for CollisionObject::SetCollidableGroup
	template <typename C>
	void SetCollidableGroup()
	{
		typeID = SceneAttorney::Collision::GetCollisionManager(SceneManager::GetCurrentScene())->GetTypeID<C>();
	}
	
	/*!
	* \brief	Request that the engine check for collision with this object.
	* 
	* Call this function in a \c CollisionObject -derived class to let the engine know you would like to begin checking for collision with this object.
	* 
	* \note You must call SetCollidableGroup() on this object before calling this function!
	* 
	* \note	This function is only accessible to classes deriving from \c CollisionObject .
	* 
	* \note	As the name of this function implies, this puts in a request with the engine for your object to be used in collision detection.
	* The request is processed by the engine on the same frame this function is called, and collision detection will begin \b the \b following frame.
	* 
	* \return	Does not return anything.
	* 
	* \section example Example
	* TODO: create tutorial for how to use the collision system
	* 
	* \see CollisionObject::GetCollisionVolume
	* \see CollisionObject::SetCollidableGroup
	* \see CollisionObject::RequestCollisionDeregistration
	* \see CollisionObject::SetCollisionSprite
	* \see CollisionObject::UpdateCollisionData
	* \see CollisionObject::OnCollisionEnter
	* \see CollisionObject::OnCollisionDuring
	* \see CollisionObject::OnCollisionExit
	*/
	void RequestCollisionRegistration(); 
	/*!
	* \brief	Request that the engine stop checking for collision with this object.
	* 
	* Call this function in a \c CollisionObject -derived class to let the engine know you would like to stop checking for collision with this object.
	* 
	* \note	This function is only accessible to classes deriving from \c CollisionObject .
	* 
	* \note As the name of this function implies, this puts in a request with the engine for your object to be used in collision detection.
	* The request is processed by the engine on the same frame this function is called, and collision detection will cease \b the \b following frame.
	* 
	* \return	Does not return anything.
	* 
	* \section example Example
	* TODO: create tutorial for how to use the collision system
	* 
	* \see CollisionObject::GetCollisionVolume
	* \see CollisionObject::SetCollidableGroup
	* \see CollisionObject::RequestCollisionRegistration
	* \see CollisionObject::SetCollisionSprite
	* \see CollisionObject::UpdateCollisionData
	* \see CollisionObject::OnCollisionEnter
	* \see CollisionObject::OnCollisionDuring
	* \see CollisionObject::OnCollisionExit
	*/
	void RequestCollisionDeregistration(); 

	// TODO: docs for CollisionObject::SetCollisionSprite
	void SetCollisionSprite(Sprite* pSprite, VolumeType colVolType); 
	// TODO: docs for CollisionObject::UpdateCollisionData
	void UpdateCollisionData(Sprite* pSprite); 

	virtual void OnCollisionEnter(CollisionObject* pOther);
	virtual void OnCollisionDuring(CollisionObject* pOther);
	virtual void OnCollisionExit(CollisionObject* pOther);

private:
	friend class CollisionObjectAttorney;
	void Register();
	void Deregister();

	void Collision(CollisionObject* pOther);
	void NoCollision(CollisionObject* pOther);

private: // member variables
	CollisionManager::JNSTypeID typeID;
	RegistrationState regState;
	CollisionObjectGroup::CollisionObjectListRef deleteRef;
	CollisionRegistrationCommand* pRegCmd;
	CollisionDeregistrationCommand* pDeregCmd;
	CollisionVolume* pColVol;
	VolumeType* pVolType;
	sf::Sprite* pColSpr;
	bool collisionThisFrame;
	bool collisionPrevFrame;

};

#endif