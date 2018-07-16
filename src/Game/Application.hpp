#pragma once

#include <InputManager.hpp>
#include <ParticleManager.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

class Application
{
public:
    Application();
    ~Application();

    static Application& GetApplication();

    void init(int argc, char** argv);
    void run();

    Core::InputManager& GetInputManager();
    const Core::InputManager& GetInputManager() const;
    Core::ParticleManager& GetParticleManager(bool overlay = false);
    const Core::ParticleManager& GetParticleManager(bool overlay = false) const;

private:
    enum
    {
        kParticleCount = 512
    };

    Core::InputManager m_inputMan;
    Core::ParticleManager m_particleMan[2];

    sf::RenderWindow m_renderWindow;
};
