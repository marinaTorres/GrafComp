#include "Rectangle.h"

Rectangle::Rectangle(){
	width = 1.0f;
	height = 1.0f;
}

Rectangle::Rectangle(float w, float h){
	width = w;
	height = h;
}

float Rectangle::getWith(){
	return width;
}

void Rectangle::setWith(float w){
	width = w;
}

float Rectangle::getHeight()
{
	return height;
}

void Rectangle::setHeight(float h){
	height = h;
}

float Rectangle::getArea()
{
	return height*width;
}

float Rectangle::getPerimeter()
{
	return 2*height+2*width;
}
