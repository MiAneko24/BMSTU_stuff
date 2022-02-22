from math import cos, pi, sin, trunc, sqrt

functions = {
    "sin^2(x) + cos^2(z) - y = 0": lambda x, z: sin(x)**2 + cos(z)**2,
    "sqrt(|sin(cos(x))|) + z / 2 - y = 0": lambda x, z: sqrt(abs(sin(cos(x)))) + z / 2,
    "sin(x) - cos(x) + x*z - y = 0": lambda x, z: sin(x) - cos(z) + x*z, 
    'y = sqrt(x^2 / 3 + z^2)' : lambda x, z: sqrt(x**2  / 3 + z ** 2),
    'y = sin(x) * cos(z) * cos(x * z)' : lambda x, z: sin(x) * cos(z) * cos(x * z),
    'y = x^2 + z^2' : lambda x, z: x**2 + z ** 2,
}