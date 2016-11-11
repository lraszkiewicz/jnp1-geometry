// Łukasz Raszkiewicz, Konrad Majewski

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <utility>

class Position;
class Vector;
class Rectangle;

class Position {
public:
    Position(int x, int y);
    int x() const;
    int y() const;
    Position reflection() const;
    static const Position origin();
    bool operator==(const Position& other) const;
    Position& operator+=(const Vector& other);
    Position operator+(const Vector& other) const;

private:
    int x_, y_;
};

class Vector {
public:
    Vector(int x, int y);
    int x() const;
    int y() const;
    Vector reflection() const;
    bool operator==(const Vector& other) const;
    Vector& operator+=(const Vector& other);
    Position operator+(const Position& other) const;
    Vector operator+(const Vector& other) const;
    Rectangle operator+(const Rectangle& other) const;
    // Rectangles operator+(const Rectangles& other);

private:
    Position point;
};

class Rectangle {
public:
    Rectangle(unsigned int width, unsigned int height, Position pos);
    Rectangle(unsigned int width, unsigned int height);
    unsigned int width() const;
    unsigned int height() const;
    Position pos() const;
    Rectangle reflection() const;
    unsigned int area() const;
    std::pair<Rectangle, Rectangle> split_horizontally(int place) const;
    std::pair<Rectangle, Rectangle> split_vertically(int place) const;
    bool operator==(const Rectangle& other) const;
    Rectangle& operator+=(const Vector& other);
    Rectangle operator+(const Vector& other) const;

private:
    unsigned int width_;
    unsigned int height_;
    Position bottom_left;
};

#endif  // GEOMETRY_H_
