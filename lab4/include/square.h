#pragma once
#include <cmath>
#include <iostream>

#include "figure.h"

template <Scalar T>
class Square : public Figure<T> {
private:
    static T distance(const Point<T>& a, const Point<T>& b) {
        T dx = a.x - b.x;
        T dy = a.y - b.y;
        return std::sqrt(dx * dx + dy * dy);
    }
    
    static bool isRightAngle(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
        T abx = b.x - a.x;
        T aby = b.y - a.y;
        T bcx = c.x - b.x;
        T bcy = c.y - b.y;
        
        T dot = abx * bcx + aby * bcy;
        return std::abs(dot) < 1e-9;
    }

public:
    Square(const Point<T>& point1, const Point<T>& point2, const Point<T>& point3,
           const Point<T>& point4) {
        this->size_ = 4;
        this->points_ = std::make_unique<Point<T>[]>(4);

        this->points_[0] = point1;
        this->points_[1] = point2;
        this->points_[2] = point3;
        this->points_[3] = point4;
        
        T side1 = distance(point1, point2);
        T side2 = distance(point2, point3);
        T side3 = distance(point3, point4);
        T side4 = distance(point4, point1);
        
        if (!(std::abs(side1 - side2) < 1e-9 && std::abs(side2 - side3) < 1e-9 && 
              std::abs(side3 - side4) < 1e-9 && isRightAngle(point1, point2, point3))) {
            throw std::invalid_argument("Points do not form a square");
        }
    }

    Square() = default;

    Square(const Square& other) {
        this->size_ = other.size_;
        this->points_ = std::make_unique<Point<T>[]>(this->size_);

        for (size_t i = 0; i < this->size_; ++i)
            this->points_[i] = other.points_[i];
    }

    Point<T> getCenter() const override {
        T cx = 0, cy = 0;

        for (size_t i = 0; i < this->size_; ++i) {
            cx += this->points_[i].x;
            cy += this->points_[i].y;
        }

        return Point<T>(cx / this->size_, cy / this->size_);
    }

    double getArea() const override {
        T side = distance(this->points_[0], this->points_[1]);
        return static_cast<double>(side * side);
    }

    void print(std::ostream& os) const override {
        for (size_t i = 0; i < this->size_; ++i)
            os << "(" << this->points_[i].x << "," << this->points_[i].y << ") ";
        os << "Area = " << getArea() << " ";
        os << "Center: (" << getCenter().x << "," << getCenter().y << ")" << std::endl;
    }

    void read(std::istream& is) override {
        this->size_ = 4;
        this->points_ = std::make_unique<Point<T>[]>(4);

        for (size_t i = 0; i < this->size_; ++i)
            is >> this->points_[i].x >> this->points_[i].y;
            
        T side1 = distance(this->points_[0], this->points_[1]);
        T side2 = distance(this->points_[1], this->points_[2]);
        T side3 = distance(this->points_[2], this->points_[3]);
        T side4 = distance(this->points_[3], this->points_[0]);
        
        if (!(std::abs(side1 - side2) < 1e-9 && std::abs(side2 - side3) < 1e-9 && 
              std::abs(side3 - side4) < 1e-9 && isRightAngle(this->points_[0], this->points_[1], this->points_[2]))) {
            throw std::invalid_argument("Read points do not form a square");
        }
    }

    bool operator==(const Square<T>& other) const {
        for (size_t i = 0; i < 4; ++i)
            if (!(this->points_[i] == other.points_[i]))
                return false;
        return true;
    }

    bool operator==(const Figure<T>& other) const override {
        const Square<T>* square = dynamic_cast<const Square<T>*>(&other);
        if (!square)
            return false;
        return *this == *square;
    }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Square<T>>(*this);
    }
    
    T getSideLength() const {
        return distance(this->points_[0], this->points_[1]);
    }
};