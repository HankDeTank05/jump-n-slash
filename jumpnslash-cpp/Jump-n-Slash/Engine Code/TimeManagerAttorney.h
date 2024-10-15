#ifndef TIME_MANAGER_ATTORNEY_H
#define TIME_MANAGER_ATTORNEY_H

class TimeManagerAttorney
{
public:
	class Termination
	{
	private:
		friend class JumpSlashEngine;
		static void Terminate();
	};

	class Time
	{
	private:
		friend class JumpSlashEngine;
		static void Start();
		static void ProcessTime();
	};
};

#endif