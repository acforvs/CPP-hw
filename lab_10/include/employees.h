#ifndef LAB11_EMPLOYEES_H_INCLUDED
#define LAB11_EMPLOYEES_H_INCLUDED

#include <cassert>
#include <fstream>
#include <stdint.h>
#include <string>
#include <vector>

using namespace std;

class Employee {
public:
  Employee(string name, int32_t base_salary);
  virtual ~Employee();

  virtual int salary() const = 0;

  virtual void print(ostream &out) const = 0;
  virtual void print_binary(ofstream &bout) const = 0;

  virtual void read(istream &in) = 0;
  virtual void read_binary(ifstream &bin) = 0;

private:
  friend ostream &operator<<(std::ostream &out, const Employee &emp);
  friend istream &operator>>(std::istream &in, Employee &emp);

  friend ofstream &operator<<(std::ofstream &bout, const Employee &emp);
  friend ifstream &operator>>(std::ifstream &bin, Employee &emp);

protected:
  string _name;
  int32_t _base_salary;
};

class Developer : public Employee {
public:
  Developer(string name, int32_t base_salary, bool has_bonus);
  ~Developer();
  int salary() const override;

  void print(ostream &out) const override;
  void print_binary(ofstream &bout) const override;

  void read(istream &in) override;
  void read_binary(ifstream &bin) override;

private:
  bool _has_bonus;
};

class SalesManager : public Employee {
public:
  SalesManager(string name, int32_t base_salary, int32_t sold_nm,
               int32_t price);
  ~SalesManager();

  int salary() const override;

  void print(ostream &out) const override;
  void print_binary(ofstream &bout) const override;

  void read(istream &in) override;
  void read_binary(ifstream &bin) override;

private:
  int32_t _sold_nm, _price;
};

class EmployeesArray {
public:
  EmployeesArray();
  ~EmployeesArray();

  void add(Employee *e);
  int total_salary() const;

  static Employee *create_by_type(int32_t type) {
    switch (type) {
    case 1:
      return new Developer("", 0, 0);
    case 2:
      return new SalesManager("", 0, 0, 0);
    }
    assert(false && "incorrect type for the employee");
  }

private:
  friend ostream &operator<<(ostream &out, const EmployeesArray &arr);
  friend ifstream &operator>>(ifstream &bin, EmployeesArray &arr);
  friend ofstream &operator<<(ofstream &bout, const EmployeesArray &arr);
  vector<Employee *> _employees;
};

#endif
