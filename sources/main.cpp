#include <iostream>
#include <simplex_method.hpp>
#include <vector>

int main() {
    std::vector<std::vector<double>> A = {{2, 1, 1}, {1, 4, 0}, {0, 0.5, 1}};
    std::vector<double> b = {6, 4, 1}, c = {3, 1, 4};
    std::vector<double> answer = simplix_method(A, b, c);
    std::cout << "F=" << answer[0] << std::endl;
    for (size_t i = 1; i < answer.size(); i++) { std::cout << "x" << i << "=" << answer[i] << " "; }
}
