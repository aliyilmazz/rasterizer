#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H

#include <iostream>

class Color {

public:
    float _channels[3];
    Color();
    Color(float r, float g, float b);

    float R() const
    {
        return _channels[0];
    }

    float G() const
    {
        return _channels[1];
    }

    float B() const
    {
        return _channels[2];
    }

    Color operator+(const Color& rhs) const
    {
        Color ret;
        ret._channels[0] = _channels[0] + rhs.R();
        ret._channels[1] = _channels[1] + rhs.G();
        ret._channels[2] = _channels[2] + rhs.B();
        return ret;
    }

    Color operator-(const Color& rhs) const
    {
        Color ret;
        ret._channels[0] = _channels[0] - rhs.R();
        ret._channels[1] = _channels[1] - rhs.G();
        ret._channels[2] = _channels[2] - rhs.B();
        return ret;
    }

    Color operator*(const Color& rhs) const
    {
        Color ret;
        ret._channels[0] = _channels[0] * rhs.R();
        ret._channels[1] = _channels[1] * rhs.G();
        ret._channels[2] = _channels[2] * rhs.B();
        return ret;
    }

    Color operator*(float c) const
    {
        return Color(_channels[0] * c,
                     _channels[1] * c,
                     _channels[2] * c);
    }

    Color operator/(float denom) const
    {
        return (*this) * (1 / denom);
    }

    friend inline std::istream &operator>>(std::istream &stream, Color &color)
    {
        return stream >> color._channels[0] >> color._channels[1] >> color._channels[2];
    }
    friend inline std::ostream &operator<<(std::ostream &os, Color &color)
    {
        os << color.R() << " " << color.G() << " " << color.B();
        return os;
    }
};


inline Color::Color()
{
    _channels[0] = _channels[1] = _channels[2] = 0;
}

inline Color::Color(float r, float g, float b) {
    _channels[0] = std::max(0.0f, std::min(255.0f, r));
    _channels[1] = std::max(0.0f, std::min(255.0f, g));
    _channels[2] = std::max(0.0f, std::min(255.0f, b));
}


#endif //RAYTRACER_COLOR_H
