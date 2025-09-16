

# Given points
x0, y0 = 1, 6
x1, y1 = 2, 11
x2, y2 = 3, 18


# Step 1: Calculate denominators for basis polynomials L0, L1, L2
d0 = (x0 - x1) * (x0 - x2)
print(f'd0 = (x0 - x1)*(x0 - x2) = ({x0} - {x1})*({x0} - {x2}) = {d0}')

d1 = (x1 - x0) * (x1 - x2)
print(f'd1 = (x1 - x0)*(x1 - x2) = ({x1} - {x0})*({x1} - {x2}) = {d1}')

d2 = (x2 - x0) * (x2 - x1)
print(f'd2 = (x2 - x0)*(x2 - x1) = ({x2} - {x0})*({x2} - {x1}) = {d2}')


# Step 2: Define basis polynomials L0, L1, L2 as functions of x
def L0(x):
    numerator = (x - x1) * (x - x2)
    val = numerator / d0
    print(f'L0({x}) = (({x} - {x1})*({x} - {x2}))/d0 = ({x - x1})*({x - x2})/{d0} = {val}')
    return val

def L1(x):
    numerator = (x - x0) * (x - x2)
    val = numerator / d1
    print(f'L1({x}) = (({x} - {x0})*({x} - {x2}))/d1 = ({x - x0})*({x - x2})/{d1} = {val}')
    return val

def L2(x):
    numerator = (x - x0) * (x - x1)
    val = numerator / d2
    print(f'L2({x}) = (({x} - {x0})*({x} - {x1}))/d2 = ({x - x0})*({x - x1})/{d2} = {val}')
    return val


# Step 3: Calculate P(x) at some example value, say x=1.5
x_val = 1.5
L0_val = L0(x_val)
L1_val = L1(x_val)
L2_val = L2(x_val)

P_x = y0 * L0_val + y1 * L1_val + y2 * L2_val
print(f'P({x_val}) = y0*L0({x_val}) + y1*L1({x_val}) + y2*L2({x_val}) = ' \
      f'{y0}*{L0_val} + {y1}*{L1_val} + {y2}*{L2_val} = {P_x}')



# Step 4: Expand L0, L1, L2 into quadratic form to find coefficients
# L_i(x) = a_i*x^2 + b_i*x + c_i
def lagrange_basis_coefficients(xi, xj, xk):
    denominator = (xi - xj) * (xi - xk)
    a = 1 / denominator
    b = - (xj + xk) / denominator
    c = (xj * xk) / denominator
    print(f'For xi={xi}, xj={xj}, xk={xk}:')
    print(f'  a = 1/(({xi} - {xj})*({xi} - {xk})) = {a}')
    print(f'  b = -({xj} + {xk})/(({xi} - {xj})*({xi} - {xk})) = {b}')
    print(f'  c = ({xj} * {xk})/(({xi} - {xj})*({xi} - {xk})) = {c}')
    return a, b, c

a0, b0, c0 = lagrange_basis_coefficients(x0, x1, x2)
a1, b1, c1 = lagrange_basis_coefficients(x1, x0, x2)
a2, b2, c2 = lagrange_basis_coefficients(x2, x0, x1)

# Step 5: Compute final coefficients for polynomial P(x) = a*x^2 + b*x + c
a = y0 * a0 + y1 * a1 + y2 * a2
b = y0 * b0 + y1 * b1 + y2 * b2
c = y0 * c0 + y1 * c1 + y2 * c2

print(f'\nFinal polynomial coefficients:')
print(f'a = {a}')
print(f'b = {b}')
print(f'c = {c}')
