// Łukasz Raszkiewicz, Konrad Majewski
#ifndef GEOMETRY_H_
#define GEOMETRY_H_
#include <utility>

class Position {

};

class Vector {
public:
    Vector(int x, int y);
    bool operator==(const Vector &other) const;
    int x() const;
    int y() const;
    Vector reflection() const;
    Vector & operator+=(const Vector &vec);

private:
    Position point;
};

class Rectangle {
public:
    Rectangle(unsigned int width, unsigned int height, Position pos);
    Rectangle(unsigned int width, unsigned int height);
    bool operator==(const Rectangle &other) const;
    unsigned int width() const;
    unsigned int height() const;
    Position pos() const;
    Rectangle reflection() const;
    Rectangle & operator+=(const Vector &vec);
    unsigned int area() const;
    std::pair<Rectangle, Rectangle> split_horizontally(int place) const;
    std::pair<Rectangle, Rectangle> split_vertically(int place) const;

private:
    unsigned int width_;
    unsigned int height_;
    Position bottom_left;
};

#endif // GEOMETRY_H_