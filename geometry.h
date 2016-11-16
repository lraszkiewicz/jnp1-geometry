// Łukasz Raszkiewicz, Konrad Majewski

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <utility>
#include <vector>

class Position;
class Vector;
class Rectangle;
class Rectangles;

class Position {
public:
    Position(int32_t x, int32_t y);
    int32_t x() const;
    int32_t y() const;
    Position reflection() const;
    static const Position origin();
    bool operator==(const Position& other) const;
    Position& operator+=(const Vector& vec);

private:
    int32_t x_, y_;
};

class Vector {
public:
    Vector(int32_t x, int32_t y);
    int32_t x() const;
    int32_t y() const;
    Vector reflection() const;
    bool operator==(const Vector& other) const;
    Vector& operator+=(const Vector& vec);

private:
    Position point;
};

class Rectangle {
public:
    Rectangle(int32_t width, int32_t height, Position pos);
    Rectangle(int32_t width, int32_t height);
    int32_t width() const;
    int32_t height() const;
    Position pos() const;
    Rectangle reflection() const;
    int32_t area() const;
    std::pair<Rectangle, Rectangle> split_horizontally(int32_t place) const;
    std::pair<Rectangle, Rectangle> split_vertically(int32_t place) const;
    bool operator==(const Rectangle& other) const;
    Rectangle& operator+=(const Vector& vec);

private:
    int32_t width_;
    int32_t height_;
    Position bottom_left;
};

class Rectangles {
public:
    Rectangles();
    Rectangles(std::initializer_list<Rectangle> recs);
    size_t size() const;
    void split_horizontally(size_t idx, int32_t place);
    void split_vertically(size_t idx, int32_t place);
    Rectangle& operator[](size_t i);
    bool operator==(const Rectangles& other) const;
    Rectangles& operator+=(const Vector& vec);

private:
    std::vector<Rectangle> rectangle_list;
    void split(size_t idx, int32_t place, bool horizontally);
};

const Position operator+(const Position& pos, const Vector& vec);
const Position operator+(Position&& pos, const Vector& vec);
const Position operator+(const Vector& vec, const Position& pos);
const Position operator+(const Vector& vec, Position&& pos);

const Vector operator+(const Vector& vec1, const Vector& vec2);
const Vector operator+(Vector&& vec1, const Vector& vec2);
const Vector operator+(const Vector& vec1, Vector&& vec2);
const Vector operator+(Vector&& vec1, Vector&& vec2);

const Rectangle operator+(const Rectangle& rec, const Vector& vec);
const Rectangle operator+(Rectangle&& rec, const Vector& vec);
const Rectangle operator+(const Vector& vec, const Rectangle& rec);
const Rectangle operator+(const Vector& vec, Rectangle&& rec);

const Rectangles operator+(const Rectangles& recs, const Vector& vec);
const Rectangles operator+(Rectangles&& recs, const Vector& vec);
const Rectangles operator+(const Vector& vec, const Rectangles& recs);
const Rectangles operator+(const Vector& vec, Rectangles&& recs);

Rectangle merge_horizontally(const Rectangle& rect1, const Rectangle& rect2);
Rectangle merge_vertically(const Rectangle& rect1, const Rectangle& rect2);

#endif  // GEOMETRY_H_
