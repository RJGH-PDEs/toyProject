#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <iostream>
#include <cmath>
#include <gsl/gsl_integration.h>

// Global variables
double (*function_toIntegrate)(double, void *);
double (*f_1)(double, void *);
double (*f_2)(double, void *);

// Returns the product of the two member variables
double product(double x, void * params) {
    double f = f_1(x, params)*f_2(x, params);
    return f;
}

// Computes the integral of the given function
double integral(double a, double b, double (*f)(double, void *), int n){
    // Set the function to be integrated as attribute
    function_toIntegrate = f;

    gsl_integration_glfixed_table * w = gsl_integration_glfixed_table_alloc(n);
    double result;

    gsl_function F;
    F.function = function_toIntegrate;

    result = gsl_integration_glfixed(&F, a, b, w);

    gsl_integration_glfixed_table_free(w);

    // return the result
    return result;
}

// Computes the L2 inner product of the two given functions
double inner_product(double a, double b, double (*f)(double, void *), double (*g)(double, void *), int n) {
    // Save the two functions to be integrated as attributes
    f_1 = f;
    f_2 = g;
 
    // Computes the inner product
    return integral(a, b, product, n);
}

// Computes the L2 norm
double L2_norm(double a, double b, double (*f)(double, void *), int n){
    // Computes the inner product
    return std::sqrt(inner_product(a, b, f, f, n));
}

#endif // INTEGRATION_H