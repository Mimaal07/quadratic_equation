#include <gtest/gtest.h>
#include "../src/solver.h"
#include "../src/interpreters.h"
#include <iostream>

// ========== ТЕСТЫ ПАРСЕРА (ПАТТЕРН ИНТЕРПРЕТАТОР) ==========

TEST(ParserTest, ValidNumbers) {
    EXPECT_TRUE(NumberInterpreter::validate("123"));
    EXPECT_TRUE(NumberInterpreter::validate("-123"));
    EXPECT_TRUE(NumberInterpreter::validate("0.5"));
    EXPECT_TRUE(NumberInterpreter::validate("-0.5"));
    EXPECT_TRUE(NumberInterpreter::validate("123.456"));
    EXPECT_TRUE(NumberInterpreter::validate("1e3"));
    EXPECT_TRUE(NumberInterpreter::validate("-1.5e-3"));
    EXPECT_TRUE(NumberInterpreter::validate("2E+5"));
}

TEST(ParserTest, InvalidNumbers) {
    EXPECT_FALSE(NumberInterpreter::validate(""));
    EXPECT_FALSE(NumberInterpreter::validate("abc"));
    EXPECT_FALSE(NumberInterpreter::validate("12a34"));
    EXPECT_FALSE(NumberInterpreter::validate("12.34.56"));
    EXPECT_FALSE(NumberInterpreter::validate("--123"));
    EXPECT_FALSE(NumberInterpreter::validate(".123"));
    EXPECT_FALSE(NumberInterpreter::validate("123."));
    EXPECT_FALSE(NumberInterpreter::validate("e5"));
    EXPECT_FALSE(NumberInterpreter::validate("1e"));
    EXPECT_FALSE(NumberInterpreter::validate("1e+"));
}

// ========== ТЕСТЫ РЕШЕНИЯ УРАВНЕНИЯ ==========

TEST(SolverTest, QuadraticTwoRoots) {
    auto res = QuadraticSolver::solveNumbers(1, -5, 6);
    EXPECT_EQ(res.type, SolutionType::OK);
    EXPECT_EQ(res.rootsCount, 2);
    EXPECT_NEAR(res.roots[0], 2.0, 1e-10);
    EXPECT_NEAR(res.roots[1], 3.0, 1e-10);
}

TEST(SolverTest, QuadraticOneRoot) {
    auto res = QuadraticSolver::solveNumbers(1, -4, 4);
    EXPECT_EQ(res.type, SolutionType::OK);
    EXPECT_EQ(res.rootsCount, 1);
    EXPECT_NEAR(res.roots[0], 2.0, 1e-10);
}

TEST(SolverTest, QuadraticNoRoots) {
    auto res = QuadraticSolver::solveNumbers(1, 0, 1);
    EXPECT_EQ(res.type, SolutionType::NO_SOLUTION);
    EXPECT_EQ(res.rootsCount, 0);
}

TEST(SolverTest, LinearOneRoot) {
    auto res = QuadraticSolver::solveNumbers(0, 2, -4);
    EXPECT_EQ(res.type, SolutionType::OK);
    EXPECT_EQ(res.rootsCount, 1);
    EXPECT_NEAR(res.roots[0], 2.0, 1e-10);
}

TEST(SolverTest, LinearNoRoots) {
    auto res = QuadraticSolver::solveNumbers(0, 0, 5);
    EXPECT_EQ(res.type, SolutionType::NO_SOLUTION);
    EXPECT_EQ(res.rootsCount, 0);
}

TEST(SolverTest, InfiniteSolutions) {
    auto res = QuadraticSolver::solveNumbers(0, 0, 0);
    EXPECT_EQ(res.type, SolutionType::INF);
    EXPECT_EQ(res.rootsCount, 0);
}

TEST(SolverTest, WithZeroAAndNonZeroB) {
    auto res = QuadraticSolver::solveNumbers(0, 3, 6);
    EXPECT_EQ(res.type, SolutionType::OK);
    EXPECT_EQ(res.rootsCount, 1);
    EXPECT_NEAR(res.roots[0], -2.0, 1e-10);
}

// ========== ИНТЕГРАЦИОННЫЕ ТЕСТЫ ==========

TEST(IntegrationTest, ValidInput) {
    QuadraticSolver solver;
    auto res = solver.solve("1", "-5", "6");
    EXPECT_EQ(res.type, SolutionType::OK);
    EXPECT_EQ(res.rootsCount, 2);
}

TEST(IntegrationTest, InvalidInput) {
    QuadraticSolver solver;
    auto res = solver.solve("abc", "1", "1");
    EXPECT_EQ(res.type, SolutionType::WRONG);
}

TEST(IntegrationTest, ExponentialNotation) {
    QuadraticSolver solver;
    auto res = solver.solve("1e3", "0", "-4e3");
    // 1000x^2 - 4000 = 0 → x^2 = 4 → x = ±2
    EXPECT_EQ(res.type, SolutionType::OK);
    EXPECT_EQ(res.rootsCount, 2);
    EXPECT_NEAR(res.roots[0], -2.0, 1e-10);
    EXPECT_NEAR(res.roots[1], 2.0, 1e-10);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    
    // Пауза перед закрытием окна
    std::cout << std::endl << "Press Enter to exit...";
    std::cin.get();
    
    return result;
}