from math import floor, cos, sin, pi

N_PTS = 10_000
CENTRE = (0.25, 0.50)
RADIUS = 0.25

def s(x):
    rational_portion = x - floor(x)
    return min(rational_portion, 1 - rational_portion)

def blancmange(x, n_terms=100):
    return sum(s(pow(2, n) * x) / pow(2, n) for n in range(n_terms))

def linspace(a, b, n):
    dx = (b - a) / (n - 1)
    return [a + dx * i for i in range(n)]

def get_theta_value():
    c_x, c_y = CENTRE
    theta = linspace(pi, 1.5 * pi, N_PTS)
    for t in theta:
        x = c_x + RADIUS * cos(t)
        y = c_y + RADIUS * sin(t)
        y_b = blancmange(x)

        if abs(y_b - y) <= 1e-5:
            return t

    return -1

def trapz(ys, xs):
    total = 0
    for i in range(1, len(xs)):
        dx = xs[i] - xs[i - 1]
        total += (ys[i] + ys[i - 1]) * 0.5 * dx

    return total

"""
    The circle intersects with the curve at two points.
    We can see that one of the values is t = 0:
        circle(t) = (0.25, 0.50) + 0.25 * exp(i * t)
        blancmange(0.5) = 0.5
        circle(0).x = 0.5

    The other intersection point can be solved for numerically (get_theta_value).
    Then we calculate the answer through numerical integration.
"""

t = get_theta_value()
a = CENTRE[0] + RADIUS * cos(t)
b = CENTRE[0] + RADIUS * cos(0)
xs = linspace(a, b, N_PTS)
ys = [blancmange(x) for x in xs]

total_area = trapz(ys, xs)

theta = linspace(t, 2 * pi, N_PTS)
xs = [CENTRE[0] + RADIUS * cos(t) for t in theta]
ys = [CENTRE[1] + RADIUS * sin(t) for t in theta]

area = total_area - trapz(ys, xs)
area = round(area, 8)

print(area)
