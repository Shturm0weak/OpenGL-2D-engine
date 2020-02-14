#ifndef ALLSTATICS_H
#define ALLSTATICS_H

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
OrthographicCamera Window::m_camera(-5.f, 5.f, 3.75f, -3.75f); //initialize the camera
GLFWwindow *Window::m_window;
//storage of all references to our objects in the scene
std::vector <std::reference_wrapper<Renderer2DLayer>> Renderer2DLayer::objects2d;
//storage of all references to our object's collisions in the scene
std::vector <std::reference_wrapper<Renderer2DLayer>> Renderer2DLayer::collision2d;
const char** Renderer::items;
//visible collisions
bool Collision::IsVisible = true;
int Renderer2DLayer::obj_id = 0;
int Renderer2DLayer::col_id = 0;
//ThreadPool
ThreadPool* ThreadPool::thread_pool = nullptr;
bool ThreadPool::initialized;
std::vector<std::string> Editor::texturesPath;
std::vector<Texture*> Editor::texture;
#endif // !ALLSTATICS_H