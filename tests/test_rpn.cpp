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
    EXPECT_THROW(evaluate_rpn("2 abc +"), std::invalid_argument);
    EXPECT_THROW(evaluate_rpn("x y z"), std::invalid_argument);
    EXPECT_THROW(evaluate_rpn("5 !"), std::invalid_argument);
    EXPECT_THROW(evaluate_rpn("hello"), std::invalid_argument);
    EXPECT_THROW(evaluate_rpn("2 3 &"), std::invalid_argument);
    EXPECT_THROW(evaluate_rpn("5 2 $"), std::invalid_argument);
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
    // (3.5 * 2.5 + 1.5) / 2 = (8.75 + 1.5) / 2 = 10.25 / 2 = 5.125
    EXPECT_NEAR(evaluate_rpn("3.5 2.5 * 1.5 + 2 /"), 5.125, 1e-9);
    
    // Для получения 4.75: (3.5 * (2.5 + 1.5)) / 2 = (3.5 * 4.0) / 2 = 14.0 / 2 = 7.0
    // Или другое выражение: 3.5 2.5 1.5 + * 2 /
    
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

// Main function for running tests
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}