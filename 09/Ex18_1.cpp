#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>


using std::vector;

static constexpr double EPS = 1e-15;

struct Point{
    double x;
    double y;
};

double cross_product(const Point &a, const Point &b, const Point &c){
    return (b.x - a.x)*(c.y - b.y) - (b.y - a.y)*(c.x - b.x);
}

double euclid_dist(const Point &a, const Point &b){
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void place_smallest_first(std::vector<Point> &points) {
  int smallest_ind = 0;
  for (int i = 1; i < points.size(); ++i) 
    if (points.at(i).x < points.at(smallest_ind).x) 
        smallest_ind = i; 
    std::swap(points.at(0), points.at(smallest_ind));
}

vector<Point> convex(vector<Point> &points){
    place_smallest_first(points);
    vector<Point> hull;
    Point A = points.at(0);
    std::sort(points.begin()+1, 
        points.end(), 
        [A](Point B, Point C) {
            auto product = cross_product(C, B, A);
            if (product == 0) 
                return euclid_dist(B, A) < euclid_dist(C, A);
            return product < EPS;
        });

    for (int i=0; i < points.size(); i++){
        while (hull.size() >= 2 && cross_product(hull[hull.size() - 2], hull[hull.size() - 1], points[i]) <= 0)
            hull.pop_back();
        hull.push_back(points[i - 1]);
    }
    return hull;
}

double perimeter(vector<Point> &points){
    double perimeter = 0.0;
    for (int i=0; i<points.size(); i++){
        if (i == points.size() - 1){
            perimeter += euclid_dist(points[i], points.front());
            break;
        }
        perimeter += euclid_dist(points[i], points[i+1]);
    }
    return perimeter;
}

int main(){
    int n;
    std::cin >> n;
    vector<Point> points;
    double a, b;
    for (int i=0; i<n; i++){
        std::cin >> a >> b;
        points.push_back(Point{a, b});
    }
    points = convex(points);
    double res = perimeter(points);
    std::cout << res;
    return 0;
}
