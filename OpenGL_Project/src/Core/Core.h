#pragma once
#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "../vendor/glm/gtc/type_ptr.hpp"
const float PI = 3.141592653589793238462643383279f;

inline glm::mat4 StPos(float x, float y) { return glm::translate(glm::mat4(1.f), glm::vec3(x, y, 0.0f)); }
inline float Angle(float angle) { return angle * PI / 180; }
