#ifndef UPDATABLE_OBJECT_ATTORNEY_H
#define UPDATABLE_OBJECT_ATTORNEY_H

// forward declarations
class UpdatableObject;

class UpdatableObjectAttorney
{
public:
	class GameLoop
	{
	private:
		friend class UpdateManager;
		static void Update(UpdatableObject* pUpdatable);
	};

	class Registration
	{
	private:
		friend class UpdateRegistrationCommand;
		friend class UpdateDeregistrationCommand;
		static void Register(UpdatableObject* pUpdatable);
		static void Deregister(UpdatableObject* pUpdatable);
	};
};

#endif