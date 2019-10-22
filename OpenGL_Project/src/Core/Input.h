#pragma once

class Input {
public:
	inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedimp(keycode); }
protected:
	virtual bool IsKeyPressedimp(int keycode) = 0;
private:
	static Input* s_Instance;
};
