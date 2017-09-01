#include <iostream>
#include "Circle.h"
#include "Rectangle.h"
#include "Employee.h"
using namespace std;

int main1() {

	Circle circulo(2, "green");
	cout << circulo.getRadius() << endl;

	Rectangle rectangulo(5, 6);
	cout << rectangulo.getArea() << endl;
	cout << "Cambiando la base a 10" << endl;
	rectangulo.setWith(10);
	cout << rectangulo.getPerimeter() << endl;

	Employee empleado(123, "Adalberto", "Gutierritos", 1080);
	cout << empleado.Print() << endl;
	std::cin.get();
	return 0;
}
