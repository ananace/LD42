#include "StateManager.hpp"
#include "IState.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

StateManager::StateManager()
{
}

StateManager::~StateManager()
{
}

void StateManager::pushState(std::unique_ptr<IState>&& state)
{
    state->init();
    state->m_stateManager = this;

    m_curState = std::move(state);
}

void StateManager::popState()
{
    m_curState = nullptr;
}

const IState* StateManager::curState() const
{
    return m_curState.get();
}

IState* StateManager::curState()
{
    return m_curState.get();
}

void StateManager::update(float dt)
{
    if (!m_curState)
        return;

    m_curState->update(dt);
}

void StateManager::draw(sf::RenderTarget& rt)
{
    if (!m_curState)
        return;

    m_curState->draw(rt);
}
