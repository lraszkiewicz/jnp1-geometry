// Łukasz Raszkiewicz, Konrad Majewski

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <initializer_list>
#include <cstddef>
#include <utility>
#include <vector>

class Position;
class Vector;
class Rectangle;
class Rectangles;

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
    Rectangle(int width, int height, Position pos);
    Rectangle(int width, int height);
    int width() const;
    int height() const;
    Position pos() const;
    Rectangle reflection() const;
    int area() const;
    std::pair<Rectangle, Rectangle> split_horizontally(int place) const;
    std::pair<Rectangle, Rectangle> split_vertically(int place) const;
    bool operator==(const Rectangle& other) const;
    Rectangle& operator+=(const Vector& other);
    Rectangle operator+(const Vector& other) const;

private:
    int width_;
    int height_;
    Position bottom_left;
};

Rectangle merge_horizontally(const Rectangle& rect1, const Rectangle& rect2);
Rectangle merge_vertically(const Rectangle& rect1, const Rectangle& rect2);

class Rectangles {
public:
    Rectangles();
    Rectangles(std::initializer_list<Rectangle> recs);
    size_t size() const;
    void split_horizontally(size_t idx, int place);
    void split_vertically(size_t idx, int place);
    Rectangle& operator[](size_t i);
    bool operator==(const Rectangles& other) const;
    Rectangles& operator+=(const Vector& other);

private:
    std::vector<Rectangle> rectangle_list;
};

#endif  // GEOMETRY_H_
