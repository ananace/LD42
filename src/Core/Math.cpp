#include "Math.hpp"

#include <SFML/Graphics/Color.hpp>

namespace Core
{

namespace Math
{

template<>
sf::Vector2f Lerp<sf::Vector2f>(const sf::Vector2f& start, const sf::Vector2f& end, float delta)
{
    return start + (end - start) * delta;
}

template<>
sf::Color Lerp<sf::Color>(const sf::Color& start, const sf::Color& end, float delta)
{
    sf::Color ret;

    ret.r = start.r + (end.r - start.r) * delta;
    ret.g = start.g + (end.g - start.g) * delta;
    ret.b = start.b + (end.b - start.b) * delta;
    ret.a = start.a + (end.a - start.a) * delta;

    return ret;
}

}

}

using Core::Math::Spinor;

template<typename T>
Spinor<T>::Spinor()
    : Real(0)
    , Complex(0)
{ }
template<typename T>
Spinor<T>::Spinor(T real, T imag)
    : Real(real)
    , Complex(imag)
{ }
template<typename T>
Spinor<T>::Spinor(const sf::Vector2<T>& point)
    : Real(cos(Angle(point)))
    , Complex(sin(Angle(point)))
{ }
template<typename T>
Spinor<T>::Spinor(T angle)
    : Real(cos(angle))
    , Complex(sin(angle))
{ }

template<typename T>
bool Spinor<T>::operator==(const Spinor<T>& other)
{
    return FloatCmp(Real, other.Real) &&
           FloatCmp(Complex, other.Complex);
}

template<typename T>
Spinor<T>& Spinor<T>::operator+=(const Spinor<T>& rhs)
{
    Real += rhs.Real;
    Complex += rhs.Complex;
    return *this;
}

template<typename T>
Spinor<T>& Spinor<T>::operator-=(const Spinor<T>& rhs)
{
    Real -= rhs.Real;
    Complex -= rhs.Complex;
    return *this;
}
template<typename T>
Spinor<T>& Spinor<T>::operator*=(const Spinor<T>& rhs)
{
    Real *= rhs.Real;
    Complex *= rhs.Complex;
    return *this;
}
template<typename T>
Spinor<T>& Spinor<T>::operator*=(T val)
{
    Real *= val;
    Complex *= val;
    return *this;
}
template<typename T>
Spinor<T>& Spinor<T>::operator/=(const Spinor<T>& rhs)
{
    T len = rhs.Real * rhs.Real + rhs.Complex * rhs.Complex;
    if (len == 0)
    {
        Real = 0;
        Complex = 0;
    }
    else
    {
        T newReal = (Real * rhs.Real - Complex * rhs.Complex) / len;
        Complex = (Complex * rhs.Real - Real * rhs.Complex) / len;
        Real = newReal;
    }

    return *this;
}
template<typename T>
Spinor<T>& Spinor<T>::operator/=(T val)
{
    Real /= val;
    Complex /= val;
    return *this;
}

template<typename T>
Spinor<T> Spinor<T>::operator+(const Spinor<T>& rhs)
{
    return { Real + rhs.Real, Complex + rhs.Complex };
}
template<typename T>
Spinor<T> Spinor<T>::operator-(const Spinor<T>& rhs)
{
    return { Real - rhs.Real, Complex - rhs.Complex };
}
template<typename T>
Spinor<T> Spinor<T>::operator*(const Spinor<T>& rhs)
{
    return { Real * rhs.Real, Complex * rhs.Complex };
}
template<typename T>
Spinor<T> Spinor<T>::operator*(T val)
{
    return { Real * val, Complex * val };
}
template<typename T>
Spinor<T> Spinor<T>::operator/(const Spinor<T>& rhs)
{
    T len = rhs.Real * rhs.Real + rhs.Complex * rhs.Complex;
    if (len == 0)
    {
        return {};
    }

    return {
        (Real * rhs.Real - Complex * rhs.Complex) / len,
        (Complex * rhs.Real - Real * rhs.Complex) / len
    };
}
template<typename T>
Spinor<T> Spinor<T>::operator/(T val)
{
    return { Real / val, Complex / val };
}

template<typename T>
void Spinor<T>::invert()
{
    T len = sqrt(Real * Real + Complex * Complex);

    Real *= len;
    Complex *= -len;
}
template<typename T>
Spinor<T> Spinor<T>::getInverted() const
{
    T len = sqrt(Real * Real + Complex * Complex);

    return {
        Real * len,
        Complex * -len
    };
}
template<typename T>
void Spinor<T>::normalize()
{
    T len = sqrt(Real * Real + Complex * Complex);

    Real /= len;
    Complex /= len;
}
template<typename T>
Spinor<T> Spinor<T>::getNormalized() const
{
    T len = sqrt(Real * Real + Complex * Complex);

    return {
        Real / len,
        Complex / len
    };
}
template<typename T>
T Spinor<T>::getLength() const
{
    return sqrt(Real * Real + Complex * Complex);
}

template<typename T>
T Spinor<T>::getAngle() const
{
    return atan2(Complex, Real) * 2;
}

// Interpolation
template<typename T>
Spinor<T> Spinor<T>::slerp(const Spinor<T>& other, T delta) const
{
    T tr, tc, omega, cosom, sinom, scale0, scale1;
    cosom = Real * other.Real + Complex * other.Complex;

    if (cosom < 0)
    {
        cosom = -cosom;
        tc = -other.Complex;
        tr = -other.Real;
    }
    else
    {
        tc = other.Complex;
        tr = other.Real;
    }

    if (1 - cosom > T(0.001))
    {
        omega = acos(cosom);
        sinom = sin(omega);
        scale0 = sin((1 - delta) * omega) / sinom;
        scale1 = sin(delta * omega) / sinom;
    }
    else
    {
        scale0 = 1 - delta;
        scale1 = delta;
    }

    return Spinor(scale0 * Real + scale1 * tr, scale0 * Complex + scale1 * tc);
}

template struct Core::Math::Spinor<float>;
template struct Core::Math::Spinor<double>;
