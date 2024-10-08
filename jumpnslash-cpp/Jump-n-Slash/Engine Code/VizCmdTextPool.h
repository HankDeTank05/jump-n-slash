#ifndef VIZ_CMD_TEXT_POOL_H
#define VIZ_CMD_TEXT_POOL_H

#include <stack>

// forward declarations
class VisualizerCommandText;

class VizCmdTextPool
{
public:
	VizCmdTextPool();
	VizCmdTextPool(const VizCmdTextPool& vctp) = delete;
	VizCmdTextPool& operator=(const VizCmdTextPool& vctp) = delete;
	virtual ~VizCmdTextPool();

	using TextCmdPool = std::stack<VisualizerCommandText*>;

	VisualizerCommandText* GetCommand();
	void RecycleCommand(VisualizerCommandText* pCmd);

private:
	TextCmdPool pool;
};

#endif