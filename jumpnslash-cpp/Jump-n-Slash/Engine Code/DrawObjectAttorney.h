#ifndef DRAW_OBJECT_ATTORNEY_H
#define DRAW_OBJECT_ATTORNEY_H

// forward declarations
class DrawObject;

class DrawObjectAttorney
{
public:
	class GameLoop
	{
	private:
		friend class DrawManager;
		static void Draw(DrawObject* pDrawable);
	};
	class Registration
	{
	private:
		friend class DrawRegistrationCommand;
		friend class DrawDeregistrationCommand;
		static void Register(DrawObject* pDrawable);
		static void Deregister(DrawObject* pDrawable);
	};
};

#endif