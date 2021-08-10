#include "employees.h"

Employee::Employee(string name, int32_t base_salary) {
  _name = name;
  _base_salary = base_salary;
}

Employee::~Employee() {}

void Employee::print(ostream &out) const {
  out << "Name: " << _name << endl;
  out << "Base Salary: " << _base_salary << endl;
}

void Employee::print_binary(ofstream &bout) const {
  bout.write((char *)&_name[0], _name.length() + 1);
  bout.write((char *)&_base_salary, sizeof(int32_t));
}

void Employee::read_binary(ifstream &bin) {
  getline(bin, _name, '\0');
  bin.read((char *)&_base_salary, sizeof(int32_t));
}

void Employee::read(istream &in) { in >> _name >> _base_salary; }

ostream &operator<<(ostream &out, const Employee &emp) {
  emp.print(out);
  return out;
}

ofstream &operator<<(ofstream &bout, const Employee &emp) {
  emp.print_binary(bout);
  return bout;
}

istream &operator>>(istream &in, Employee &emp) {
  emp.read(in);
  return in;
}

ifstream &operator>>(ifstream &bin, Employee &emp) {
  emp.read_binary(bin);
  return bin;
}
