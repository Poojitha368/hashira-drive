#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <cctype>

// Function to convert a single character to its integer value
int charToInt(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    else if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
    else if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
    else return -1; // error
}

// Convert a number string in any base (up to 16) to decimal (unsigned long long)
unsigned long long convertToDecimal(const std::string& valueStr, int base) {
    unsigned long long result = 0;
    for (char c : valueStr) {
        int val = charToInt(c);
        if (val < 0 || val >= base) {
            std::cerr << "Invalid character '" << c << "' for base " << base << std::endl;
            exit(1);
        }
        result = result * base + val;
    }
    return result;
}

// Calculate denominator (xi - xj) * (xi - xk)
double denominator(double xi, double xj, double xk) {
    return (xi - xj) * (xi - xk);
}

// Calculate Lagrange basis polynomial coefficients a, b, c
std::vector<double> lagrangeBasisCoefficients(double xi, double xj, double xk) {
    double denom = denominator(xi, xj, xk);
    double a = 1.0 / denom;
    double b = - (xj + xk) / denom;
    double c = (xj * xk) / denom;
    return {a, b, c};
}

int main() {
    // Simulate the JSON key-value pairs
    // Format: key -> pair(base, string_value)
    std::map<std::string, std::pair<int, std::string>> jsonData = {
        {"1", {10, "4"}},
        {"2", {2, "111"}},
        {"3", {10, "12"}},
        {"6", {4, "213"}}
    };

    int k = 3; // degree+1, number of roots to fit quadratic polynomial

    // Extract roots and convert to decimal
    std::vector<double> x_points;
    for (int i = 1; i <= 6; ++i) {
        std::string key = std::to_string(i);
        if (jsonData.find(key) == jsonData.end())
            continue;
        int base = jsonData[key].first;
        std::string valStr = jsonData[key].second;
        unsigned long long val = convertToDecimal(valStr, base);
        x_points.push_back(static_cast<double>(val));
        if ((int)x_points.size() == k) break;
    }

    // Define example y values (replace with actual values as needed)
    std::vector<double> y_points = {10, 20, 30};

    // Print points used
    std::cout << "Using points:\n";
    for (int i = 0; i < k; ++i) {
        std::cout << "(x" << i << ", y" << i << ") = (" << x_points[i] << ", " << y_points[i] << ")\n";
    }

    // Calculate Lagrange basis coefficients
    std::vector<double> a_b_c_0 = lagrangeBasisCoefficients(x_points[0], x_points[1], x_points[2]);
    std::vector<double> a_b_c_1 = lagrangeBasisCoefficients(x_points[1], x_points[0], x_points[2]);
    std::vector<double> a_b_c_2 = lagrangeBasisCoefficients(x_points[2], x_points[0], x_points[1]);

    // Compute final polynomial coefficients
    double a = y_points[0]*a_b_c_0[0] + y_points[1]*a_b_c_1[0] + y_points[2]*a_b_c_2[0];
    double b = y_points[0]*a_b_c_0[1] + y_points[1]*a_b_c_1[1] + y_points[2]*a_b_c_2[1];
    double c = y_points[0]*a_b_c_0[2] + y_points[1]*a_b_c_1[2] + y_points[2]*a_b_c_2[2];

    std::cout << "\nComputed polynomial coefficients:\n";
    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n";
    std::cout << "c = " << c << "\n";
    std::cout << "\nPolynomial: P(x) = " << a << " x^2 + " << b << " x + " << c << "\n";

    return 0;
}
