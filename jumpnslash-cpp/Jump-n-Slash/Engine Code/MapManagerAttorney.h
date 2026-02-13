#ifndef GRID_MANAGER_ATTORNEY_H
#define GRID_MANAGER_ATTORNEY_H

class MapManagerAttorney
{
public:
	class Termination
	{
	private:
		friend class JumpSlashEngine;
		static void Terminate();
	};
};

#endif