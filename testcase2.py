import json

# Corrected sample JSON input without extra braces
json_data = {
    "keys": {
        "n": 10,
        "k": 7
    },
    "1": {
        "base": "6",
        "value": "13444211440455345511"
    },
    "2": {
        "base": "15",
        "value": "aed7015a346d635"
    },
    "3": {
        "base": "15",
        "value": "6aeeb69631c227c"
        
    },
    "4": {
        "base": "16",
        "value": "e1b5e05623d881f"
    },
    "5": {
        "base": "8",
        "value": "316034514573652620673"
    },
    "6": {
        "base": "3",
        "value": "2122212201122002221120200210011020220200"
    },
    "7": {
        "base": "3",
        "value": "20120221122211000100210021102001201112121"
    },
    "8": {
        "base": "6",
        "value": "20220554335330240002224253"
    },
    "9": {
        "base": "12",
        "value": "45153788322a1255483"
    },
    "10": {
        "base": "7",
        "value": "1101613130313526312514143"
    }
}

# Step 1: Extract roots x_i from JSON and convert to decimal integers
roots = []
for key in json_data:
    if key == "keys":
        continue
    base = int(json_data[key]["base"])
    val_str = json_data[key]["value"]
    x_val = int(val_str, base)
    roots.append(x_val)

# Here for example, we pick first k roots for polynomial fit
k = json_data["keys"]["k"]
x_points = roots[:k]

# Step 2: Define corresponding y_i values (replace with your actual y values)
# For example purposes only, defining arbitrary y points:
y_points = [10 * (i + 1) for i in range(k)]  # [10, 20, 30, 40, 50, 60, 70]

print("Using points:")
for i in range(k):
    print(f"(x{i}, y{i}) = ({x_points[i]}, {y_points[i]})")

# Step 3: Calculate denominator for Lagrange basis polynomials
def denominator(xi, xj, xk):
    return (xi - xj) * (xi - xk)

d0 = denominator(x_points[0], x_points[1], x_points[2])
d1 = denominator(x_points[1], x_points[0], x_points[2])
d2 = denominator(x_points[2], x_points[0], x_points[1])

# Step 4: Calculate Lagrange basis polynomial coefficients
def lagrange_basis_coefficients(xi, xj, xk):
    denom = (xi - xj) * (xi - xk)
    a = 1 / denom
    b = - (xj + xk) / denom
    c = (xj * xk) / denom
    return a, b, c

a0, b0, c0 = lagrange_basis_coefficients(x_points[0], x_points[1], x_points[2])
a1, b1, c1 = lagrange_basis_coefficients(x_points[1], x_points[0], x_points[2])
a2, b2, c2 = lagrange_basis_coefficients(x_points[2], x_points[0], x_points[1])

# Step 5: Calculate final polynomial coefficients
a = y_points[0] * a0 + y_points[1] * a1 + y_points[2] * a2
b = y_points[0] * b0 + y_points[1] * b1 + y_points[2] * b2
c = y_points[0] * c0 + y_points[1] * c1 + y_points[2] * c2

print("\nComputed polynomial coefficients:")
print(f"a = {a}")
print(f"b = {b}")
print(f"c = {c}")
print(f"\nPolynomial: P(x) = {a} x^2 + {b} x + {c}")
