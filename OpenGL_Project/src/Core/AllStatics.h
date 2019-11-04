
//deltatime
float DeltaTime::time;
float DeltaTime::lasttime;
float DeltaTime::deltatime;
//colors
vec4 COLORS::Red = vec4(0.9, 0, 0, 1);
vec4 COLORS::Yellow = vec4(1, 1, 0, 1);
vec4 COLORS::Blue = vec4(0, 0, 1, 1);
vec4 COLORS::Green = vec4(0, 1, 0, 1);
vec4 COLORS::Brown = vec4(0.5, 0.3, 0.1, 1);
vec4 COLORS::White = vec4(1, 1, 1, 1);
vec4 COLORS::Orange = vec4(1, 0.31, 0, 1);
//create the window
GLFWwindow *Window::m_window;
//storage of all references to our objects in the scene
std::vector <std::reference_wrapper<Renderer2D>> Renderer2D::objects2d;
//storage of all references to our object's collisions in the scene
std::vector <std::reference_wrapper<Renderer2D>> Renderer2D::collision2d;
//visible collisions
bool Collision::IsVisible = false;
