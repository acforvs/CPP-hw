#include "employees.h"

SalesManager::SalesManager(string name, int32_t base_salary, int32_t sold_nm,
                           int32_t price)
    : Employee(name, base_salary) {
  _sold_nm = sold_nm;
  _price = price;
}

SalesManager::~SalesManager() {}

int SalesManager::salary() const {
  return _base_salary + _sold_nm * _price * 0.01;
}

void SalesManager::print(ostream &out) const {
  out << "Sales Manager" << endl;
  Employee::print(out);
  out << "Sold items: " << _sold_nm << endl;
  out << "Item price: " << _price << endl;
}

void SalesManager::print_binary(ofstream &bout) const {
  int32_t type = 2;
  bout.write((char *)&type, sizeof(int32_t));
  Employee::print_binary(bout);
  bout.write((char *)&_sold_nm, sizeof(int32_t));
  bout.write((char *)&_price, sizeof(int32_t));
}

void SalesManager::read(istream &in) {
  Employee::read(in);
  in >> _sold_nm >> _price;
}

void SalesManager::read_binary(ifstream &bin) {
  Employee::read_binary(bin);
  bin.read((char *)&_sold_nm, sizeof(int32_t));
  bin.read((char *)&_price, sizeof(int32_t));
}
