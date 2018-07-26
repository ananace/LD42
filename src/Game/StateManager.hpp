#pragma once

#include <memory>

namespace sf { class RenderTarget; }
class IState;

class StateManager
{
public:
    StateManager();
    StateManager(const StateManager& copy) = default;
    StateManager(StateManager&& move) = default;
    ~StateManager();

    StateManager& operator=(const StateManager& copy) = default;
    StateManager& operator=(StateManager&& move) = default;

    void pushState(std::unique_ptr<IState>&& state);
    void popState();
    const IState* curState() const;
    IState* curState();

    void update(float dt);

    void draw(sf::RenderTarget& rt);

private:
    std::unique_ptr<IState> m_curState;
};
