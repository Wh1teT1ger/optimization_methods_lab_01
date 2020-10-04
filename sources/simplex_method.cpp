
#include <simplex_method.hpp>

Simplix_table::Simplix_table(std::vector<std::vector<double>> const &A, std::vector<double> const &b,
                             std::vector<double> const &c) {
    for (size_t i = 1; i <= c.size(); i++) {
        _free_variables.push_back(i);
        _basic_variables.push_back(i + c.size());
    }
    std::vector<std::vector<double>> table(c.size() + 1, std::vector<double>(c.size() + 1));
    for (size_t i = 0; i < b.size(); i++) { table[i][0] = b[i]; }
    table[c.size()][0] = 0;
    for (size_t i = 0; i < c.size(); i++) {
        for (size_t j = 0; j < c.size(); j++) { table[i][j + 1] = A[i][j]; }
    }
    for (size_t i = 0; i < b.size(); i++) { table[b.size()][i + 1] = -c[i]; }
    _table = table;
}

std::vector<size_t> Simplix_table::basic_variables() { return _basic_variables; }

std::vector<size_t> Simplix_table::free_variables() { return _free_variables; }

std::vector<std::vector<double>> Simplix_table::table() { return _table; }

void Simplix_table::transformation(size_t string, size_t colunm) {
    size_t variable = _basic_variables[string];
    _basic_variables[string] = _free_variables[colunm - 1];
    _free_variables[colunm - 1] = variable;
    for (size_t i = 0; i < _table.size(); i++) {
        for (size_t j = 0; j < _table.size(); j++) {
            if (i != string && j != colunm) {
                _table[i][j] = _table[i][j] - _table[i][colunm] * _table[string][j] / _table[string][colunm];
            }
        }
    }
    for (size_t i = 0; i < _table.size(); i++) {
        if (i != string) { _table[i][colunm] = -_table[i][colunm] / _table[string][colunm]; }
    }
    for (size_t i = 0; i < _table.size(); i++) {
        if (i != colunm) { _table[string][i] = _table[string][i] / _table[string][colunm]; }
    }
    _table[string][colunm] = 1 / _table[string][colunm];
}

size_t permissive_string(Simplix_table table, size_t permissive_column) {
    size_t permissive_string;
    double min;
    bool check = true;
    double simplex_relation;
    for (size_t i = 0; i < table.table().size() - 1; i++) {
        if (table.table()[i][permissive_column] != 0) {
            simplex_relation = table.table()[i][0] / table.table()[i][permissive_column];
            if (simplex_relation >= 0 && (simplex_relation < min || check == true)) {
                min = simplex_relation;
                check = false;
                permissive_string = i;
            }
        }
    }
    return permissive_string;
}

void print_table(Simplix_table table) {
    std::cout << std::setw(5) << "     " << std::setw(8) << 'x' << 0;
    for (size_t i = 0; i < table.free_variables().size(); i++) {
        std::cout << std::setw(7) << 'x' << table.free_variables()[i];
    }
    std::cout << std::endl;
    for (size_t i = 0; i < table.table().size(); i++) {
        if (i != table.table().size() - 1) std::cout << std::setw(5) << 'x' << table.basic_variables()[i];
        else
            std::cout << "     F";
        for (size_t j = 0; j < table.table().size(); j++) { std::cout << std::setw(8) << table.table()[i][j]; }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::vector<double> simplix_method(std::vector<std::vector<double>> const &A, std::vector<double> const &b,
                                   std::vector<double> const &c) {
    Simplix_table simplixTable(A, b, c);
    double min = 0;
    print_table(simplixTable);
    do {
        min = 0;
        size_t permissive_column = 0;
        for (size_t i = 1; i <= c.size(); i++) {
            if (simplixTable.table()[b.size()][i] < 0 && simplixTable.table()[b.size()][i] < min) {
                min = simplixTable.table()[b.size()][i];
                permissive_column = i;
            }
        }
        if (min == 0) break;
        size_t perm_string = permissive_string(simplixTable, permissive_column);
        std::cout << "permissive column: " << permissive_column + 1 << std::endl;
        std::cout << "permissive string: " << perm_string + 1 << std::endl;
        simplixTable.transformation(perm_string, permissive_column);
        print_table(simplixTable);
    } while (min < 0);
    std::vector<double> answer(b.size() * 2 + 1);
    answer[0] = simplixTable.table()[simplixTable.table().size() - 1][0];
    for (size_t i = 0; i < b.size(); i++) { answer[simplixTable.basic_variables()[i]] = simplixTable.table()[i][0]; }
    for (size_t i = 0; i < b.size(); i++) { answer[simplixTable.free_variables()[i]] = 0; }
    return answer;
}
