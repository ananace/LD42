#pragma once

#include <SFML/System/Vector2.hpp>

#include <type_traits>

#include <cmath>

namespace Core
{

namespace Math
{
    template<typename T>
    constexpr T Pi();
    template<typename T>
    constexpr T HalfPi() { return Pi<T>() / T(2); }
    template<typename T>
    constexpr T TwoPi() { return Pi<T>() * T(2); }

    template<typename T>
    constexpr T Phi();

    template<typename T>
    constexpr T Deg2Rad(T degrees);
    template<typename T>
    constexpr T Rad2Deg(T radians);

    template<typename T>
    constexpr bool FloatCmp(T a, T b, T epsilon = 0.0000001);

    template<typename T>
    T AngularLerp(T start, T end, T delta);

    template<typename T, typename = std::enable_if_t<std::is_arithmetic<T>::value>>
    T Lerp(T start, T end, float delta);
    template<typename T, typename = std::enable_if_t<!std::is_arithmetic<T>::value>>
    T Lerp(const T& start, const T& end, float delta);

    template<typename T>
    sf::Vector2<T> Normalized(const sf::Vector2<T>& vec);
    template<typename T>
    float Length(const sf::Vector2<T>& vec);
    template<typename T>
    float LengthSquared(const sf::Vector2<T>& vec);
    template<typename T>
    float Distance(const sf::Vector2<T>& p1, const sf::Vector2<T>& p2);
    template<typename T>
    float DistanceSquared(const sf::Vector2<T>& p1, const sf::Vector2<T>& p2);
    template<typename T>
    float Angle(const sf::Vector2<T>& vec);
    template<typename T>
    float Direction(const sf::Vector2<T>& p1, const sf::Vector2<T>& p2);

    template<typename T>
    struct Spinor
    {
    public:
        Spinor();
        Spinor(T real, T imag);
        explicit Spinor(const sf::Vector2<T>& point);
        explicit Spinor(T angle);
        Spinor(const Spinor<T>& copy) = default;
        Spinor(Spinor<T>&& move) = default;
        ~Spinor() = default;

        Spinor<T>& operator=(const Spinor<T>& rhs) = default;
        Spinor<T>& operator=(Spinor<T>&& rhs) = default;

        bool operator==(const Spinor<T>& other);

        Spinor<T>& operator+=(const Spinor<T>& rhs);
        Spinor<T>& operator-=(const Spinor<T>& rhs);
        Spinor<T>& operator*=(const Spinor<T>& rhs);
        Spinor<T>& operator*=(T val);
        Spinor<T>& operator/=(const Spinor<T>& rhs);
        Spinor<T>& operator/=(T val);

        Spinor<T> operator+(const Spinor<T>& rhs);
        Spinor<T> operator-(const Spinor<T>& rhs);
        Spinor<T> operator*(const Spinor<T>& rhs);
        Spinor<T> operator*(T val);
        Spinor<T> operator/(const Spinor<T>& rhs);
        Spinor<T> operator/(T val);

        void invert();
        Spinor<T> getInverted() const;
        void normalize();
        Spinor<T> getNormalized() const;

        T getLength() const;
        T getAngle() const;

        // Interpolation
        Spinor<T> slerp(const Spinor<T>& other, T delta) const;

        T Real,
          Complex;
    };

    typedef Spinor<float> Spinorf;
    typedef Spinor<double> Spinord;

}

#include "Math.inl"

}
