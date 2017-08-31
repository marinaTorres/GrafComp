/*********************************************************
Materia: Gráficas Computacionales
Fecha: 14 de agosto del 2017
Autor: A01375051 Marina Fernanda Torres Gómez
*********************************************************/

#include <iostream>
#include "Circle.h"
#include "Rectangle.h"
#include "Employee.h"
using namespace std;


int PerimetroRectangulo(int base, int altura) {
	int perimetro = 2 * base + 2 * altura;
	return perimetro;
}

float AreaTriangulo(float base, float altura) {
	float area;
	area = (base*altura) / 2;
	return area;
}

int Mayor(int numero1, int numero2, int numero3) {
	int mayor;
	mayor = (numero1 > numero2) ? numero1 : numero2;
	mayor = (mayor > numero3) ? mayor : numero3;

	return mayor;
}

int Menor(int numero1, int numero2, int numero3) {
	int menor;
	menor = (numero1 > numero2) ? numero2 : numero1;
	menor = (menor > numero3) ? numero3 : menor;

	return menor;
}

void FilaEstrellas(int n) {
	for (int i = 0; i < n; i++) {
		cout << "*";
	}
	cout << endl;
}

void MatrizEstrellas(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << "*";
		}
		cout << endl;
	}
}

void PiramideEstrellas(int n) {
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= i; j++) {
			cout << "*";
		}
		cout << endl;
	}
}

void FlechaEstrellas(int n) {
	int k = 1;
	for (int i = 0; i < n + (n - 1); i++) {
		if (i <= (n - 1)) {
			for (int j = 0; j <= i; j++) {
				cout << "*";
			}
		}
		else {
			for (int j = 0; j < (i - k); j++) {
				cout << "*";
			}
			k += 2;
		}
		cout << endl;
	}

}

void Fibonacci(int n) {
	int i = 0;
	int a = 1, b = 1, c;
	cout << a << " " << b << " ";
	while (i < n - 2) {
		c = a + b;
		cout << c << " ";
		a = b;
		b = c;
		i++;
	}
	cout << endl;
}

bool EsPrimo(int numero) {
	bool primo;
	int a = 0;
	for (int i = 1; i<(numero + 1); i++) {
		if (numero%i == 0) {
			a++;
		}
	}
	if (a != 2) {
		primo = false;
	}
	else {
		primo = true;
	}
	return primo;
}

int main3() {


	cout << "++++Menu++++\n1)Perimetro\n2)Area\n3)Mayor\n4)Menor" << endl;
	cout << "5)Fila Estrellas\n6)Matriz Estrellas\n7)Piramide Estrellas\n8)Flecha Estrelas\n9)Fibonacci\n10)Es primo?" << endl;
	cout << "Presione 0 para terminar" << endl;

	int opc;
	cout << "\nOpcion:" << endl;
	cin >> opc;

	while (opc != 0) {
		switch (opc) {
		case 1: {
			int baseP, alturaP;
			cout << "\nBase:" << endl;
			cin >> baseP;
			cout << "Altura:" << endl;
			cin >> alturaP;
			int p = PerimetroRectangulo(baseP, alturaP);
			cout << "Perimetro: " << p << endl;
		}
				break;
		case 2: {
			float baseA, alturaA;
			cout << "\nBase:" << endl;
			cin >> baseA;
			cout << "Altura:" << endl;
			cin >> alturaA;
			float a = AreaTriangulo(baseA, alturaA);
			cout << "Area: " << a << "\n" << endl;
		}
				break;
		case 3: {
			int  num1, num2, num3, mayor;
			cout << "\nNumero 1:" << endl;
			cin >> num1;
			cout << "Numero 2:" << endl;
			cin >> num2;
			cout << "Numero 3:" << endl;
			cin >> num3;

			mayor = Mayor(num1, num2, num3);
			cout << "Mayor: " << mayor << endl;
		}
				break;
		case 4: {
			int  num1, num2, num3, menor;
			cout << "\nNumero 1:" << endl;
			cin >> num1;
			cout << "Numero 2:" << endl;
			cin >> num2;
			cout << "Numero 3:" << endl;
			cin >> num3;

			menor = Menor(num1, num2, num3);
			cout << "Menor: " << menor << endl;
		}
				break;
		case 5: {
			int  n;
			cout << "\nNo. de estrellas:" << endl;
			cin >> n;
			FilaEstrellas(n);
		}
				break;
		case 6: {
			int n;
			cout << "\nNo. de estrellas:" << endl;
			cin >> n;
			MatrizEstrellas(n);
		}
				break;
		case 7: {
			int n;
			cout << "\nNo. de estrellas:" << endl;
			cin >> n;
			PiramideEstrellas(n);
		}
				break;
		case 8: {
			int n;
			cout << "\nNo. de estrellas:" << endl;
			cin >> n;
			FlechaEstrellas(n);
		}
				break;
		case 9: {
			int n;
			cout << "\nNumero de elementos:" << endl;
			cin >> n;
			Fibonacci(n);
		}
				break;
		case 10: {
			int n;
			cout << "\nNumero:" << endl;
			cin >> n;
			bool primo = EsPrimo(n);
			cout << "Es primo: " << primo << endl;
		}
				 break;
		}
		cout << "\nOpcion:" << endl;
		cin >> opc;
	}

	std::cin.get();
	return 0;
}