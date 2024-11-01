#ifndef INPUT_EVENT_H
#define INPUT_EVENT_H

enum class GamepadBtnEvent
{
	BtnPress,
	BtnRelease
};

enum class GamepadAxisEvent
{
	AxisInputPositive,
	AxisInputNegative,
	AxisInputAny
};

enum class KeyEvent
{
	KeyPress,
	KeyRelease
};

enum class MouseEvent
{
	BtnPress,
	BtnRelease
};

#endif