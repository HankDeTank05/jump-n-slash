#include "TimeManager.h"

TimeManager* TimeManager::pInstance = nullptr;

TimeManager::TimeManager()
	: clock(),
	currentTime(0.f),
	previousTime(0.f),
	frameTime(0.f)
{
	// do nothing
}

TimeManager& TimeManager::Instance()
{
	if (pInstance == nullptr)
	{
		pInstance = new TimeManager();
	}
	return *pInstance;
}

float TimeManager::GetCurrentEngineTime()
{
	return Instance().privGetCurrentEngineTime();
}

float TimeManager::GetFrameTime()
{
	return Instance().privGetFrameTime();
}

void TimeManager::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

void TimeManager::ProcessTime()
{
	Instance().privProcessTime();
}

void TimeManager::Start()
{
	Instance();
}

float TimeManager::privGetCurrentEngineTime()
{
	return currentTime;
}

float TimeManager::privGetFrameTime()
{
	return frameTime;
}

void TimeManager::privProcessTime()
{
	previousTime = currentTime;

	currentTime = clock.getElapsedTime().asSeconds();

	frameTime = currentTime - previousTime;
}
