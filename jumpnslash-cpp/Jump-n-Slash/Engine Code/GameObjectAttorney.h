#ifndef GAME_OBJECT_ATTORNEY_H
#define GAME_OBJECT_ATTORNEY_H

// forward declarations
class GameObject;

class GameObjectAttorney
{
public:
	class CommandAccess
	{
	private:
		friend class GameObjectRegistrationCommand;
		friend class GameObjectDeregistrationCommand;
		static void EnterScene(GameObject* pGameObject);
		static void ExitScene(GameObject* pGameObject);
	};
};

#endif