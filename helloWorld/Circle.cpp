#include "Circle.h"

Circle::Circle() {
	radius = 1.0;
	color = "red";
}

Circle::Circle(double r) {
	radius = r;
	color = "verde";
}

Circle::Circle(double r, std::string c) {
	radius = r;
	color = c;
}

double Circle::getRadius() {
	return radius;
}

std::string Circle::getColor(){
	return color;
}

void Circle::setRadius(double r){
	radius = r;
}

void Circle::setColor(std::string c){
	color = c;
}

double Circle::getArea() {
	return 3.14159*radius*radius;
}