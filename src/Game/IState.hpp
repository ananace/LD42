#pragma once

namespace sf { class RenderTarget; }
class StateManager;

class IState
{
public:
    IState() = default;
    virtual ~IState();

    virtual void init() = 0;
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderTarget& rt) = 0;

protected:
    const StateManager& getStateManager() const { return *m_stateManager; }
    StateManager& getStateManager() { return *m_stateManager; }

private:
    friend class StateManager;

    StateManager* m_stateManager;
};
