#include <employees.h>
#include <iostream>

int main() {
  string cmd, filename;
  EmployeesArray employees;

  while (cin) {
    cin >> cmd;
    if (cmd == "exit") {
      break;
    } else if (cmd == "load") {
      cin >> filename;
      ifstream in(filename, ios_base::binary);
      in >> employees;
    } else if (cmd == "save") {
      cin >> filename;
      ofstream out(filename, ios_base::binary);
      out << employees;
    } else if (cmd == "list") {
      cout << employees;
    } else if (cmd == "add") {
      int type;
      cin >> type;
      Employee *emp = EmployeesArray::create_by_type(type);
      cin >> *emp;
      employees.add(emp);
    }
  }
}
