#include "PhysicsMath.h"
#include <cmath>

using namespace VerletPhysics;

Vector2& Vector2::operator=(const Vector2& other)
{
    m_x = other.x();
    m_y = other.y();
    return *this;
}

Vector2 Vector2::operator+(const Vector2& other) const
{
    return Vector2(x() + other.x(), y() + other.y());
}

Vector2 Vector2::operator-(const Vector2& other) const
{
    return Vector2(x() - other.x(), y() - other.y());
}

Vector2 Vector2::operator*(double scalar) const
{
    return Vector2(x() * scalar, y() * scalar);
}

Vector2 Vector2::operator/(double scalar) const
{
    if (scalar == 0.0) return Vector2(0, 0);
    return Vector2(x() / scalar, y() / scalar);
}


double VectorMath::magnitude(const Vector2& vec)
{
    return std::sqrt(vec.x() * vec.x() + vec.y() * vec.y());
}

double VectorMath::magnitudeSquared(const Vector2& vec)
{
    return vec.x() * vec.x() + vec.y() * vec.y();
}

Vector2 VectorMath::normalize(const Vector2& vec)
{
    double magnitude = VectorMath::magnitude(vec);
    if (magnitude == 0.0) return Vector2(0.0, 0.0);

    return Vector2(vec.x() / magnitude, vec.y() / magnitude);
}

double VectorMath::dotProduct(const Vector2& vec1, const Vector2& vec2)
{
    return vec1.x() * vec2.x() + vec1.y() * vec2.y();
}
