#include <iostream>
#include <stdexcept>
#include "../include/rpn.h"

int main() {
    std::string expression;
    std::cout << "Enter RPN expression: ";
    std::getline(std::cin, expression);
    
    try {
        double result = evaluate_rpn(expression);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}