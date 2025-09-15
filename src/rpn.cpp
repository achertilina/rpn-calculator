#include "../include/rpn.h"
#include <sstream>
#include <stack>
#include <stdexcept>
#include <cmath>
#include <cctype>

// Вспомогательная функция для вычисления факториала
long long factorial(int n) {
    if (n < 0) throw std::invalid_argument("Factorial of negative number");
    if (n > 20) throw std::invalid_argument("Factorial too large");
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

double evaluate_rpn(const std::string& expression) {
    std::stack<double> stack;
    std::istringstream iss(expression);
    std::string token;
    
    while (iss >> token) {
        try {
            size_t pos;
            double number = std::stod(token, &pos);
            
            if (pos == token.length()) {
                stack.push(number);
                continue;
            }
        } catch (const std::exception&) {
            // Не число, обрабатываем как оператор или функцию
        }
        
        // Бинарные операторы
        if (token == "+") {
            if (stack.size() < 2) throw std::invalid_argument("Not enough operands for '+'");
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            stack.push(a + b);
        }
        else if (token == "-") {
            if (stack.size() < 2) throw std::invalid_argument("Not enough operands for '-'");
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            stack.push(a - b);
        }
        else if (token == "*") {
            if (stack.size() < 2) throw std::invalid_argument("Not enough operands for '*'");
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            stack.push(a * b);
        }
        else if (token == "/") {
            if (stack.size() < 2) throw std::invalid_argument("Not enough operands for '/'");
            double b = stack.top(); stack.pop();
            if (b == 0.0) throw std::invalid_argument("Division by zero");
            double a = stack.top(); stack.pop();
            stack.push(a / b);
        }
        else if (token == "^") {
            if (stack.size() < 2) throw std::invalid_argument("Not enough operands for '^'");
            double exponent = stack.top(); stack.pop();
            double base = stack.top(); stack.pop();
            stack.push(std::pow(base, exponent));
        }
        else if (token == "%") {
            if (stack.size() < 2) throw std::invalid_argument("Not enough operands for '%'");
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            if (b == 0) throw std::invalid_argument("Modulo by zero");
            stack.push(std::fmod(a, b));
        }
        // Унарные операторы
        else if (token == "~") {
            if (stack.size() < 1) throw std::invalid_argument("Not enough operands for '~'");
            double a = stack.top(); stack.pop();
            stack.push(-a);
        }
        else if (token == "++") {
            if (stack.size() < 1) throw std::invalid_argument("Not enough operands for '++'");
            double a = stack.top(); stack.pop();
            stack.push(a + 1);
        }
        else if (token == "--") {
            if (stack.size() < 1) throw std::invalid_argument("Not enough operands for '--'");
            double a = stack.top(); stack.pop();
            stack.push(a - 1);
        }
        else if (token == "!") {
            if (stack.size() < 1) throw std::invalid_argument("Not enough operands for '!'");
            double a = stack.top(); stack.pop();
            if (a < 0 || a != std::floor(a)) {
                throw std::invalid_argument("Factorial requires non-negative integer");
            }
            stack.push(static_cast<double>(factorial(static_cast<int>(a))));
        }
        // Математические функции
        else if (token == "sqrt") {
            if (stack.size() < 1) throw std::invalid_argument("Not enough operands for 'sqrt'");
            double a = stack.top(); stack.pop();
            if (a < 0) throw std::invalid_argument("Square root of negative number");
            stack.push(std::sqrt(a));
        }
        else if (token == "abs") {
            if (stack.size() < 1) throw std::invalid_argument("Not enough operands for 'abs'");
            double a = stack.top(); stack.pop();
            stack.push(std::abs(a));
        }
        else if (token == "sin") {
            if (stack.size() < 1) throw std::invalid_argument("Not enough operands for 'sin'");
            double a = stack.top(); stack.pop();
            stack.push(std::sin(a));
        }
        else if (token == "cos") {
            if (stack.size() < 1) throw std::invalid_argument("Not enough operands for 'cos'");
            double a = stack.top(); stack.pop();
            stack.push(std::cos(a));
        }
        else if (token == "tan") {
            if (stack.size() < 1) throw std::invalid_argument("Not enough operands for 'tan'");
            double a = stack.top(); stack.pop();
            stack.push(std::tan(a));
        }
        else if (token == "asin") {
            if (stack.size() < 1) throw std::invalid_argument("Not enough operands for 'asin'");
            double a = stack.top(); stack.pop();
            if (a < -1.0 || a > 1.0) throw std::invalid_argument("asin argument out of range [-1, 1]");
            stack.push(std::asin(a));
        }
        else if (token == "acos") {
            if (stack.size() < 1) throw std::invalid_argument("Not enough operands for 'acos'");
            double a = stack.top(); stack.pop();
            if (a < -1.0 || a > 1.0) throw std::invalid_argument("acos argument out of range [-1, 1]");
            stack.push(std::acos(a));
        }
        else if (token == "atan") {
            if (stack.size() < 1) throw std::invalid_argument("Not enough operands for 'atan'");
            double a = stack.top(); stack.pop();
            stack.push(std::atan(a));
        }
        else if (token == "ln") {
            if (stack.size() < 1) throw std::invalid_argument("Not enough operands for 'ln'");
            double a = stack.top(); stack.pop();
            if (a <= 0) throw std::invalid_argument("Logarithm of non-positive number");
            stack.push(std::log(a));
        }
        else if (token == "log") {
            if (stack.size() < 1) throw std::invalid_argument("Not enough operands for 'log'");
            double a = stack.top(); stack.pop();
            if (a <= 0) throw std::invalid_argument("Logarithm of non-positive number");
            stack.push(std::log10(a));
        }
        else {
            throw std::invalid_argument("Invalid token: '" + token + "'");
        }
    }
    
    if (stack.empty()) throw std::invalid_argument("Empty expression");
    if (stack.size() > 1) throw std::invalid_argument("Too many operands");
    
    return stack.top();
}