#include "InputManager.hpp"

#include <SFML/Window/Event.hpp>

#include <algorithm>

#include <cmath>

using Core::InputManager;

InputManager::InputManager()
{ }

void InputManager::init(int inputCount)
{
    m_inputs.resize(inputCount);
    m_curValues.resize(inputCount, 0);
    m_oldValues.resize(inputCount, 0);
}

void InputManager::bind(int input, sf::Keyboard::Key key)
{
    Input& bind = m_inputs[input];

    bind.Type = Input::Type_Key;
    bind.Key.Key = key;
}

void InputManager::bind(int input, unsigned int joystick, sf::Joystick::Axis axis, bool direction)
{
    Input& bind = m_inputs[input];

    bind.Type = Input::Type_JAxis;
    bind.JAxis.Joystick = joystick;
    bind.JAxis.Axis = axis;
    bind.JAxis.Direction = direction;
}

void InputManager::bind(int input, unsigned int joystick, unsigned int button)
{
    Input& bind = m_inputs[input];

    bind.Type = Input::Type_JButton;
    bind.JButton.Joystick = joystick;
    bind.JButton.Button = button;
}

void InputManager::pushEvent(const sf::Event& ev)
{
    std::vector<Input>::iterator it = m_inputs.end();
    float value = 0;

    switch (ev.type)
    {
    case sf::Event::KeyPressed:
    case sf::Event::KeyReleased:
        it = std::find_if(m_inputs.begin(), m_inputs.end(), [&ev](const Input& inp) {
            return inp.Type == Input::Type_Key && inp.Key.Key == ev.key.code;
        });
        value = float(ev.type == sf::Event::KeyPressed);
        break;

    case sf::Event::JoystickButtonPressed:
    case sf::Event::JoystickButtonReleased:
        it = std::find_if(m_inputs.begin(), m_inputs.end(), [&ev](const Input& inp) {
            return inp.Type == Input::Type_JButton \
                && inp.JButton.Joystick == ev.joystickButton.joystickId \
                && inp.JButton.Button == ev.joystickButton.button;
        });
        value = float(ev.type == sf::Event::JoystickButtonPressed);
        break;

    case sf::Event::JoystickMoved:
        // TODO: Set other direction input to zero?
        it = std::find_if(m_inputs.begin(), m_inputs.end(), [&ev](const Input& inp) {
            bool dircmp = ev.joystickMove.position > 0;
            return inp.Type == Input::Type_JAxis \
                && inp.JAxis.Joystick == ev.joystickMove.joystickId \
                && inp.JAxis.Axis == ev.joystickMove.axis \
                && inp.JAxis.Direction == dircmp;
        });
        value = std::fabs(ev.joystickMove.position / 100.f);
        break;

    default:
        return;
    }

    if (it != m_inputs.end())
    {
        int input = it - m_inputs.begin();
        m_oldValues[input] = m_curValues[input];
        m_curValues[input] = value;
    }
}

int InputManager::numInputs() const
{
    return m_inputs.size();
}
