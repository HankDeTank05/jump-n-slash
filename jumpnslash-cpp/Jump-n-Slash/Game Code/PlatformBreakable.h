#ifndef PLATFORM_BREAKABLE_H
#define PLATFORM_BREAKABLE_H

class PlatformBreakable
{
public:
	PlatformBreakable();
	PlatformBreakable(const PlatformBreakable& pb) = delete;
	PlatformBreakable& operator=(const PlatformBreakable& pb) = delete;
	virtual ~PlatformBreakable() = default;
};

#endif