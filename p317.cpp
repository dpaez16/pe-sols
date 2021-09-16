#include <bits/stdc++.h>

using namespace std;

#define INITIAL_HEIGHT      100
#define INITIAL_SPEED       20
#define G                   9.81
#define N_PLACES            4

/*
    Computes horizontal distance that a projectile will travel
    when launched from (0, h) with velocity INITIAL_SPEED * (cos(theta), sin(theta)).

    Below is the equation of the height of a projectile over time:
    y(t) = INITIAL_HEIGHT + INITIAL_SPEED * sin(theta) - 0.5 * G * t^2                                                                          (1)

    When setting (1) equal to 0, we get:
    t(theta) = (INITIAL_SPEED * sin(theta) + sqrt(INITIAL_SPEED^2 * sin^2(theta) + 2 * G * INITIAL_HEIGHT)) / G                                 (2)

    (2) computes the total air time of a projectile. 
    Below is the equation for the total horizontal distance of the projectile:

    x(theta) = INITIAL_SPEED * cos(theta) * t                                                                                                   (3)

    Substituting (2) in (3), we get:

    x(theta) = INITIAL_SPEED * cos(theta) * (INITIAL_SPEED * sin(theta) + sqrt(INITIAL_SPEED^2 * sin^2(theta) + 2 * G * INITIAL_HEIGHT)) / G	(4)
*/
double f(double theta) {
    double v = INITIAL_SPEED;
    double g = G;
    double h = INITIAL_HEIGHT;
    
    return (powl(v, 2) * sinl(theta) * cosl(theta) + v * cosl(theta) * sqrt(powl(v * sinl(theta), 2) + 2 * g * h)) / g;
}

/*
    Derivative of above function. Used Wolfram to compute it.
*/
double df(double theta) {
    double v = INITIAL_SPEED;
    double g = G;
    double h = INITIAL_HEIGHT;
    
    return -(v * sinl(theta) * sqrt(2 * g * h + powl(v * sinl(theta), 2))) / g + \
            (powl(v, 3) * sinl(theta) * powl(cosl(theta), 2)) / (g * sqrt(2 * g * h + powl(v * sinl(theta), 2))) - \
            powl(v * sinl(theta), 2) / g + powl(v * cosl(theta), 2) / g;
}

/*
    Finds root of f, where root lies in the interval.
*/
double find_zero(double (*f)(double), pair<double, double> interval, double eps=1e-6) {
    double a = interval.first;
    double b = interval.second;
    
    while (abs((b - a) / 2) > eps) {
        double m = (a + b) / 2;
        if (f(a) * f(m) < 0)
            b = m;
        else
            a = m;
    }

    return (a + b) / 2;
}

/*
    Computes volume of solid of revolution of firework trajectory.

    The surrounding area a 2D firecracker covers is a symmetric upside-down parabola.
    It will be of the form:
    
    g(x) = ax^2 + c										(5)

    We can see that f(0) = c = the highest point a fragment of the firework will travel.
    This value will be:

    c = INITIAL_HEIGHT + INITIAL_SPEED^2 / 2 * G

    To figure out `a`, we observe that the zeros of (5) represent the furthest points a
    fragment will travel before hitting the ground. 
    
    To compute these points, we must find the optimal angle that yields the maximum 
    horizontal distance traveled (i.e. the optimal angle that maximizes (4)). 
    We will compute this optimal angle through the bisection method.

    Once we have this value (call it `x_c`). We can figure out `a` like so:

    g(x_c) = ax_c^2 + c = 0    ==>    a = -c / x_c^2

    Now we have both coefficients of (5), we can compute the volume covered by a 3D
    firework by computing the volume of solid of revolution like so:

    \int_0^{x_c} 2 * pi * x * g(x) dx = \int_0^{x_c} 2 * pi * x * (ax^2 + c) dx
                                      = 0.5 * pi * a * x_c^4 + pi * c * x_c^2
*/
double volume() {
    double optimal_angle = find_zero(df, {-M_PI / 2, M_PI / 2});
    double highest_x = f(optimal_angle);
    double highest_y = INITIAL_HEIGHT + powl(INITIAL_SPEED, 2) / (2 * G);
    
    double x = highest_x;
    double h = highest_y;
    double a = -h / powl(highest_x, 2);
    return 0.5 * M_PI * a * powl(x, 4) + M_PI * h * powl(x, 2);
}

double round_n_places(double x, int n) {
    return round(pow(10, n) * x) / pow(10, n);
}

string format_ans(double x) {
    string x_str = to_string(x);
    size_t pos = x_str.find('.');
	if (pos != x_str.npos) x_str = x_str.substr(0, pos + N_PLACES + 1);

    return x_str;
}

int main() {
    double ans = round_n_places(volume(), N_PLACES);
    string ans_str = format_ans(ans);
    cout << ans_str << endl;
    return 0;
}
