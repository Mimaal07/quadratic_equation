#ifndef SOLVER_H
#define SOLVER_H

#include <string>
#include <vector>

enum class SolutionType {
    OK,
    INF,
    WRONG,
    NO_SOLUTION
};

struct SolutionResult {
    SolutionType type;
    std::vector<long double> roots;
    int rootsCount;
};

class QuadraticSolver {
public:
    SolutionResult solve(const std::string& a_str,
                         const std::string& b_str,
                         const std::string& c_str);
    
    static SolutionResult solveNumbers(long double a, long double b, long double c);
    
private:
    static constexpr long double EPS = 1e-12;
    static bool isZero(long double x);
};

#endif