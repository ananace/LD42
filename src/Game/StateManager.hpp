#pragma once

namespace sf { class RenderTarget; }

class StateManager
{
public:
    StateManager();
    StateManager(const StateManager& copy) = default;
    StateManager(StateManager&& move) = default;
    ~StateManager();

    StateManager& operator=(const StateManager& copy) = default;
    StateManager& operator=(StateManager&& move) = default;

    void update(float dt);

    void draw(sf::RenderTarget& rt);

private:
};
