#pragma once
#include <string>
class Employee {
public:
	Employee(int id, std::string firstName, std::string lastName, int salary);

	int getId();
	std::string getFirstName();
	std::string getLastNAme();
	std::string getName();
	int getSalary();

	void setSalary(int salary);
	int getAnnualSalary();
	int raiseSalary(int percent);
	std::string Print();
private:
	int _id;
	std::string _firstName;
	std::string _lastName;
	int _salary;

};