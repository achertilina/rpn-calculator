#include <gtest/gtest.h>
#include "rpn.h"
#include <stdexcept>

TEST(RPNTest, BasicAddition) {
    EXPECT_DOUBLE_EQ(evaluate_rpn("2 3 +"), 5.0);
}

TEST(RPNTest, Subtraction) {
    EXPECT_DOUBLE_EQ(evaluate_rpn("10 3 -"), 7.0);
}

TEST(RPNTest, Multiplication) {
    EXPECT_DOUBLE_EQ(evaluate_rpn("4 5 *"), 20.0);
}

TEST(RPNTest, Division) {
    EXPECT_DOUBLE_EQ(evaluate_rpn("20 4 /"), 5.0);
}

TEST(RPNTest, DivisionByZero) {
    EXPECT_THROW(evaluate_rpn("1 0 /"), std::invalid_argument);
}

TEST(RPNTest, InvalidExpression) {
    EXPECT_THROW(evaluate_rpn("2 +"), std::invalid_argument);
}

TEST(RPNTest, ComplexExpression) {
    EXPECT_NEAR(evaluate_rpn("15 7 1 1 + - / 3 * 2 1 1 + + -"), 5.0, 1e-9);
}

TEST(RPNTest, MultipleOperations) {
    EXPECT_DOUBLE_EQ(evaluate_rpn("3 4 5 * +"), 23.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("5 1 2 + 4 * + 3 -"), 14.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("2 3 4 * + 5 -"), 9.0);
}

TEST(RPNTest, EmptyExpression) {
    EXPECT_THROW(evaluate_rpn(""), std::invalid_argument);
}

TEST(RPNTest, TooManyOperands) {
    EXPECT_THROW(evaluate_rpn("2 3 4 +"), std::invalid_argument);
    EXPECT_THROW(evaluate_rpn("1 2 3 4 +"), std::invalid_argument);
}

TEST(RPNTest, InvalidToken) {
    // ИСПРАВЛЕНО: убрали "5 !" так как ! теперь валидный оператор
    EXPECT_THROW(evaluate_rpn("2 abc +"), std::invalid_argument);
    EXPECT_THROW(evaluate_rpn("x y z"), std::invalid_argument);
    EXPECT_THROW(evaluate_rpn("hello"), std::invalid_argument);
    EXPECT_THROW(evaluate_rpn("2 3 &"), std::invalid_argument);
    EXPECT_THROW(evaluate_rpn("5 2 $"), std::invalid_argument);
    EXPECT_THROW(evaluate_rpn("5 #"), std::invalid_argument); // Добавили новый невалидный оператор
}

TEST(RPNTest, DecimalNumbers) {
    EXPECT_DOUBLE_EQ(evaluate_rpn("2.5 3.5 +"), 6.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("10.0 2.5 /"), 4.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("3.14 2 *"), 6.28);
}

TEST(RPNTest, NegativeNumbers) {
    EXPECT_DOUBLE_EQ(evaluate_rpn("-5 3 +"), -2.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("10 -3 -"), 13.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("-4 -2 *"), 8.0);
}

TEST(RPNTest, SingleNumber) {
    EXPECT_DOUBLE_EQ(evaluate_rpn("42"), 42.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("3.14"), 3.14);
    EXPECT_DOUBLE_EQ(evaluate_rpn("-10"), -10.0);
}

TEST(RPNTest, ComplexExpressionsWithDecimals) {
    // ИСПРАВЛЕНО: правильное ожидаемое значение
    EXPECT_NEAR(evaluate_rpn("3.5 2.5 * 1.5 + 2 /"), 5.125, 1e-9);
    EXPECT_NEAR(evaluate_rpn("10.0 3.0 / 2.0 *"), 6.666666666666667, 1e-9);
}

TEST(RPNTest, MultipleSpaces) {
    EXPECT_DOUBLE_EQ(evaluate_rpn("  2   3   +  "), 5.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("10    2   /"), 5.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("   4   5   *   "), 20.0);
}

TEST(RPNTest, NotEnoughOperandsForMultipleOperators) {
    EXPECT_THROW(evaluate_rpn("+"), std::invalid_argument);
    EXPECT_THROW(evaluate_rpn("2 + +"), std::invalid_argument);
    EXPECT_THROW(evaluate_rpn("3 4 * +"), std::invalid_argument);
}

TEST(RPNTest, MixedOperations) {
    EXPECT_DOUBLE_EQ(evaluate_rpn("3 4 + 5 * 6 -"), 29.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("20 4 / 3 * 2 +"), 17.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("8 2 / 2 * 4 +"), 12.0);
}

// Новые операции
TEST(RPNTest, PowerOperation) {
    EXPECT_DOUBLE_EQ(evaluate_rpn("2 3 ^"), 8.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("4 2 ^"), 16.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("5 0 ^"), 1.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("9 0.5 ^"), 3.0);
    EXPECT_NEAR(evaluate_rpn("2 0.5 ^"), 1.414213562, 1e-9);
}

TEST(RPNTest, ModuloOperation) {
    EXPECT_DOUBLE_EQ(evaluate_rpn("7 3 %"), 1.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("10 5 %"), 0.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("15 4 %"), 3.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("12.5 3.2 %"), 12.5 - 3 * 3.2); // fmod(12.5, 3.2)
    EXPECT_THROW(evaluate_rpn("5 0 %"), std::invalid_argument);
}

TEST(RPNTest, UnaryMinus) {
    EXPECT_DOUBLE_EQ(evaluate_rpn("5 ~"), -5.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("-3 ~"), 3.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("2.5 ~"), -2.5);
    EXPECT_DOUBLE_EQ(evaluate_rpn("0 ~"), 0.0);
}

TEST(RPNTest, IncrementDecrement) {
    EXPECT_DOUBLE_EQ(evaluate_rpn("5 ++"), 6.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("3 --"), 2.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("0 ++"), 1.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("2.5 ++"), 3.5);
    EXPECT_DOUBLE_EQ(evaluate_rpn("-1 ++"), 0.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("-1 --"), -2.0);
}

TEST(RPNTest, Factorial) {
    EXPECT_DOUBLE_EQ(evaluate_rpn("5 !"), 120.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("0 !"), 1.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("1 !"), 1.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("3 !"), 6.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("4 !"), 24.0);
    EXPECT_THROW(evaluate_rpn("-1 !"), std::invalid_argument);
    EXPECT_THROW(evaluate_rpn("2.5 !"), std::invalid_argument);
    EXPECT_THROW(evaluate_rpn("21 !"), std::invalid_argument); // Слишком большое
}

TEST(RPNTest, ComplexOperationsWithNewOperators) {
    EXPECT_DOUBLE_EQ(evaluate_rpn("2 3 ^ 1 +"), 9.0);      // 2^3 + 1 = 8 + 1 = 9
    EXPECT_DOUBLE_EQ(evaluate_rpn("5 2 % 3 *"), 3.0);      // (5%2)*3 = 1*3 = 3
    EXPECT_DOUBLE_EQ(evaluate_rpn("4 ~ ++"), -3.0);        // -4 + 1 = -3
    EXPECT_DOUBLE_EQ(evaluate_rpn("3 ! 2 ^"), 36.0);       // (3!)^2 = 6^2 = 36
    EXPECT_DOUBLE_EQ(evaluate_rpn("5 2 ^ 3 %"), 1.0);      // (5^2)%3 = 25%3 = 1
    EXPECT_DOUBLE_EQ(evaluate_rpn("4 2 / ~"), -2.0);       // -(4/2) = -2
    EXPECT_DOUBLE_EQ(evaluate_rpn("2 3 ^ 4 * 5 ~ +"), 27.0); // 2^3 * 4 + (-5) = 8*4 -5 = 32-5=27
}
// Добавьте эти тесты в существующий файл

TEST(RPNTest, SquareRoot) {
    EXPECT_DOUBLE_EQ(evaluate_rpn("4 sqrt"), 2.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("9 sqrt"), 3.0);
    EXPECT_NEAR(evaluate_rpn("2 sqrt"), 1.414213562, 1e-9);
    EXPECT_THROW(evaluate_rpn("-1 sqrt"), std::invalid_argument);
}

TEST(RPNTest, AbsoluteValue) {
    EXPECT_DOUBLE_EQ(evaluate_rpn("5 abs"), 5.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("-3 abs"), 3.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("0 abs"), 0.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("-2.5 abs"), 2.5);
}

TEST(RPNTest, TrigonometricFunctions) {
    EXPECT_NEAR(evaluate_rpn("0 sin"), 0.0, 1e-9);
    EXPECT_NEAR(evaluate_rpn("0 cos"), 1.0, 1e-9);
    EXPECT_NEAR(evaluate_rpn("0 tan"), 0.0, 1e-9);
    
    EXPECT_NEAR(evaluate_rpn("1.047197551 sin"), 0.86602540378, 1e-9); // sin(60°)
    EXPECT_NEAR(evaluate_rpn("1.047197551 cos"), 0.5, 1e-9); // cos(60°)
}

TEST(RPNTest, InverseTrigonometricFunctions) {
    EXPECT_NEAR(evaluate_rpn("0 asin"), 0.0, 1e-9);
    EXPECT_NEAR(evaluate_rpn("1 asin"), 1.57079632679, 1e-9); // π/2
    EXPECT_NEAR(evaluate_rpn("0 acos"), 1.57079632679, 1e-9); // π/2
    EXPECT_NEAR(evaluate_rpn("1 acos"), 0.0, 1e-9);
    EXPECT_NEAR(evaluate_rpn("0 atan"), 0.0, 1e-9);
    EXPECT_NEAR(evaluate_rpn("1 atan"), 0.78539816339, 1e-9); // π/4
    
    EXPECT_THROW(evaluate_rpn("1.1 asin"), std::invalid_argument);
    EXPECT_THROW(evaluate_rpn("-1.1 acos"), std::invalid_argument);
}

TEST(RPNTest, Logarithms) {
    EXPECT_NEAR(evaluate_rpn("1 ln"), 0.0, 1e-9);
    EXPECT_NEAR(evaluate_rpn("2.718281828 ln"), 1.0, 1e-9); // ln(e)
    EXPECT_NEAR(evaluate_rpn("1 log"), 0.0, 1e-9);
    EXPECT_NEAR(evaluate_rpn("10 log"), 1.0, 1e-9);
    EXPECT_NEAR(evaluate_rpn("100 log"), 2.0, 1e-9);
    
    EXPECT_THROW(evaluate_rpn("0 ln"), std::invalid_argument);
    EXPECT_THROW(evaluate_rpn("-1 log"), std::invalid_argument);
}

TEST(RPNTest, ComplexMathExpressions) {
    EXPECT_NEAR(evaluate_rpn("4 sqrt 2 ^"), 4.0, 1e-9); // (√4)^2 = 4
    EXPECT_NEAR(evaluate_rpn("2 3 ^ sqrt"), 2.8284271247, 1e-9); // √(2^3) = √8
    EXPECT_NEAR(evaluate_rpn("45 ~ abs"), 45.0, 1e-9); // abs(-45)
    EXPECT_NEAR(evaluate_rpn("0.5 asin 2 *"), 1.047197551, 1e-9); // 2 * asin(0.5) = 60°
    EXPECT_NEAR(evaluate_rpn("100 log 2 ^"), 4.0, 1e-9); // (log10(100))^2 = 2^2 = 4
    
    // Убрали проблемный тест с неверным ожиданием
    // 4 * atan(0.25) ≠ π, это математическая ошибка
}
// Main function for running tests
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}