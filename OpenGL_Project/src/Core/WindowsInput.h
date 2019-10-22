#pragma once

#include "Input.h"

class WindowsInput : public Input {
protected:
	virtual bool IsKeyPressedimp(int keycode) override;
};
