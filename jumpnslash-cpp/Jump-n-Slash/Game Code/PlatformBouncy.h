#ifndef PLATFORM_BOUNCY_H
#define PLATFORM_BOUNCY_H

class PlatformBouncy
{
public:
	PlatformBouncy();
	PlatformBouncy(const PlatformBouncy& pb) = delete;
	PlatformBouncy& operator=(const PlatformBouncy& pb) = delete;
	virtual ~PlatformBouncy() = default;
};

#endif