#include <iostream>
#include <string>

class BasisFunction {
public:
    // Constructor
    BasisFunction(int i, int p) : interval(i), power(p)  {}

    // Member function to display information
    void displayInfo() {
        std::cout << "Interval: " << interval << std::endl;
        std::cout << "Power: " << power << std::endl;
    }

    // Member function to change interval and power
    void setIntPow(int i, int p) {
        interval = i;
        power    = p;
    }

private:
    int interval;
    int power;
    double a;
    double b;
    double h;
};

int main() {
    // Create an instance of the Person class
    BasisFunction person(1, 30);

    // Call the member function to display information
    person.displayInfo();

    return 0;
}
