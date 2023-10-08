#include <iostream>

// Define a simple struct
struct MyStruct {
    int x;
    double (*f_1)(double);
    double y;
};

// A function that takes a void* as a parameter
void ProcessData(double x, void* data) {
    // Cast the void* back to the struct type
    MyStruct* structPtr = static_cast<MyStruct*>(data);

    double (*f)(double) = structPtr->f_1;

    // Access and use the struct members
    std::cout << "f(0): " << f(x) << std::endl;   
    std::cout << "x: " << structPtr->x << std::endl;
    std::cout << "y: " << structPtr->y << std::endl;
}

double functionToPass(double x){
    return x - 1.0;
}

int main() {
    // Create an instance of MyStruct
    MyStruct myData;
    myData.x = 10;
    myData.y = 3.14;
    myData.f_1 = functionToPass;

    // Pass a pointer to the struct to the ProcessData function
    ProcessData(4, &myData);

    return 0;
}