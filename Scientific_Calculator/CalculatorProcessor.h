#pragma once
#include <string>

class CalculatorProcessor
{
private:
    // static pointer to singleton instance - CalculatorProcessor
    static CalculatorProcessor* instance;

    // Private constructor - helps prevent multiple instances
    CalculatorProcessor() {} 

public:
    // Clean up memory leak
    static void CleanUpInstance();
    // Delete copy constructor and assignment operator to prevent copies of instance
    CalculatorProcessor(const CalculatorProcessor&) = delete;
    CalculatorProcessor& operator=(const CalculatorProcessor&) = delete;

    // Get the singleton instance - CalculatorProcessor
    static CalculatorProcessor* GetInstance();

    // Calculate method with inputted values
    float Calculate(const std::string& expression);
};

