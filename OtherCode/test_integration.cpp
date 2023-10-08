#include <iostream>
#include "integration.h"

// Function to be integrated
double function_1 (double x, void * params) {
    double alpha = *(double *) params;
    double f = alpha*x;
    return f;
}

// Function to be integrated
double function_2 (double x,  void * params) {
    double f = x*x-1;
    return f;
}

// The initial condition for the PDE
double initial_condition(double x, void * params){
    // In this case f(x) = sin(2 pi x)
    return std::sin(2.0 * M_PI * x);
}

// Test the code
int main (){
    // Domain constants
    double a = 0.0;
    double b = 1.0;

    // The parameters to be passed to function 1
    double alpha = 2.0;

    // Integrate function 1
    double result = integral(a, b, function_1, &alpha, 2);
    std::cout << "Integral: " << result << std::endl;

    // Integrate initial condition
    result = integral(a, b, initial_condition, nullptr, 2);
    std::cout << "Integral: " << result << std::endl;

    // Compute L2 norm of function 1
    result = norm_l2(a, b , function_1, &alpha, 4);
    std::cout << "Norm: " << result << std::endl;

    // Change the alpha, and compute the inner product
    // Note that no parameters are needed by function_2, therefore the passed parameter is nullptr
    alpha = 1.0;
    result = inner_product(a, b, function_1, function_2, &alpha, nullptr, 2);
    std::cout << "Inner product: " << result << std::endl;

    return 0;
}
