#ifndef DRAWABLE_OBJECT_H
#define DRAWABLE_OBJECT_H

class DrawableObject
{
public:
	DrawableObject();
	DrawableObject(const DrawableObject& dob) = delete;
	DrawableObject& operator=(const DrawableObject& dob) = delete;
	virtual ~DrawableObject();

protected:

	// TODO: documentation for DrawableObject::Draw()
	virtual void Draw();

	// TODO: documentation for DrawableObject::EnqueueForDrawRegistration()
	void EnqueueForDrawRegistration();
	// TODO: documentation for DrawableObject::EnqueueForDrawDeregistration()
	void EnqueueForDrawDeregistration();
};

#endif