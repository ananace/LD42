#include "Application.hpp"
#include "Inputs.hpp"
#include "Particles.hpp"

#include <Math.hpp>

#include <SFML/Window/Event.hpp>

Application* g_application;

Application::Application()
{
    g_application = this;

    m_inputMan.init(Input_Count);
    m_particleMan.setParticleCount(kParticleCount);
}

Application::~Application()
{
    g_application = nullptr;
}

void Application::init(int argc, char** argv)
{
    (void)argc;
    (void)argv;
}

void Application::run()
{
    sf::Event ev = {};
    while (m_renderWindow.isOpen())
    {
        while (m_renderWindow.pollEvent(ev))
        {
            m_inputMan.pushEvent(ev);

            if (ev.type == sf::Event::Closed)
                m_renderWindow.close();
        }

        m_renderWindow.clear();

        m_renderWindow.display();
    }
}


Core::InputManager& Application::GetInputManager()
{
    return m_inputMan;
}
const Core::InputManager& Application::GetInputManager() const
{
    return m_inputMan;
}
Core::ParticleManager& Application::GetParticleManager()
{
    return m_particleMan;
}
const Core::ParticleManager& Application::GetParticleManager() const
{
    return m_particleMan;
}

Application& Application::GetApplication()
{
    return *g_application;
}
