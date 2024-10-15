#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <SFML/System/Clock.hpp>

class TimeManager // this class is written as a singleton
{
private:
	static TimeManager* pInstance;

	TimeManager();
	TimeManager(const TimeManager& tm) = delete;
	TimeManager& operator=(const TimeManager& tm) = delete;
	virtual ~TimeManager() = default;

	static TimeManager& Instance();

public: // api functions
	static float GetCurrentEngineTime(); // TODO: docs for TimeManager::GetCurrentEngineTime
	static float GetFrameTime(); // TODO: docs for TimeManager::GetFrameTime

private: // engine-only api functions
	friend class TimeManagerAttorney;
	static void Terminate();
	static void ProcessTime(); // TODO: docs for TimeManager::ProcessTime
	static void Start();

private: // api backend functions
	float privGetCurrentEngineTime();
	float privGetFrameTime();

	void privProcessTime();

private: // member variables
	sf::Clock clock;
	float currentTime;
	float previousTime;
	float frameTime;
};

#endif