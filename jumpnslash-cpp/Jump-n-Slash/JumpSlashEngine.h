#ifndef JUMP_SLASH_ENGINE_H
#define JUMP_SLASH_ENGINE_H

class JumpSlashEngine
{
public:
	JumpSlashEngine();
	JumpSlashEngine(const JumpSlashEngine& jse) = delete;
	JumpSlashEngine& operator=(const JumpSlashEngine& jse) = delete;
	~JumpSlashEngine();

};

#endif