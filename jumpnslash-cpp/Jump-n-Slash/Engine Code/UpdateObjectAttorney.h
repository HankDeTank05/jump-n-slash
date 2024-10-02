#ifndef UPDATE_OBJECT_ATTORNEY_H
#define UPDATE_OBJECT_ATTORNEY_H

// forward declarations
class UpdateObject;

class UpdateObjectAttorney
{
public:
	class GameLoop
	{
	private:
		friend class UpdateManager;
		static void Update(UpdateObject* pUpdatable, float deltaTime);
	};

	class Registration
	{
	private:
		friend class UpdateRegistrationCommand;
		friend class UpdateDeregistrationCommand;
		static void Register(UpdateObject* pUpdatable);
		static void Deregister(UpdateObject* pUpdatable);
	};
};

#endif