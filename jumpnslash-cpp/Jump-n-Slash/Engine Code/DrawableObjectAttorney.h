#ifndef DRAWABLE_OBJECT_ATTORNEY_H
#define DRAWABLE_OBJECT_ATTORNEY_H

// forward declarations
class DrawableObject;

class DrawableObjectAttorney
{
public:
	class GameLoop
	{
	private:
		friend class DrawManager;
		static void Draw(DrawableObject* pDrawable);
	};
	class Registration
	{
	private:
		friend class DrawRegistrationCommand;
		static void Register(DrawableObject* pDrawable);
	};
};

#endif