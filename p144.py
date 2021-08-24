import math

class Vector:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    
    def __add__(self, other):
        return Vector(
            self.x + other.x,
            self.y + other.y
        )
    
    def __sub__(self, other):
        return Vector(
            self.x - other.x,
            self.y - other.y
        )
    
    def __mul__(self, c):
        return Vector(
            c * self.x,
            c * self.y
        )
    
    def __neg__(self):
        return self * -1
    
    def __abs__(self):
        x, y = self.x, self.y
        return math.sqrt(x ** 2 + y ** 2)
    
    def __eq__(self, other):
        eps = 1e-3
        return abs(self - other) <= eps
    
    def __repr__(self):
        x, y = self.x, self.y
        return f'({x}, {y})'
    
    def angle(self):
        if self.x != 0:
            return math.atan(self.y / self.x)
        
        if self.y > 0:
            return math.pi / 2
        elif self.y < 0:
            return 3 * math.pi / 2
        else:
            return math.atan(0 / 0)

    def normalize(self):
        return self * (1. / abs(self))

    def rotate(self, theta):
        x, y = self.x, self.y
        return Vector(
            x * math.cos(theta) - y * math.sin(theta),
            x * math.sin(theta) + y * math.cos(theta)
        )
    
    @staticmethod
    def dot(a, b):
        return a.x * b.x + a.y * b.y
    
    @staticmethod
    def angle_between(a, b):
        return math.acos(
            round(abs(Vector.dot(a.normalize(), b.normalize())), 10)
        )

def get_eqn(u, d):
    v = u + d
    m = (v.y - u.y) / (v.x - u.x)
    b = u.y - m * u.x
    return (m, b)

def eqn(p):
    x, y = p.x, p.y
    return abs(4 * x ** 2 + y ** 2 - 100)

def slope(p):
    x, y = p.x, p.y
    return -4 * x / y

def find_zeros(u, d):
    m, b = get_eqn(u, d)
    
    a_ = m ** 2 + 4
    b_ = 2 * m * b
    c_ = b ** 2 - 100
    
    return [
        (-b_ + math.sqrt(b_ ** 2 - 4 * a_ * c_)) / (2 * a_),
        (-b_ - math.sqrt(b_ ** 2 - 4 * a_ * c_)) / (2 * a_)
    ]
            
def get_next_point(u, d):
    m, b = get_eqn(u, d)
    g = lambda x: m * x + b
    
    zeros = find_zeros(u, d)
    x = max(zeros, key = lambda z: abs(z - u.x))
    y = g(x)
    return Vector(x, y)

def get_incident_angles(v, d):
    a = -d
    b = Vector(1, slope(v))

    theta1 = Vector.angle_between(a, b)
    theta2 = math.pi - theta1
    
    angles = sorted([theta1, theta2])
    return angles

def get_next_direction(prev_dir, v, angles, eps=1e-2):
    d = Vector(1, slope(v))
    
    new_d = d.rotate(angles[0])
    if abs(Vector.angle_between(-prev_dir, new_d)) <= eps:
        return d.rotate(angles[1])
    
    return new_d

exit_point = Vector(0, 10)
eps = 1e-2

u = Vector(0, 10.1)
d = Vector(1.4, -9.6) - u
bounces = 0

while True:
    v = get_next_point(u, d)
    if abs(v - exit_point) <= eps:
        break
    
    angles = get_incident_angles(v, d)
    d = get_next_direction(d, v, angles)
    u = Vector(v.x, v.y)
    bounces += 1

print(bounces)