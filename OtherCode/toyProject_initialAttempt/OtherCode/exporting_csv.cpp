#include <iostream>
#include <fstream>

// Create a vector of evenly spaced numbers.
std::vector<double> range(double min, double max, size_t N) {
    std::vector<double> my_range;
    double delta = (max-min)/double(N);
    for(int i=0; i<N+1; i++) {
        //std::cout << min +i*delta << std::endl;
        my_range.push_back(min + i*delta);
    }
    return my_range;
}

/*
Saves a csv file called "data.csv" where the first row containes the values of x
and the second row contains the values of f(x).

Arguments:
- double a: the start of graphing domain
- double b: the end   of graphing domain
- int N:    the number of intervals in the domain
- f:        the function to be graphed

The data.csv file may then be opened in MATLAB (or python) for graphing purposes
*/ 

int export_csv(double a, double b, int N, double (*f)(double, void *)){
    // Create a double array (or vector) with data
    std::vector<double> data = range(a,b,N);

    // Specify the CSV file name
    const std::string csvFileName = "data.csv";

    // Open the CSV file for writing
    std::ofstream csvFile(csvFileName);

    // Check if the file was successfully opened
    if (!csvFile.is_open()) {
        std::cerr << "Error: Could not open the CSV file." << std::endl;
        return 1; // Exit with an error code
    }

    // Write the data to the CSV file
    for (size_t i = 0; i < data.size(); ++i) {
        csvFile << data[i];
        // Add a comma except for the last element
        if (i < data.size() - 1) {
            csvFile << ",";
        }
    }

    // Add a newline character to end the row
    csvFile << std::endl;

    // Write the data of the fuction to the CSV file
    for (size_t i = 0; i < data.size(); ++i) {
        csvFile << f(data[i], nullptr);
        // Add a comma except for the last element
        if (i < data.size() - 1) {
            csvFile << ",";
        }
    }

    // Close the CSV file
    csvFile.close();

    std::cout << "Data has been saved to " << csvFileName << std::endl;

    return 0;
}

// int main() {
//     // Set the domain and the number of intervals;
//     double a = 0;
//     double b = 1.0;
//     double N = 50;

//     // Create a double array (or vector) with data
//     std::vector<double> data = range(a,b,N);

//     // Specify the CSV file name
//     const std::string csvFileName = "data.csv";

//     // Open the CSV file for writing
//     std::ofstream csvFile(csvFileName);

//     // Check if the file was successfully opened
//     if (!csvFile.is_open()) {
//         std::cerr << "Error: Could not open the CSV file." << std::endl;
//         return 1; // Exit with an error code
//     }

//     // Write the data to the CSV file
//     for (size_t i = 0; i < data.size(); ++i) {
//         csvFile << data[i];
//         // Add a comma except for the last element
//         if (i < data.size() - 1) {
//             csvFile << ",";
//         }
//     }

//     // Add a newline character to end the row
//     csvFile << std::endl;

//     // Write the data of the fuction to the CSV file
//     for (size_t i = 0; i < data.size(); ++i) {
//         csvFile << std::sin(2.0*M_PI*data[i]);
//         // Add a comma except for the last element
//         if (i < data.size() - 1) {
//             csvFile << ",";
//         }
//     }

//     // Close the CSV file
//     csvFile.close();

//     std::cout << "Data has been saved to " << csvFileName << std::endl;

//     return 0; // Exit with success
// }