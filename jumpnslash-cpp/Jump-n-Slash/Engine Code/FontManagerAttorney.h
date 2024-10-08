#ifndef FONT_MANAGER_ATTORNEY_H
#define FONT_MANAGER_ATTORNEY_H

class FontManagerAttorney
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