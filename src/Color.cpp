#include <iostream>
#include "Color.h"
#include <cmath>

Color::Color() : r(0), b(0), g(0)
{
}

Color::Color(float iR, float iG, float iB) : r(iR), g(iG), b(iB)
{
}

Color::~Color()
{
}

float Color::R()
{
    return r;
}

float Color::G()
{
    return g;
}

float Color::B()
{
    return b;
}

Color Color::operator+(Color const& col) {
    Color c;
    c.r = fmax(fmin(r + col.r, 1), 0);
    c.g = fmax(fmin(g + col.g, 1), 0);
    c.b = fmax(fmin(b + col.b, 1), 0);
    return c;
}

Color Color::operator*(Color const& col) const {
    return Color(r * col.r, g * col.g, b * col.b);
}

Color Color::operator*(float scalar) const {
    return Color(r * scalar, g * scalar, b * scalar);
}

Color& Color::operator=(Color const& col) {
    r = col.r;
    g = col.g;
    b = col.b;
    return *this;
}

std::ostream & operator<<(std::ostream & _stream, Color const & col) {
    return _stream << "(" << col.r << "," << col.g << "," << col.b << ")";
}