#include "../include/array.h"

#include <gtest/gtest.h>

#include "../include/square.h"
#include "../include/rectangle.h"
#include "../include/trapezoid.h"

template <Scalar T>
shared_ptr<Square<T>> makeSquare() {
    return make_shared<Square<T>>(Point<T>(0, 0), Point<T>(2, 0), Point<T>(2, 2), Point<T>(0, 2));
}

template <Scalar T>
shared_ptr<Rectangle<T>> makeRectangle() {
    return make_shared<Rectangle<T>>(Point<T>(0, 0), Point<T>(4, 0), Point<T>(4, 2), Point<T>(0, 2));
}

template <Scalar T>
shared_ptr<Trapezoid<T>> makeTrapezoid() {
    return make_shared<Trapezoid<T>>(Point<T>(0, 0), Point<T>(5, 0), Point<T>(4, 3), Point<T>(1, 3));
}

TEST(ArrayTest, AddAndGetFigures) {
    Array<int> array;
    auto square = makeSquare<int>();
    auto rectangle = makeRectangle<int>();
    auto trapezoid = makeTrapezoid<int>();

    array.addFigure(square);
    array.addFigure(rectangle);
    array.addFigure(trapezoid);

    EXPECT_EQ(array.getSize(), 3);
    EXPECT_EQ(array.getFigure(0), square);
    EXPECT_EQ(array.getFigure(1), rectangle);
    EXPECT_EQ(array.getFigure(2), trapezoid);

    EXPECT_EQ(array[0], square);
    EXPECT_EQ(array[1], rectangle);
    EXPECT_EQ(array[2], trapezoid);
}

TEST(ArrayTest, TotalArea) {
    Array<int> array;
    auto square = makeSquare<int>();
    auto rectangle = makeRectangle<int>();
    auto trapezoid = makeTrapezoid<int>();

    array.addFigure(square);
    array.addFigure(rectangle);
    array.addFigure(trapezoid);

    double expected_area = static_cast<double>(*square) + static_cast<double>(*rectangle) +
                           static_cast<double>(*trapezoid);
    EXPECT_DOUBLE_EQ(array.getAllArea(), expected_area);
}

TEST(ArrayTest, RemoveFigure) {
    Array<int> array;
    auto square = makeSquare<int>();
    auto rectangle = makeRectangle<int>();
    auto trapezoid = makeTrapezoid<int>();

    array.addFigure(square);
    array.addFigure(rectangle);
    array.addFigure(trapezoid);

    array.removeFigure(1);
    EXPECT_EQ(array.getSize(), 2);
    EXPECT_EQ(array.getFigure(0), square);
    EXPECT_EQ(array.getFigure(1), trapezoid);

    array.removeFigure(0);
    EXPECT_EQ(array.getSize(), 1);
    EXPECT_EQ(array.getFigure(0), trapezoid);

    array.removeFigure(0);
    EXPECT_EQ(array.getSize(), 0);

    array.removeFigure(0);
    EXPECT_EQ(array.getSize(), 0);
}

TEST(ArrayTest, CopyArray) {
    Array<int> array1;
    auto square = makeSquare<int>();
    array1.addFigure(square);

    Array<int> array2 = array1;
    EXPECT_EQ(array2.getSize(), array1.getSize());
    EXPECT_NE(array2.getFigure(0), array1.getFigure(0));
    EXPECT_EQ(static_cast<double>(*array2.getFigure(0)), static_cast<double>(*array1.getFigure(0)));
}

TEST(ArrayTest, MoveArray) {
    Array<int> array1;
    auto square = makeSquare<int>();
    array1.addFigure(square);

    Array<int> array2 = std::move(array1);
    EXPECT_EQ(array2.getSize(), 1);
    EXPECT_EQ(array1.getSize(), 0);
}

TEST(ArrayTest, ResizeArray) {
    Array<int> array(2);
    auto square = makeSquare<int>();
    auto rectangle = makeRectangle<int>();
    auto trapezoid = makeTrapezoid<int>();

    array.addFigure(square);
    array.addFigure(rectangle);
    EXPECT_EQ(array.getCapacity(), 2);

    array.addFigure(trapezoid);
    EXPECT_GE(array.getCapacity(), 3);
    EXPECT_EQ(array.getSize(), 3);
}

TEST(ArrayTest, IndexOutOfBounds) {
    Array<int> array;
    auto square = makeSquare<int>();
    array.addFigure(square);

    EXPECT_EQ(array.getFigure(10), nullptr);
    EXPECT_EQ(array[10], nullptr);
}

TEST(ArrayTest, PrintFigures) {
    Array<int> array;
    auto square = makeSquare<int>();
    array.addFigure(square);

    EXPECT_NO_THROW(array.printFigures());
}

TEST(SquareTest, AreaCalculation) {
    auto square = makeSquare<int>();
    EXPECT_DOUBLE_EQ(static_cast<double>(*square), 4.0);
}

TEST(SquareTest, CenterCalculation) {
    auto square = makeSquare<int>();
    Point<int> center = square->getCenter();
    EXPECT_EQ(center.x, 1);
    EXPECT_EQ(center.y, 1);
}

TEST(SquareTest, Equality) {
    auto square1 = makeSquare<int>();
    auto square2 = makeSquare<int>();
    EXPECT_TRUE(*square1 == *square2);
}

TEST(RectangleTest, AreaCalculation) {
    auto rectangle = makeRectangle<int>();
    EXPECT_DOUBLE_EQ(static_cast<double>(*rectangle), 8.0);
}

TEST(RectangleTest, CenterCalculation) {
    auto rectangle = makeRectangle<int>();
    Point<int> center = rectangle->getCenter();
    EXPECT_EQ(center.x, 2);
    EXPECT_EQ(center.y, 1);
}

TEST(RectangleTest, Equality) {
    auto rectangle1 = makeRectangle<int>();
    auto rectangle2 = makeRectangle<int>();
    EXPECT_TRUE(*rectangle1 == *rectangle2);
}

TEST(TrapezoidTest, AreaCalculation) {
    auto trapezoid = makeTrapezoid<int>();
    double area = trapezoid->getArea();
    EXPECT_GT(area, 0);
}

TEST(TrapezoidTest, CenterCalculation) {
    auto trapezoid = makeTrapezoid<int>();
    Point<int> center = trapezoid->getCenter();
    EXPECT_NE(center.x, 0);
    EXPECT_NE(center.y, 0);
}

TEST(TrapezoidTest, Equality) {
    auto trapezoid1 = makeTrapezoid<int>();
    auto trapezoid2 = makeTrapezoid<int>();
    EXPECT_TRUE(*trapezoid1 == *trapezoid2);
}

TEST(FigureTest, SquareClone) {
    auto square = makeSquare<int>();
    auto cloned = square->clone();
    EXPECT_NE(square.get(), cloned.get());
    EXPECT_TRUE(*square == *cloned);
}

TEST(FigureTest, RectangleClone) {
    auto rectangle = makeRectangle<int>();
    auto cloned = rectangle->clone();
    EXPECT_NE(rectangle.get(), cloned.get());
    EXPECT_TRUE(*rectangle == *cloned);
}

TEST(FigureTest, TrapezoidClone) {
    auto trapezoid = makeTrapezoid<int>();
    auto cloned = trapezoid->clone();
    EXPECT_NE(trapezoid.get(), cloned.get());
    EXPECT_TRUE(*trapezoid == *cloned);
}