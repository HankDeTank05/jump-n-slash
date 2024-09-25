#ifndef TEXTURE_MANAGER_ATTORNEY_H
#define TEXTURE_MANAGER_ATTORNEY_H

class TextureManagerAttorney
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