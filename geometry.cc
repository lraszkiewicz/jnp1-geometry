// Łukasz Raszkiewicz, Konrad Majewski

#include <cassert>
#include "geometry.h"

// Position methods implementation
Position::Position(int x, int y)
    : x_(x), y_(y) {}

int Position::x() const {
    return x_;
}

int Position::y() const {
    return y_;
}

Position Position::reflection() const {
    return Position(y_, x_);
}

const Position Position::origin() {
    static const Position origin_field = Position(0, 0);
    return origin_field;
}

bool Position::operator==(const Position& other) const {
    return x_ == other.x_ && y_ == other.y_;
}

Position& Position::operator+=(const Vector& other) {
    x_ += other.x();
    y_ += other.y();
    return *this;
}

Position Position::operator+(const Vector& other) const {
    return Position(*this) += other;
}

// Vector methods implementation
Vector::Vector(int x, int y)
    : point(Position(x,y)) {}

int Vector::x() const {
    return point.x();
}

int Vector::y() const {
    return point.y();
}

Vector Vector::reflection() const {
    return Vector(y(), x());
}

bool Vector::operator==(const Vector& other) const {
    return point == other.point;
}

Vector& Vector::operator+=(const Vector& other) {
    point += other;
    return *this;
}

Position Vector::operator+(const Position& other) const {
    return other + *this;
}

Vector Vector::operator+(const Vector& other) const {
    return Vector(*this) += other;
}

Rectangle Vector::operator+(const Rectangle& other) const {
    return other + *this;
}

// Rectangle methods implementation
Rectangle::Rectangle(int width, int height, Position pos)
    : width_(width), height_(height), bottom_left(pos) {
    assert(width > 0);
    assert(height > 0);
}

Rectangle::Rectangle(int width, int height)
    : Rectangle(width, height, Position::origin()) {}

int Rectangle::width() const {
    return width_;
}

int Rectangle::height() const {
    return height_;
}

Position Rectangle::pos() const {
    return bottom_left;
}

Rectangle Rectangle::reflection() const {
    return Rectangle(height_, width_, bottom_left.reflection());
}

int Rectangle::area() const {
    return width_ * height_;
}

std::pair<Rectangle, Rectangle> Rectangle::split_horizontally(int place) const {
    assert(bottom_left.y() < place && place < bottom_left.y() + height_);
    return {
        Rectangle(width_, place - bottom_left.y(), bottom_left),
        Rectangle(width_, bottom_left.y() + height_ - place,
            bottom_left + Vector(0, place - bottom_left.y()))
    };
}

std::pair<Rectangle, Rectangle> Rectangle::split_vertically(int place) const {
    assert(bottom_left.x() < place && place < bottom_left.x() + width_);
    return {
        Rectangle(place - bottom_left.x(), height_, bottom_left),
        Rectangle(bottom_left.x() + width_ - place, height_,
            bottom_left + Vector(place - bottom_left.x(), 0))
    };
}

bool Rectangle::operator==(const Rectangle& other) const {
    return width_ == other.width_
        && height_ == other.height_
        && bottom_left == other.bottom_left;
}

Rectangle& Rectangle::operator+=(const Vector& other) {
    bottom_left += other;
    return *this;
}

Rectangle Rectangle::operator+(const Vector& other) const {
    return Rectangle(*this) += other;
}

// Additional functions implementation
Rectangle merge_horizontally(const Rectangle& rect1, const Rectangle& rect2) {
    assert(rect1.width() == rect2.width());
    assert(rect1.pos() + Vector(0, rect1.height()) == rect2.pos());
    return Rectangle(rect1.width(), rect1.height() + rect2.height(), rect1.pos());
}

Rectangle merge_vertically(const Rectangle& rect1, const Rectangle& rect2) {
    assert(rect1.height() == rect2.height());
    assert(rect1.pos() + Vector(rect1.width(), 0) == rect2.pos());
    return Rectangle(rect1.width() + rect2.width(), rect1.height(), rect1.pos());
}

// Rectangles methods implementation
Rectangles::Rectangles() {};

Rectangles::Rectangles(std::initializer_list<Rectangle> recs)
    : rectangle_list(recs) {};

size_t Rectangles::size() const {
    return rectangle_list.size();
}

void Rectangles::split_horizontally(size_t idx, int place) {
    assert(idx < rectangle_list.size());
    auto it = rectangle_list.begin() + idx;
    auto new_recs = (*it).split_horizontally(place);
    it = rectangle_list.erase(it);
    rectangle_list.insert(it, new_recs.first);
    rectangle_list.insert(it, new_recs.second);
}

void Rectangles::split_vertically(size_t idx, int place) {
    assert(idx < rectangle_list.size());
    auto it = rectangle_list.begin() + idx;
    auto new_recs = (*it).split_vertically(place);
    it = rectangle_list.erase(it);
    rectangle_list.insert(it, new_recs.first);
    rectangle_list.insert(it, new_recs.second);
}

Rectangle& Rectangles::operator[](size_t i) {
    assert(i < rectangle_list.size());
    return rectangle_list[i];
}

bool Rectangles::operator==(const Rectangles& other) const {
    return rectangle_list == other.rectangle_list;
}

Rectangles& Rectangles::operator+=(const Vector& other) {
    for (Rectangle rec : rectangle_list)
        rec += other;
    return *this;
}
