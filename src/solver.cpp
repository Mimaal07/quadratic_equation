#include "solver.h"
#include "interpreters.h"
#include <cmath>

bool QuadraticSolver::isZero(long double x) {
    return std::abs(x) < EPS;
}

SolutionResult QuadraticSolver::solveNumbers(long double a, long double b, long double c) {
    SolutionResult result;
    
    // Случай: a = 0 (линейное уравнение)
    if (isZero(a)) {
        if (isZero(b)) {
            if (isZero(c)) {
                result.type = SolutionType::INF;
            } else {
                result.type = SolutionType::NO_SOLUTION;
            }
            result.rootsCount = 0;
            return result;
        } else {
            result.type = SolutionType::OK;
            result.rootsCount = 1;
            result.roots.push_back(-c / b);
            return result;
        }
    }
    
    // Квадратное уравнение
    long double discriminant = b * b - 4 * a * c;
    
    if (discriminant < -EPS) {
        result.type = SolutionType::NO_SOLUTION;
        result.rootsCount = 0;
    } else if (std::abs(discriminant) < EPS) {
        result.type = SolutionType::OK;
        result.rootsCount = 1;
        result.roots.push_back(-b / (2 * a));
    } else {
        long double sqrtD = std::sqrt(discriminant);
        result.type = SolutionType::OK;
        result.rootsCount = 2;
        result.roots.push_back((-b - sqrtD) / (2 * a));
        result.roots.push_back((-b + sqrtD) / (2 * a));
        if (result.roots[0] > result.roots[1]) {
            std::swap(result.roots[0], result.roots[1]);
        }
    }
    
    return result;
}

SolutionResult QuadraticSolver::solve(const std::string& a_str,
                                      const std::string& b_str,
                                      const std::string& c_str) {
    auto a = NumberInterpreter::parse(a_str);
    auto b = NumberInterpreter::parse(b_str);
    auto c = NumberInterpreter::parse(c_str);
    
    if (!a.has_value() || !b.has_value() || !c.has_value()) {
        SolutionResult result;
        result.type = SolutionType::WRONG;
        result.rootsCount = 0;
        return result;
    }
    
    return solveNumbers(a.value(), b.value(), c.value());
}