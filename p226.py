from math import floor, cos, sin, pi

N_PTS = 10_000

def s(x):
    rational_portion = x - floor(x)
    return min(rational_portion, 1 - rational_portion)

def blancmange(x, n_terms=100):
    return sum(s(pow(2, n) * x) / pow(2, n) for n in range(n_terms))

def linspace(a, b, n):
    dx = (b - a) / (n - 1)
    return [a + dx * i for i in range(n)]

def get_theta_value():
    theta = linspace(pi, 1.5 * pi, N_PTS)
    for t in theta:
        x = 0.25 + 0.25 * cos(t)
        y = 0.50 + 0.25 * sin(t)
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

t = get_theta_value()
a = 0.25 + 0.25 * cos(t)
b = 0.5
xs = linspace(a, b, N_PTS)
ys = [blancmange(x) for x in xs]

total_area = trapz(ys, xs)

theta = linspace(t, 2 * pi, N_PTS)
xs = [0.25 + 0.25 * cos(t) for t in theta]
ys = [0.50 + 0.25 * sin(t) for t in theta]

area = total_area - trapz(ys, xs)
area = round(area, 8)

print(area)
