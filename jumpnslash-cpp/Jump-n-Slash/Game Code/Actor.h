#ifndef ACTOR_H
#define ACTOR_H

#include "../Engine Code/AlarmObject.h"
#include "../Engine Code/CollisionObject.h"
#include "../Engine Code/DrawObject.h"
#include "../Engine Code/UpdateObject.h"

class Actor : public AlarmObject, public CollisionObject, public DrawObject, public UpdateObject
{
public:
	Actor();
	Actor(const Actor& a) = delete;
	Actor& operator=(const Actor& a) = delete;
	virtual ~Actor();
};

#endif
