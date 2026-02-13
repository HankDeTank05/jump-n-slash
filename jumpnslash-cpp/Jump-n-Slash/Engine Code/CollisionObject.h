#ifndef COLLISION_OBJECT_H
#define COLLISION_OBJECT_H

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


protected:
	enum class VolumeType
	{
		BSphere,
		AABB
	};

	/*!
	* \brief	Set the group that this CollisionObject will be a part of.
	* 
	* This function is called when first creating an object. It includes the calling \c CollisionObject in a group of objects based
	* on its type which should be tested for collision. Without calling this function, \c CollisionObject s will not be tested for collision.
	* 
	* \returns	Does not return anything.
	* 
	* \section example Example
	* TODO: docs for CollisionObject::SetCollisionObjectGroup needs example code
	* 
	* \see	CollisionObject::RequestCollisionRegistration
	* \see	CollisionObject::RequestCollisionDeregistration
	* \see	CollisionObject::SetCollisionSprite
	* \see	CollisionObject::UpdateCollisionData
	* \see	CollisionObject::OnCollisionEnter
	* \see	CollisionObject::OnCollisionDuring
	* \see	CollisionObject::OnCollisionExit
	*/
	template <typename C>
	void SetCollisionObjectGroup()
	{
		typeID = SceneAttorney::Collision::GetCollisionManager(SceneManager::GetCurrentScene())->GetTypeID<C>();
	}
	
	/*!
	* \brief	Request that the engine check for collision with this object.
	* 
	* Call this function in a \c CollisionObject -derived class to let the engine know you would like to begin checking for collision with this object.
	* 
	* \note You must call SetCollisionObjectGroup() on this object before calling this function!
	* 
	* \note	This function is only accessible to classes deriving from \c CollisionObject .
	* 
	* \note	As the name of this function implies, this puts in a request with the engine for your object to be used in collision detection.
	* The request is processed by the engine on the same frame this function is called, and collision detection will begin \b the \b following frame.
	* 
	* \return	Does not return anything.
	* 
	* \section example Example
	* TODO: docs for CollisionObject::RequestCollisionRegistration needs example code
	* 
	* \see CollisionObject::GetCollisionVolume
	* \see CollisionObject::SetCollisionObjectGroup
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
	* TODO: docs for CollisionObject::RequestCollisionDeregistration needs example code
	* 
	* \see CollisionObject::GetCollisionVolume
	* \see CollisionObject::SetCollisionObjectGroup
	* \see CollisionObject::RequestCollisionRegistration
	* \see CollisionObject::SetCollisionSprite
	* \see CollisionObject::UpdateCollisionData
	* \see CollisionObject::OnCollisionEnter
	* \see CollisionObject::OnCollisionDuring
	* \see CollisionObject::OnCollisionExit
	*/
	void RequestCollisionDeregistration(); 

	/*!
	* \brief	Sets the sprite which the chosen collision volume should be fit to.
	* 
	* This function uses a given sprite and chosen collision volume type to create the initial collision volume which will be used for collision testing.
	* The chosen collision volume's size will be fit to be as small as possible while still encompassing the entire sprite.
	* 
	* \note	
	*/
	void SetCollisionSprite(Sprite* pSprite, VolumeType colVolType); 
	void UpdateCollisionData();
	// TODO: docs for CollisionObject::UpdateCollisionData
	void UpdateCollisionData(Sprite* pSprite); 

	virtual void OnCollisionEnter(CollisionObject* pOther);
	virtual void OnCollisionDuring(CollisionObject* pOther);
	virtual void OnCollisionExit(CollisionObject* pOther);

private:
	friend class CollisionObjectAttorney;
	const CollisionVolume& GetCollisionVolume();

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
	Sprite* pColSpr;
	bool collisionThisFrame;
	bool collisionPrevFrame;

};

#endif