#include "employees.h"

Developer::Developer(string name, int32_t base_salary, bool has_bonus)
    : Employee(name, base_salary) {
  _has_bonus = has_bonus;
}

Developer::~Developer() {}

int Developer::salary() const {
  return _has_bonus ? _base_salary + 1000 : _base_salary;
}

void Developer::print(ostream &out) const {
  out << "Developer" << endl;
  Employee::print(out);
  out << "Base salary: " << _base_salary << endl;
  out << "Has bonus: " << (_has_bonus ? '+' : '-') << endl;
}

void Developer::print_binary(ofstream &bout) const {
  int32_t type = 1;
  bout.write((char *)&type, sizeof(int32_t));
	Employee::print_binary(bout);
	bout.write((char *)&_has_bonus, sizeof(int8_t));
}

void Developer::read(istream &in) {
  Employee::read(in);
  in >> _has_bonus;
}

void Developer::read_binary(ifstream &bin) {
  Employee::read_binary(bin);
  bin.read((char *)&_has_bonus, sizeof(int8_t));
}
