#include "Image.h"
#include <algorithm>
#include <climits>

// This class has mostly consist of helper functions, you could use them when dealing image pixels.
/*
 * BEWARE!
 * DO NOT MODIFY THIS FILE
 * IT WILL BE REPLACED DURING CHECKS
 */

Image::Image(int width, int height, const Color& color)
{
    _width = width;
    _height = height;
    _pixels = new Color[(int)width*(int)height];
    _buffer = new float[(int)width*(int)height];
    for(int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            _buffer[i*width+j] = 9999999.0f;
            _pixels[i*width+j] = color;
        }
    }
}

Image::Image(const Image& rhs) : _width(rhs._width), _height(rhs._height)
{
    _pixels = new Color[_width * _height];
    std::copy(rhs._pixels, rhs._pixels + _width * _height, _pixels);
}

Image::Image(Image&& rhs) :  _width(rhs._width), _height(rhs._height), _pixels(rhs._pixels)
{
    rhs._pixels = nullptr;
}

Image::~Image()
{
    delete[] _pixels;
}

Color &Image::Pixel(int x, int y)
{
    return _pixels[x * _width + y];
}

const Color &Image::Pixel(int x, int y) const
{
    return _pixels[x * _width + y];
}

Image& Image::operator=(Image rhs)
{
    using std::swap;
    swap(_width, rhs._width);
    swap(_height, rhs._height);
    swap(_pixels, rhs._pixels);
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Image &image) {
    os << "P3" << std::endl << image._width << " " << image._height << std::endl << 255 << std::endl ;

    for (int i = 0; i < image._height; ++i) {
        for (int j = 0; j < image._width; ++j) {
            os << static_cast<int>(image.Pixel(i, j).R()) << " ";
            os << static_cast<int>(image.Pixel(i, j).G()) << " ";
            os << static_cast<int>(image.Pixel(i, j).B()) << " ";
        }
        os << std::endl;
    }

    return os;
}
