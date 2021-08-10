#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "linq.hpp"

#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

using linq::from;

TEST_CASE("until works on the first elem") {
  std::vector<int> xs = {1, 2, 3, 4, 5};
  std::vector<int> res = from(xs.begin(), xs.end())
                             .until([](int x) { return x != -1; })
                             .to_vector();

  CHECK(res.size() == 0);
}

TEST_CASE("until_eq works on the first elem") {
  std::vector<int> xs = {1, 2, 3, 4, 5};
  std::vector<int> res = from(xs.begin(), xs.end()).until_eq(1).to_vector();

  CHECK(res.size() == 0);
}

TEST_CASE("until should accept all elements") {
  std::vector<int> xs = {1, 2, 3};
  std::vector<int> res =
      from(xs.begin(), xs.end()).until([](int x) { return x > 5; }).to_vector();

  CHECK(res.size() == 3);
}

TEST_CASE("until on empty sequence") {
  std::vector<int> xs;
  std::vector<int> res = from(xs.begin(), xs.end()).until_eq(0).to_vector();

  CHECK(res.size() == 0);
}

TEST_CASE("select on empty sequence") {
  std::vector<int> xs;
  std::vector<int> res = from(xs.begin(), xs.end())
                             .select([](int x) { return x == 3; })
                             .to_vector();

  CHECK(res.size() == 0);
}

TEST_CASE("select on empty sequence v2") {
  std::vector<int> xs = {1, 2, 3, 4};
  std::vector<int> res = from(xs.begin(), xs.end())
                             .take(3)
                             .drop(5)
                             .select([](int x) { return x + 3; })
                             .to_vector();

  CHECK(res.size() == 0);
}

TEST_CASE("where on empty sequence") {
  std::vector<int> xs;
  std::vector<int> res = from(xs.begin(), xs.end())
                             .where([](int x) { return x == 100; })
                             .to_vector();

  CHECK(res.size() == 0);
}

TEST_CASE("where string") {
  std::vector<std::string> ss = {"kek", "prikol", "mem", "lol", "ugar"};
  std::vector<std::string> res =
      from(ss.begin(), ss.end())
          .where([](std::string s) { return s.size() == 3; })
          .to_vector();

  CHECK(res.size() == 3);
  std::vector<std::string> exp = {"kek", "mem", "lol"};
  CHECK(exp == res);
}

TEST_CASE("select string") {
  std::vector<std::string> ss = {"kek", "lol", "mem"};
  std::vector<std::string> res =
      from(ss.begin(), ss.end())
          .select([](std::string s) { return s + s; })
          .to_vector();

  std::vector<std::string> exp = {"kekkek", "lollol", "memmem"};
  CHECK(res == exp);
}

TEST_CASE("take & drop") {
  std::vector<std::string> ss = {"kek", "mem", "lol"};
  std::vector<std::string> res =
      from(ss.begin(), ss.end())
          .take(2)
          .drop(1)
          .select([](std::string s) { return "TEST: " + s; })
          .to_vector();

  CHECK(res.size() == 1);
  CHECK(res[0] == "TEST: mem");
}

TEST_CASE("take more than length") {
  std::vector<std::string> ss = {"kek", "mem"};
  std::vector<std::string> res =
      from(ss.begin(), ss.end()).take(10).to_vector();
  CHECK(res.size() == 2);
}

TEST_CASE("drop more than length") {
  std::vector<int> xs = {1, 2, 3, 4};
  std::vector<int> res = from(xs.begin(), xs.end()).drop(100).to_vector();

  CHECK(res.size() == 0);
}

TEST_CASE("type change inside select") {
  std::vector<std::string> ss = {"kek", "ugar", "mem", "loool"};
  std::vector<double> res =
      from(ss.begin(), ss.end())
          .select<int>([](std::string s) { return int(s.length()); })
          .select<double>([](int x) { return x / 2.0; })
          .to_vector();

  std::vector<double> exp = {1.5, 2.0, 1.5, 2.5};
  CHECK(res == exp);
}

TEST_CASE("no changes") {
  std::vector<int> xs = {1, 2, 3, 4, 5};
  std::vector<int> res = from(xs.begin(), xs.end()).to_vector();

  CHECK(res == xs);
}

TEST_CASE("take sequence") {
  std::vector<int> xs = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> res = from(xs.begin(), xs.end())
                             .take(9)
                             .take(8)
                             .take(7)
                             .take(6)
                             .take(5)
                             .take(4)
                             .take(3)
                             .take(2)
                             .take(1)
                             .to_vector();

  CHECK(res.size() == 1);
  CHECK(res[0] == 1);
}

TEST_CASE("drop sequence") {
  std::vector<int> xs = {1, 2, 3, 4};
  std::vector<int> res = from(xs.begin(), xs.end()).drop(1).drop(2).to_vector();

  CHECK(res.size() == 1);
  CHECK(res[0] == 4);
}

TEST_CASE("where until select") {
  std::vector<int> xs = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<double> res = from(xs.begin(), xs.end())
                                .where([](int x) { return x % 2 == 1; })
                                .until([](int x) { return x == 9; })
                                .select<double>([](int x) { return x * 1.0; })
                                .to_vector();

  std::vector<double> exp = {1.0, 3.0, 5.0, 7.0};
  CHECK(exp == res);
}

TEST_CASE("reverse iterator") {
  std::vector<int> xs = {1, 2, 3};
  std::vector<int> res = from(xs.rbegin(), xs.rend()).to_vector();

  std::vector<int> exp = {3, 2, 1};
  CHECK(exp == res);
}

TEST_CASE("from set") {
  std::set<int> s = {1, 2, 3};
  std::vector<int> res = from(s.begin(), s.end()).until_eq(2).to_vector();

  CHECK(res.size() == 1);
  CHECK(res[0] == 1);
}

TEST_CASE("copy_to") {
  std::stringstream out_str;
  std::ostream_iterator<std::string> out(out_str, "\n");

  std::vector<std::string> ss = {"Hello", "it's", "me", "you"};
  from(ss.begin(), ss.end())
      .where([](std::string s) { return s.length() > 2; })
      .select(
          [](std::string s) { return s + ", " + std::to_string(s.length()); })
      .copy_to(out);

  CHECK(out_str.str() == "Hello, 5\nit's, 4\nyou, 3\n");
}

TEST_CASE("filter class") {
  class User {
  private:
    int age_;
    std::string name_;

  public:
    User(int age, std::string name) : age_(age), name_(name){};
    int age() const { return age_; };
  };

  std::vector<User> users;
  users.push_back(User(30, "Ivan"));
  users.push_back(User(31, "Igor"));
  users.push_back(User(44, "Egor"));
  users.push_back(User(20, "Maria"));
  users.push_back(User(36, "Dima"));

  std::vector<int> res =
      from(users.begin(), users.end())
          .where([](User u) { return 30 <= u.age() && u.age() < 40; })
          .select<int>([](User u) { return u.age(); })
          .to_vector();

  CHECK(res.size() == 3);
  std::vector<int> exp = {30, 31, 36};
  CHECK(res == exp);
}
