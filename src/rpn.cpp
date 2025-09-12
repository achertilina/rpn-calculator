#include "../include/rpn.h"
#include <sstream>
#include <stack>
#include <stdexcept>
#include <cmath>
#include <cctype>

double evaluate_rpn(const std::string& expression) {
    std::stack<double> stack;
    std::istringstream iss(expression);
    std::string token;
    
    while (iss >> token) {
        // Пытаемся преобразовать токен в число
        try {
            size_t pos;
            double number = std::stod(token, &pos);
            
            // Если вся строка успешно преобразована в число
            if (pos == token.length()) {
                stack.push(number);
                continue;
            }
        } catch (const std::exception&) {
            // Не число, продолжаем обработку как оператор
        }
        
        // Обработка операторов
        if (token == "+") {
            if (stack.size() < 2) {
                throw std::invalid_argument("Not enough operands for '+'");
            }
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            stack.push(a + b);
        }
        else if (token == "-") {
            if (stack.size() < 2) {
                throw std::invalid_argument("Not enough operands for '-'");
            }
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            stack.push(a - b);
        }
        else if (token == "*") {
            if (stack.size() < 2) {
                throw std::invalid_argument("Not enough operands for '*'");
            }
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            stack.push(a * b);
        }
        else if (token == "/") {
            if (stack.size() < 2) {
                throw std::invalid_argument("Not enough operands for '/'");
            }
            double b = stack.top(); stack.pop();
            if (b == 0.0) {
                throw std::invalid_argument("Division by zero");
            }
            double a = stack.top(); stack.pop();
            stack.push(a / b);
        }
        else {
            // Неизвестный токен
            throw std::invalid_argument("Invalid token: '" + token + "'");
        }
    }
    
    // Проверяем, что в стеке остался ровно один элемент
    if (stack.empty()) {
        throw std::invalid_argument("Empty expression");
    }
    if (stack.size() > 1) {
        throw std::invalid_argument("Too many operands");
    }
    
    return stack.top();
}