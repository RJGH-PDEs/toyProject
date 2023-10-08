#ifndef BASIS_FUNCTIONS_H
#define BASIS_FUNCTIONS_H

#include <iostream>
#include <cmath>
#include <vector>
#include "export_csv.h"  // <-- saves a function as csv file for graphing purposes
// #include "integration.h" // <-- integration header

/*

This code defines the code for two basis functions, they are two identical copies,
and the purpose of having two of them is so that other methods that may require two
different definitions of the basis vectors (such as the inner product in the integration
header), will have the two independent copies to work with. 

*/

/*

This flag contains information on how to compute the the domain of integration for
each basis function. If manual is true, then we would need to specify the domain of
each function (meaning there is no need of a j, and we use a and h instead) each 
time we want to use the function. If manual is false, then we need to set the domain
of the whole PDE and the number of intervals (by setting a, b, and N) and each time we 
want to use a basis function, we simply input the power and the number of the interval
(j)

*/

bool manual = false;

// This variables contain the information on the whole domain of the PDE, and the 
// number of intervals. 
double a;
double b;
int N;
double h;

// The variables that modify the end points of the domain of the basis functions
// This basis vector will be non-zero in the interval [a, a + h]
double a_1;
double h_1;
int j_1;
int power_1;

double a_2;
double h_2;
int j_2;
int power_2;

// The first basis function
double function_1(double x, void * params) {
    // This is the value that will be returned
    double f = 0.0;

    // This is the middle point of the interval
    double x_j = a_1 + h_1/2;

    if (x >= a_1 && x <= a_1 + h_1) {
    // Value is within the interval [a, a + h]
    f = (x - x_j)/h_1;

    } else {
    // The basis function is 0 outside the interval
    f = 0;
    }

    return std::pow(f, power_1);
}

// The second basis function
double function_2(double x, void * params) {
    // This is the value that will be returned
    double f = 0.0;

    // This is the middle point of the interval
    double x_j = a_2 + h_2/2;

    if (x >= a_2 && x <= a_2 + h_2) {
    // Value is within the interval [a, a + h]
    f = (x - x_j)/h_2;

    } else {
    // The basis function is 0 outside the interval
    f = 0;
    }

    return std::pow(f, power_2);
}

// Sets the domain variables for the problem, this function needs to be called before
// using the basis vectors in manual = false mode
void set_domain(double a_arg, double b_arg, int N_arg){
    a = a_arg;
    b = b_arg;
    N = N_arg;

    // Computes h
    double N_h = N; // Parse the N into double so that computation can be performed.
    h = (b-a)/N_h;
}

/*

Returns a reference to the basis function in manual = false mode
A function that returns a reference to another function based on a choice
Parameters:
j_arg: the interval number
power_arg: the power of the basis function

*/

double (*basis_function_1(int j_arg, int power_arg))(double, void *) {
    // Change to auto
    manual = false;

    // Set the values of function 1
    j_1 = j_arg;
    power_1 = power_arg;
    a_1 = a + (h)*(j_1-1);
    h_1 = h;

    // Return the function
    return function_1;
}

double (*basis_function_2(int j_arg, int power_arg))(double, void *) {
    // Change to auto
    manual = false;

    // Set the values of function 2
    j_2 = j_arg;
    power_2 = power_arg;
    a_2 = a + (h)*(j_2-1);
    h_2 = h;

    // Return the function
    return function_2;
}

/*
double (*basis_function_manual_1(double a_arg, double h_arg, int power_arg))(double, void *) {
    // Change to manual
    manual = true;

    // Set the values of the function 1;
    double a_1 = a_arg;
    double h_1 = h_arg;
    int power_1 = power_arg;

    // Return the function
    return function_1;
}
*/

/*
Used to graph the functions
*/
void graph_f1(int N, const std::string& str){
    export_csv(a,b,N, function_1, str);
}

void graph_f2(int N, const std::string& str){
    export_csv(a,b,N, function_2, str);
}

/*

Will compute the inner product between a function given as an argument and
one of the basis vectors

*/

double integrate_against_basis(int j, int power, double (*f)(double, void *)){
    // Create the basis function
    double (*b_f)(double, void *) = basis_function_1(j, power);
 
    // Print the relevant info
    printf ("a_1            = % .18f\n", a_1);
    printf ("a_1+h          = % .18f\n", a_1+h);

    // return the inner product
    return inner_product(a_1, a_1+h, b_f, f,10);
}

/*

This computes the inner product bewteen two different basis functions

*/

double basis_inner_product(int j_a, int p_a, int j_b, int p_b){
    // If the intersection of their support is empty, the inner product is 0
    if(j_a == j_b){
        return 0.0;
    }

    // If not, compute their inner product
    return integral(a_1, a_1 + h, basis_function_1(j_a, p_a + p_b), 10); 
}

#endif // EXPORTCSV_H