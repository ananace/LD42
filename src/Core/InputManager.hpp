#pragma once

#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <vector>

namespace sf { struct Event; }

namespace Core
{

class InputManager
{
public:
    InputManager();
    InputManager(const InputManager&) = default;
    InputManager(InputManager&&) = default;
    ~InputManager() = default;

    InputManager& operator=(const InputManager&) = default;
    InputManager& operator=(InputManager&&) = default;

    void init(int inputCount);
    void bind(int input, sf::Keyboard::Key key);
    void bind(int input, unsigned int joystick, sf::Joystick::Axis axis, bool direction);
    void bind(int input, unsigned int joystick, unsigned int button);

    void pushEvent(const sf::Event& ev);

    int numInputs() const;

    float operator[](int input) const;
    bool wasPressed(int input) const;
    bool isPressed(int input) const;

private:
    struct Input
    {
        enum Type_t
        {
            Type_Invalid,

            Type_Key,
            Type_JAxis,
            Type_JButton
        } Type;

        union
        {
            struct
            {
                sf::Keyboard::Key Key;
            } Key;
            struct
            {
                unsigned int Joystick;
                sf::Joystick::Axis Axis;
                bool Direction;
            } JAxis;
            struct
            {
                unsigned int Joystick;
                unsigned int Button;
            } JButton;
        };
    };

    std::vector<Input> m_inputs;
    std::vector<float> m_curValues;
    std::vector<float> m_oldValues;

};

}
