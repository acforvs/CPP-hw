#include "employees.h"

EmployeesArray::EmployeesArray() {}

EmployeesArray::~EmployeesArray() {
  for (size_t i = 0; i < _employees.size(); i++) {
    delete _employees[i];
  }
}

void EmployeesArray::add(Employee *emp) { _employees.push_back(emp); }

int EmployeesArray::total_salary() const {
  int total = 0;
  for (size_t i = 0; i < _employees.size(); i++) {
    total += _employees[i]->salary();
  }
  return total;
}

ostream &operator<<(ostream &out, const EmployeesArray &arr) {
  for (size_t i = 0; i < arr._employees.size(); i++) {
    out << i + 1 << ". " << *arr._employees[i];
  }
  out << "== Total salary: " << arr.total_salary() << endl << endl;
  return out;
}

ofstream &operator<<(ofstream &bout, const EmployeesArray &arr) {
  size_t sz = arr._employees.size();
  bout.write((char *)&sz, sizeof(int32_t));
  for (size_t i = 0; i < sz; i++) {
    bout << *arr._employees[i];
  }
  return bout;
}

ifstream &operator>>(ifstream &bin, EmployeesArray &arr) {
  int32_t sz;
  bin.read((char *)&sz, sizeof(int32_t));
  while (sz-- && !bin.eof()) {
    int32_t type;
    bin.read((char *)&type, sizeof(int32_t));
    Employee *emp = EmployeesArray::create_by_type(type);
    bin >> *emp;
    arr.add(emp);
  }
  return bin;
}
