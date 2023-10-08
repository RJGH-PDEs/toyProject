#include "integration.h"

// Function to be integrated
double function_1 (double x, void * params) {
    double f = x;
    return f;
}

// Function to be integrated
double function_2 (double x, void * params) {
    double f = x*x;
    return f;
}

/*
int main() {
    int n = 10;

    // Print the L_2 Inner product
    double result = inner_product(0.0, 1.0, function_1, function_2, n);
    printf ("result          = % .18f\n", result);

    return 0; // Return 0 to indicate successful execution
}
*/

// The initial condition for the PDE
double initial_condition(double x, void * args){
    // In this case f(x) = sin(2 pi x)
    return std::sin(2.0 * M_PI * x);
}

// Test the code
int main (){
    // Some variables
    double a = 0;
    double b = 1;
    int N  = 20;
    set_domain(a, b, N);

    // // Test the first one
    int j = 1;
    int power = 1;

    double (*f)(double, void *) = basis_function_1(j,power);
    graph_f1(1000, "data1.csv");

    // Test the first one
    j = 4;
    power = 3;
    
    f = basis_function_1(j,power);
    graph_f1(1000, "data2.csv");

    // Test the second one
    j = 19;
    power = 1;
    double point_of_eval = 1.0;

    f = basis_function_2(j,power);
    printf ("result          = % .18f\n", f(point_of_eval, nullptr));
    graph_f2(1000, "data3.csv");

    /*
    Test the inner product
    */

    double inner_p = integrate_against_basis(1, 1, initial_condition); 
    printf ("Inner product          = % .18f\n", inner_p);

    inner_p = integrate_against_basis(2, 1, initial_condition); 
    printf ("Inner product          = % .18f\n", inner_p);

    return 0;
}