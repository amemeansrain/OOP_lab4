#include <iostream>

#include "include/array.h"
#include "include/square.h"
#include "include/rectangle.h"
#include "include/trapezoid.h"

int main() {
    Square<int> square({0, 0}, {2, 0}, {2, 2}, {0, 2});
    Rectangle<int> rectangle({0, 0}, {3, 0}, {3, 2}, {0, 2});
    Trapezoid<int> trapezoid({0, 0}, {4, 0}, {3, 2}, {1, 2});

    std::cout << "Square: ";
    square.print(std::cout);

    std::cout << "Rectangle: ";
    rectangle.print(std::cout);

    std::cout << "Trapezoid: ";
    trapezoid.print(std::cout);

    std::cout << std::endl;

    Array<int> array(4);
    array.addFigure(std::make_shared<Square<int>>(square));
    array.addFigure(std::make_shared<Rectangle<int>>(rectangle));
    array.addFigure(std::make_shared<Trapezoid<int>>(trapezoid));

    std::cout << "All figures in array:" << std::endl;
    array.printFigures();

    std::cout << "Total area: " << array.getAllArea() << std::endl;

    std::cout << std::endl;

    std::shared_ptr<Figure<int>> figure = array[2];
    std::cout << "Figure at index 2: ";
    figure->print(std::cout);
    std::cout << "Area: " << static_cast<double>(*figure) << std::endl;

    return 0;
}