#pragma once
#include <string>
class Rectangle {
public:
	Rectangle();
	Rectangle(float w, float h);

	float getWith();
	void setWith(float w);
	
	float getHeight();
	void setHeight(float h);

	float getArea();
	float getPerimeter();

private:
	float width;
	float height;
};