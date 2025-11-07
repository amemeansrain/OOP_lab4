#pragma once
#include <cmath>
#include <iostream>

#include "figure.h"

template <Scalar T>
class Trapezoid : public Figure<T> {
private:
    static T distance(const Point<T>& a, const Point<T>& b) {
        T dx = a.x - b.x;
        T dy = a.y - b.y;
        return std::sqrt(dx * dx + dy * dy);
    }
    
    static bool areParallel(const Point<T>& a1, const Point<T>& a2, 
                           const Point<T>& b1, const Point<T>& b2) {
        T vec1_x = a2.x - a1.x;
        T vec1_y = a2.y - a1.y;
        T vec2_x = b2.x - b1.x;
        T vec2_y = b2.y - b1.y;
        
        T cross = vec1_x * vec2_y - vec1_y * vec2_x;
        return std::abs(cross) < 1e-9;
    }

public:
    Trapezoid(const Point<T>& point1, const Point<T>& point2, const Point<T>& point3,
              const Point<T>& point4) {
        this->size_ = 4;
        this->points_ = std::make_unique<Point<T>[]>(4);

        this->points_[0] = point1;
        this->points_[1] = point2;
        this->points_[2] = point3;
        this->points_[3] = point4;
        
        bool isTrapezoid = areParallel(point1, point2, point3, point4) ||
                          areParallel(point2, point3, point4, point1);
        
        if (!isTrapezoid) {
            throw std::invalid_argument("Points do not form a trapezoid");
        }
    }

    Trapezoid() = default;

    Trapezoid(const Trapezoid& other) {
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
        T base1, base2, height;
        
        if (areParallel(this->points_[0], this->points_[1], this->points_[2], this->points_[3])) {
            base1 = distance(this->points_[0], this->points_[1]);
            base2 = distance(this->points_[2], this->points_[3]);
            height = calculateHeight(this->points_[0], this->points_[1], this->points_[2]);
        } else {
            base1 = distance(this->points_[1], this->points_[2]);
            base2 = distance(this->points_[3], this->points_[0]);
            height = calculateHeight(this->points_[1], this->points_[2], this->points_[3]);
        }
        
        return static_cast<double>((base1 + base2) * height) / 2.0;
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
            
        bool isTrapezoid = areParallel(this->points_[0], this->points_[1], 
                                      this->points_[2], this->points_[3]) ||
                          areParallel(this->points_[1], this->points_[2], 
                                      this->points_[3], this->points_[0]);
        
        if (!isTrapezoid) {
            throw std::invalid_argument("Read points do not form a trapezoid");
        }
    }

    bool operator==(const Trapezoid<T>& other) const {
        for (size_t i = 0; i < 4; ++i)
            if (!(this->points_[i] == other.points_[i]))
                return false;
        return true;
    }

    bool operator==(const Figure<T>& other) const override {
        const Trapezoid<T>* trapezoid = dynamic_cast<const Trapezoid<T>*>(&other);
        if (!trapezoid)
            return false;
        return *this == *trapezoid;
    }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Trapezoid<T>>(*this);
    }

private:
    T calculateHeight(const Point<T>& linePoint1, const Point<T>& linePoint2, 
                     const Point<T>& point) const {
        T A = linePoint2.y - linePoint1.y;
        T B = linePoint1.x - linePoint2.x;
        T C = linePoint2.x * linePoint1.y - linePoint1.x * linePoint2.y;
        
        return std::abs(A * point.x + B * point.y + C) / std::sqrt(A * A + B * B);
    }
};