#ifndef VIZ_CMD_FACTORY_ATTORNEY_H
#define VIZ_CMD_FACTORY_ATTORNEY_H

class VizCmdFactoryAttorney
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