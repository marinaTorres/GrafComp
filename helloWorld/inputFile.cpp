/*********************************************************
Materia: Gráficas Computacionales
Fecha: 21 de agosto del 2017
Autor: A01375051 Marina Fernanda Torres Gómez
*********************************************************/

#include "inputFile.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

bool inputFile::read(std::string fileName) {

	fstream s(fileName);
	if (!s.is_open()) {
		return false;
	}
	else {


		//read 
		stringstream sso;
		sso << s.rdbuf();
		_contents = sso.str();
		s.close();
		return true;
	}
}

std::string inputFile::getContents() {
	return _contents;
}

/*
using namespace std;
int main4(int argc, char* argv[]) {

	std::string filename = "Prueba.txt";
	inputFile myFile;
	myFile.read(filename);
	std::string contents = myFile.getContents();
	cout << "Contents: " << contents << endl;
	std::cin.get();
}


Referencia:
Youtube:
-https://www.youtube.com/watch?v=6vEf4n6NQtY
-https://www.youtube.com/watch?v=LM6EDIKS5Pk

+++Interger->object->string+++
cout << "Enter an integer value" << endl;
int input;
cin >> input;

stringstream sso;
sso << input; //se convierte en objeto el int
string strinput;
sso >> strinput; //se extrae el strin del objeto y se asigna a la variable

cout << "the infer number" << input << endl;
cout << "the string form of the number " << strinput << endl;

+++string->object->int+++
string number = "44";
stringstream sso;
sso << number; //se asigna el string como objeto a la variable
int input;
sso >> input; //se extrae la parte int del objeto y se asigna a la variable
cout << input << endl;
*/