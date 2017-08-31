#include "Employee.h"

Employee::Employee(int id, std::string firstName, std::string lastName, int salary){
	_id = id;
	_firstName = firstName;
	_lastName = lastName;
	_salary = salary;
}

int Employee::getId()
{
	return _id;
}

std::string Employee::getFirstName()
{
	return _firstName;
}

std::string Employee::getLastNAme()
{
	return _lastName;
}

std::string Employee::getName()
{
	return _firstName+ " " + _lastName;
}

int Employee::getSalary()
{
	return _salary;
}

void Employee::setSalary(int salary){
	_salary = salary;
}

int Employee::getAnnualSalary(){
	return _salary*12;
}

int Employee::raiseSalary(int percent){
	return _salary+(_salary*(percent/100));
}

std::string Employee::Print()
{
	return "Em";
}
