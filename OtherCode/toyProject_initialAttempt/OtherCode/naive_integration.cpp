#include <iostream>
#include <cmath>

// Test function to be integrated
double test_func(double x) {
    // Test function: f(x) = x + 1
    return x + 1;
}

// Given two functions, f(x) and g(x),  it will return h(x) = f(x), g(x)
double product_of_functions(double (*f)(double), double (*g)(double), double x){
    return f(x)*g(x);
}

// Gauss-Legendre quadrature
double gauss_legendre_integration(double a, double b, double (*func)(double)) {
    // Number of points 
    int num_points = 3;
    
    // Sample points and weights for Gauss-Legendre quadrature
    // Define sample points and weights based on the quadrature rule
    // These values can be precomputed for different 'num_points'
    // Here, we use values for num_points = 3

    double x_i[3] = {-0.7745966692, 0.0, 0.7745966692};
    double w_i[3] = {0.5555555555,0.8888888888,0.5555555555};

    // Calculate the integral
    double integral = 0.0;

    for (int i = 0; i < num_points; ++i) {
        double x_mapped = 0.5 * (b - a) * x_i[i] + 0.5 * (b + a); // Map x_i to [a, b]
        integral += 0.5 * (b - a) * w_i[i] * func(x_mapped);
    }

    // Return the value
    return integral;
}

// Given two functions, f(x) and g(x), it computes the L^2 inner product over the interval 
double inner_product_L2(double a, double b, double (*f)(double), double (*g)(double)){

// Number of points 
int num_points = 10;
    
// Sample points and weights for Gauss-Legendre quadrature
// Define sample points and weights based on the quadrature rule
// These values can be precomputed for different 'num_points'
// Here, we use values for num_points = 3

double x_i[10] = {  -0.1488743389816312, 0.1488743389816312, 
                    -0.4333953941292472, 0.4333953941292472,
                    -0.6794095682990244, 0.6794095682990244,
                    -0.8650633666889845, 0.8650633666889845,
                    -0.9739065285171717, 0.9739065285171717
                  };


double w_i[10] = {  0.2955242247147529, 0.2955242247147529,
                    0.2692667193099963, 0.2692667193099963,
                    0.2190863625159820, 0.2190863625159820,
                    0.1494513491505806, 0.1494513491505806,
                    0.0666713443086881, 0.0666713443086881,
                    };

// Calculate the integral
double integral = 0.0;

for (int i = 0; i < num_points; ++i) {
    double x_mapped = 0.5 * (b - a) * x_i[i] + 0.5 * (b + a); // Map x_i to [a, b]
    integral += 0.5 * (b - a) * w_i[i] * product_of_functions(f,g,x_mapped);
}

// Return the value
return integral;

}

// Given a function, f(x), it returns the L_2 norm over the interval
double norm_L2(double a, double b, double (*f)(double)){
    return std::sqrt(inner_product_L2(a, b, f, f));
}

// Test the numerical integration
int main() {
    double a = 0.0;     // Start of the integration domain
    double b = 10;      // End of the integration domain

    // Integrates the function
    double result = norm_L2(a, b, std::log);

    // Print the result
    std::cout << "Approximate integral from " << a << " to " << b << ": " << result << std::endl;

    return 0;
}