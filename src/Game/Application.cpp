#include "Application.hpp"
#include "Inputs.hpp"
#include "Particles.hpp"

#include <Math.hpp>

#include <SFML/Window/Event.hpp>

#include <chrono>

Application* g_application;

Application::Application()
{
    g_application = this;

    m_inputMan.init(Input_Count);
    m_particleMan[0].setParticleCount(kParticleCount);
    m_particleMan[1].setParticleCount(kParticleCount);
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
    auto p1 = std::chrono::high_resolution_clock::now(),
         p2 = p1;
    auto dt = p1 - p2;

    sf::Event ev = {};
    while (m_renderWindow.isOpen())
    {
        p2 = p1;
        p1 = std::chrono::high_resolution_clock::now();
        dt = p1 - p2;

        float dtSeconds = std::chrono::duration_cast<std::chrono::duration<float>>(dt).count();

        while (m_renderWindow.pollEvent(ev))
        {
            m_inputMan.pushEvent(ev);

            if (ev.type == sf::Event::Closed)
                m_renderWindow.close();
        }

        m_particleMan[0].update(dtSeconds);
        m_particleMan[1].update(dtSeconds);

        m_renderWindow.clear();


        m_renderWindow.draw(m_particleMan[1]);
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
Core::ParticleManager& Application::GetParticleManager(bool overlay)
{
    if (overlay)
        return m_particleMan[1];
    return m_particleMan[0];
}
const Core::ParticleManager& Application::GetParticleManager(bool overlay) const
{
    if (overlay)
        return m_particleMan[1];
    return m_particleMan[0];
}

Application& Application::GetApplication()
{
    return *g_application;
}
