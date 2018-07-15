#include "Application.hpp"

Application* g_application;

Application::Application()
{
    g_application = this;
}

Application::~Application()
{
    g_application = nullptr;
}

Application& GetApplication()
{
    return *g_application;
}
