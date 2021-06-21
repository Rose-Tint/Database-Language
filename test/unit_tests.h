#pragma once
#include <iostream>
#include <string>
#include "../typedefs.h"
#include "../Cell.h"
#include "../Column.h"
#include "../Table.h"


void unit_tests();
template<class T> bool check(std::string msg, const T&, const T&);
template<class> bool unit_test() {}
template<> bool unit_test<Cell>();
template<> bool unit_test<Column>();
template<> bool unit_test<Table>();
