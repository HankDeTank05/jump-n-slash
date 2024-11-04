#ifndef CONTROL_SELECTION_H
#define CONTROL_SELECTION_H

#include "../Engine Code/Scene.h"

// forward declarations
class ControlSelector;

class ControlSelection : public Scene
{
public:
	ControlSelection();
	ControlSelection(const ControlSelection& cs) = delete;
	ControlSelection& operator=(const ControlSelection& cs) = delete;
	virtual ~ControlSelection() = default;

	virtual void Init() override;
	virtual void End() override;

private:
	ControlSelector* pSelector;
};

#endif