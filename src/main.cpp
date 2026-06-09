#include "solver.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

int main() {
    std::string line;
    QuadraticSolver solver;
    
    std::cout << "=== QUADRATIC EQUATION SOLVER ===" << std::endl;
    std::cout << "Enter coefficients a, b, c (empty line to exit):" << std::endl;
    
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);
        
        // Выход по пустой строке
        if (line.empty()) {
            std::cout << "Goodbye!" << std::endl;
            break;
        }
        
        std::stringstream ss(line);
        std::string a_str, b_str, c_str;
        ss >> a_str >> b_str >> c_str;
        
        if (a_str.empty()) {
            std::cout << "WRONG" << std::endl;
            continue;
        }
        
        SolutionResult result = solver.solve(a_str, b_str, c_str);
        
        switch (result.type) {
            case SolutionType::WRONG:
                std::cout << "WRONG" << std::endl;
                break;
            case SolutionType::INF:
                std::cout << "INF" << std::endl;
                break;
            case SolutionType::NO_SOLUTION:
                std::cout << "NO SOLUTION" << std::endl;
                break;
            case SolutionType::OK:
                std::cout << "OK" << std::endl;
                std::cout << result.rootsCount << std::endl;
                std::cout << std::fixed << std::setprecision(10);
                for (long double root : result.roots) {
                    if (std::abs(root) < 1e-12) root = 0.0;
                    std::cout << root << std::endl;
                }
                break;
        }
        
        std::cout << std::endl;
    }
    
    return 0;
}