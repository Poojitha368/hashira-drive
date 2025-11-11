#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <cctype>

// Convert single digit (char) to int value
int charToInt(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    else if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
    else if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
    return -1;
    
}

// Convert string number in given base to decimal (unsigned long long)
unsigned long long convertToDecimal(const std::string& value, int base) {
    unsigned long long result = 0;
    for (char c : value) {
        int val = charToInt(c);
        if (val < 0 || val >= base) {
            std::cerr << "Invalid digit '" << c << "' for base " << base << std::endl;
            exit(1);
        }
        result = result * base + val;
    }
    return result;
}

// Calculate denominator (xi - xj)*(xi - xk)
double denominator(double xi, double xj, double xk) {
    return (xi - xj) * (xi - xk);
}

// Calculate Lagrange basis polynomial coefficients a,b,c for L_i(x)
void lagrange_basis_coefficients(double xi, double xj, double xk, double &a, double &b, double &c) {
    double denom = denominator(xi, xj, xk);
    a = 1.0 / denom;
    b = - (xj + xk) / denom;
    c = (xj * xk) / denom;
}

int main() {
    // Mimic JSON input data in map: key -> pair(base, number string)
    std::map<std::string, std::pair<int, std::string>> json_data = {
        {"1", {6, "13444211440455345511"}},
        {"2", {15, "aed7015a346d635"}},
        {"3", {15, "6aeeb69631c227c"}},
        {"4", {16, "e1b5e05623d881f"}},
        {"5", {8, "316034514573652620673"}},
        {"6", {3, "2122212201122002221120200210011020220200"}},
        {"7", {3, "20120221122211000100210021102001201112121"}},
        {"8", {6, "20220554335330240002224253"}},
        {"9", {12, "45153788322a1255483"}},
        {"10", {7, "1101613130313526312514143"}}
    };

    int k = 7; // Number of points to use for fitting

    // Extract first k roots converted to decimal
    std::vector<double> x_points;
    for (int i = 1; i <= 10 && (int)x_points.size() < k; ++i) {
        std::string key = std::to_string(i);
        if (json_data.find(key) == json_data.end()) continue;
        int base = json_data[key].first;
        std::string val_str = json_data[key].second;
        unsigned long long x_val = convertToDecimal(val_str, base);
        x_points.push_back(static_cast<double>(x_val));
    }

    // Example y values corresponding to x_points (replace with your real values)
    std::vector<double> y_points(k);
    for (int i = 0; i < k; ++i)
        y_points[i] = 10.0 * (i + 1);

    std::cout << "Using points (x,y):\n";
    for (int i = 0; i < k; ++i)
        std::cout << "(x" << i << ", y" << i << ") = (" << x_points[i] << ", " << y_points[i] << ")\n";

    // Compute denominator terms for first three points (quadratic)
    double d0 = denominator(x_points[0], x_points[1], x_points[2]);
    double d1 = denominator(x_points[1], x_points[0], x_points[2]);
    double d2 = denominator(x_points[2], x_points[0], x_points[1]);

    // Compute Lagrange basis coefficients a,b,c for first three points
    double a0, b0, c0, a1, b1, c1, a2, b2, c2;
    lagrange_basis_coefficients(x_points[0], x_points[1], x_points[2], a0, b0, c0);
    lagrange_basis_coefficients(x_points[1], x_points[0], x_points[2], a1, b1, c1);
    lagrange_basis_coefficients(x_points[2], x_points[0], x_points[1], a2, b2, c2);

    // Compute final polynomial coefficients
    double a = y_points[0]*a0 + y_points[1]*a1 + y_points[2]*a2;
    double b = y_points[0]*b0 + y_points[1]*b1 + y_points[2]*b2;
    double c = y_points[0]*c0 + y_points[1]*c1 + y_points[2]*c2;

    std::cout << "\nComputed polynomial coefficients:\n";
    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n";
    std::cout << "c = " << c << "\n";

    std::cout << "\nPolynomial: P(x) = " << a << " x^2 + " << b << " x + " << c << "\n";

    return 0;
}
