
#ifndef SIMPLEX_METHOD_SIMPLEX_METHOD_HPP
#define SIMPLEX_METHOD_SIMPLEX_METHOD_HPP

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

class Simplix_table {
    std::vector<size_t> _basic_variables;
    std::vector<size_t> _free_variables;
    std::vector<std::vector<double>> _table;

public:
    Simplix_table(std::vector<std::vector<double>> const &A, std::vector<double> const &b,
                  std::vector<double> const &c);

    std::vector<size_t> basic_variables();

    std::vector<size_t> free_variables();

    std::vector<std::vector<double>> table();

    void transformation(size_t string, size_t colunm);

    void print_table(Simplix_table table);
};

size_t permissive_string(Simplix_table table, size_t permissive_column);

std::vector<double> simplix_method(std::vector<std::vector<double>> const &A, std::vector<double> const &b,
                                   std::vector<double> const &c);

#endif//SIMPLEX_METHOD_SIMPLEX_METHOD_HPP
