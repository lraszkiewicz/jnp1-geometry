// Łukasz Raszkiewicz, Konrad Majewski

#include <cassert>
#include "geometry.h"

// Position methods implementation
Position::Position(int32_t x, int32_t y)
    : x_(x), y_(y) {}

int32_t Position::x() const {
    return x_;
}

int32_t Position::y() const {
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

Position& Position::operator+=(const Vector& vec) {
    x_ += vec.x();
    y_ += vec.y();
    return *this;
}

// Vector methods implementation
Vector::Vector(int32_t x, int32_t y)
    : point(Position(x,y)) {}

int32_t Vector::x() const {
    return point.x();
}

int32_t Vector::y() const {
    return point.y();
}

Vector Vector::reflection() const {
    return Vector(y(), x());
}

bool Vector::operator==(const Vector& other) const {
    return point == other.point;
}

Vector& Vector::operator+=(const Vector& vec) {
    point += vec;
    return *this;
}

// Rectangle methods implementation
Rectangle::Rectangle(int32_t width, int32_t height, Position pos)
    : width_(width), height_(height), bottom_left(pos) {
    assert(width > 0);
    assert(height > 0);
}

Rectangle::Rectangle(int32_t width, int32_t height)
    : Rectangle(width, height, Position::origin()) {}

int32_t Rectangle::width() const {
    return width_;
}

int32_t Rectangle::height() const {
    return height_;
}

Position Rectangle::pos() const {
    return bottom_left;
}

Rectangle Rectangle::reflection() const {
    return Rectangle(height_, width_, bottom_left.reflection());
}

int32_t Rectangle::area() const {
    return width_ * height_;
}

std::pair<Rectangle, Rectangle> Rectangle::split_horizontally(int32_t place) const {
    assert(bottom_left.y() < place && place < bottom_left.y() + height_);
    return {
        Rectangle(width_, place - bottom_left.y(), bottom_left),
        Rectangle(width_, bottom_left.y() + height_ - place,
            bottom_left + Vector(0, place - bottom_left.y()))
    };
}

std::pair<Rectangle, Rectangle> Rectangle::split_vertically(int32_t place) const {
    auto rect_pair = reflection().split_horizontally(place);
    return {
            rect_pair.first.reflection(),
            rect_pair.second.reflection()
    };
}

bool Rectangle::operator==(const Rectangle& other) const {
    return width_ == other.width_
        && height_ == other.height_
        && bottom_left == other.bottom_left;
}

Rectangle& Rectangle::operator+=(const Vector& vec) {
    bottom_left += vec;
    return *this;
}

// Rectangles methods implementation
Rectangles::Rectangles() {};

Rectangles::Rectangles(std::initializer_list<Rectangle> recs)
    : rectangle_list(recs) {};

size_t Rectangles::size() const {
    return rectangle_list.size();
}

void Rectangles::split_horizontally(size_t idx, int32_t place) {
    assert(idx < rectangle_list.size());
    auto it = rectangle_list.begin() + idx;
    auto new_recs = (*it).split_horizontally(place);
    it = rectangle_list.erase(it);
    rectangle_list.insert(it, new_recs.first);
    rectangle_list.insert(it, new_recs.second);
}

void Rectangles::split_vertically(size_t idx, int32_t place) {
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

Rectangles& Rectangles::operator+=(const Vector& vec) {
    for (Rectangle& rec : rectangle_list)
        rec += vec;
    return *this;
}

// Additional operators implementation
const Position operator+(Position pos, const Vector& vec) {
    return pos += vec;
}

const Position operator+(Position&& pos, const Vector& vec) {
    return std::move(pos) += vec;
}

const Position operator+(const Vector& vec, Position pos) {
    return pos + vec;
}

const Position operator+(const Vector& vec, Position&& pos) {
    return pos + vec;
}

// Additional functions implementation
Rectangle merge_horizontally(const Rectangle& rect1, const Rectangle& rect2) {
    assert(rect1.width() == rect2.width());
    assert(rect1.pos() + Vector(0, rect1.height()) == rect2.pos());
    return Rectangle(rect1.width(), rect1.height() + rect2.height(), rect1.pos());
}

Rectangle merge_vertically(const Rectangle& rect1, const Rectangle& rect2) {
    return merge_horizontally(rect1.reflection(), rect2.reflection()).reflection();
}