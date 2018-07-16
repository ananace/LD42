#include "Application.hpp"

#include <Math.hpp>

#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    Application app;
    app.init(argc, argv);

    double d_pi = Core::Math::Pi<double>();
    float f_pi = Core::Math::Pi<float>();
    int i_pi = Core::Math::Pi<int>();

    std::cout << "Double Pi: " << std::setprecision(24) << d_pi << std::endl
              << "Float Pi: " << std::setprecision(24) << f_pi << std::endl
              << "Int Pi: " << std::setprecision(24) << i_pi << std::endl
              << "Float Phi: " << std::setprecision(24) << Core::Math::Phi<float>() << std::endl;

    std::cout << "Degrees to radians:" << std::endl
              << "0: " << Core::Math::Deg2Rad(0.f) << std::endl
              << "90: " << Core::Math::Deg2Rad(90.f) << std::endl
              << "180: " << Core::Math::Deg2Rad(180.f) << std::endl;

    sf::Vector2f p1(10, 10),
                 p2(100, 20);
    std::cout << "P1: [" << p1.x << ", " << p1.y << "], P2: [" << p2.x << ", " << p2.y << "]" << std::endl
              << "Distance: " << Core::Math::Distance(p1, p2) << std::endl
              << "Direction: " << Core::Math::Direction(p1, p2) << " (" << Core::Math::Rad2Deg(Core::Math::Direction(p1, p2)) << ")" << std::endl;

    auto norm = Core::Math::Normalized(sf::Vector2f(10, 2));
    std::cout << "[10, 2] length: " << Core::Math::Length(sf::Vector2f(10,2)) << ", normalized: [" << norm.x << ", " << norm.y << "]" << std::endl;

    return 0;
}
