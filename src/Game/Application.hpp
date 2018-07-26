#pragma once

#include <InputManager.hpp>
#include <ParticleManager.hpp>
#include "StateManager.hpp"

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
    StateManager& GetStateManager();
    const StateManager& GetStateManager() const;

private:
    enum
    {
        kParticleCount = 512
    };

    Core::InputManager m_inputMan;
    Core::ParticleManager m_particleMan[2];
    StateManager m_stateMan;

    sf::RenderWindow m_renderWindow;
};
