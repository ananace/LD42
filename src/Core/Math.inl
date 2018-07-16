#include "Math.hpp"

template<typename T>
constexpr T Math::Pi()
{
#if defined(M_PI)
    return T(M_PI);
#else
    return std::atan(T(1)) * T(4);
#endif
}

template<typename T>
constexpr T Math::Phi()
{
    return (T(1) + std::sqrt(T(5))) / T(2);
}

template<typename T>
constexpr T Math::Deg2Rad(T degrees)
{
    return degrees * (Pi<T>() / T(180));
}

template<typename T>
constexpr T Math::Rad2Deg(T radians)
{
    return radians * (T(180) / Pi<T>());
}

template<typename T>
constexpr bool Math::FloatCmp(T a, T b, T epsilon)
{
    return (b - a) < epsilon;
}

template<typename T>
T Math::AngularLerp(T start, T end, T delta)
{
    return Spinor<T>(cos(start / T(2)), sin(start / T(2)))
             .slerp(Spinor<T>(cos(end / T(2)), sin(end / T(2))), delta)
             .getAngle();
}

template<typename T>
sf::Vector2<T> Math::Normalized(const sf::Vector2<T>& vec)
{
    T len = Length(vec);

    return sf::Vector2<T>(vec.x / len, vec.y / len);
}

template<typename T>
float Math::Length(const sf::Vector2<T>& vec)
{
    return std::sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

template<typename T>
float Math::LengthSquared(const sf::Vector2<T>& vec)
{
    return (vec.x * vec.x) + (vec.y * vec.y);
}

template<typename T>
float Math::Distance(const sf::Vector2<T>& p1, const sf::Vector2<T>& p2)
{
    T dx = p2.x - p1.x;
    T dy = p2.y - p1.y;

    return std::sqrt((dx * dx) + (dy * dy));
}

template<typename T>
float Math::DistanceSquared(const sf::Vector2<T>& p1, const sf::Vector2<T>& p2)
{
    T dx = p2.x - p1.x;
    T dy = p2.y - p1.y;

    return (dx * dx) + (dy * dy);
}

template<typename T>
float Math::Angle(const sf::Vector2<T>& vec)
{
    return std::atan2(vec.y, vec.x);
}

template<typename T>
float Math::Direction(const sf::Vector2<T>& p1, const sf::Vector2<T>& p2)
{
    T dx = p2.x - p1.x;
    T dy = p2.y - p1.y;

    return std::atan2(dy, dx);
}

