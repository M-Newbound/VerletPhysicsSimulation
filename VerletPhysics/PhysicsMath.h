#pragma once

namespace VerletPhysics {

    constexpr static double PI = 3.1415;
    constexpr static double TWO_PI = 2 * PI;


    /**
    * A representation a 2D vector with x and y components.
    *
    * Provides a representation of a 2D vector with x and y coordinates.
    * It offers basic mathematical operations for vector addition, subtraction, scalar
    * multiplication, and scalar division.
    */
    struct Vector2
    {

    private:
        double m_x;
        double m_y;

    public:

        Vector2() : m_x(0.0), m_y(0.0) {}
        Vector2(double x, double y) : m_x(x), m_y(y) {}

        double x() const { return m_x; }
        double y() const { return m_y; }

        Vector2& operator=(const Vector2& other);

        /**
         * Overloads the + operator to perform vector addition.
         *
         * This operator allows you to add two Vector2 objects together, resulting
         * in a new Vector2 representing the sum of their components.
         *
         * @param other The Vector2 to be added.
         * @return A new Vector2 representing the result of the addition.
         */
        Vector2 operator+(const Vector2& other) const;

        /**
         * Overloads the - operator to perform vector subtraction.
         *
         * This operator allows you to subtract one Vector2 object from another,
         * resulting in a new Vector2 representing the difference of their components.
         *
         * @param other The Vector2 to be subtracted.
         * @return A new Vector2 representing the result of the subtraction.
         */
        Vector2 operator-(const Vector2& other) const;

        /**
         * Overloads the * operator to perform scalar multiplication.
         *
         * This operator allows you to multiply a Vector2 by a scalar value, resulting
         * in a new Vector2 where each component is multiplied by the scalar.
         *
         * @param scalar The scalar value to multiply the vector by.
         * @return A new Vector2 representing the result of the multiplication.
         */
        Vector2 operator*(double scalar) const;

        /**
         * Overloads the / operator to perform scalar division.
         *
         * This operator allows you to divide a Vector2 by a scalar value, resulting
         * in a new Vector2 where each component is divided by the scalar.
         *
         * @param scalar The scalar value to divide the vector by.
         * @return A new Vector2 representing the result of the division.
         *
         * @note Any division by zero will return a zerod Vector2.
         */
        Vector2 operator/(double scalar) const;


    };

    struct VectorMath
    {
        /**
         * Calculate the magnitude (length) of a Vector2D.
         *
         * @param vec The Vector2D whose magnitude is to be calculated.
         * @return The magnitude of the Vector2D.
         */
        static double magnitude(const Vector2& vec);

        /**
         * Calculate the squared magnitude of a Vector2D.
         *
         * This avoids the square root operation, which can be computationally
         * expensive and is useful when comparing vector lengths.
         *
         * @param vec The Vector2D whose squared magnitude is to be calculated.
         * @return The squared magnitude of the Vector2D.
         */
        static double magnitudeSquared(const Vector2& vec);

        /**
         * Normalize a Vector2D (make it a unit vector with magnitude 1).
         *
         * @param vec The Vector2D to be normalized.
         * @return A new normalized Vector2D.
         */
        static Vector2 normalize(const Vector2& vec);

        /**
         * Calculate the dot product of two Vector2D objects.
         *
         * @param vec1 The first Vector2D.
         * @param vec2 The second Vector2D.
         * @return The dot product of the two vectors.
         */
        static double dotProduct(const Vector2& vec1, const Vector2& vec2);



    };


};
