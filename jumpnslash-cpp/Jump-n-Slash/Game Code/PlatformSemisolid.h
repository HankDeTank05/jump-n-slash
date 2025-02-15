#ifndef PLATFORM_SEMISOLID_H
#define PLATFORM_SEMISOLID_H

class PlatformSemisolid
{
public:
	PlatformSemisolid();
	PlatformSemisolid(const PlatformSemisolid& ps) = delete;
	PlatformSemisolid& operator=(const PlatformSemisolid& ps) = delete;
	virtual ~PlatformSemisolid() = default;
};

#endif