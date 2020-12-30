#include <bits/stdc++.h>

using namespace std;

struct Point{
    int x, y;
};

// find orientation of ordered triplet
// 0: p, q and r are collinear
// 1: clockwise
// 2: counterclockwise
int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0; // collinear

    return (val > 0) ? 1 : 2; // clockwise or counterclockwise
}

// prints convex hull of a set of n points
void convex_hull(Point points[], int n)
{
    // there must be at least 3 points
    if (n < 3) return;

    // initialize result
    vector<Point> hull;

    // find the leftmost point
    int l = 0;
    for (int i = 1; i < n; ++i) {
        if (points[i].x < points[l].x)
        {
            l = i;
        }
    }

    // start from leftmost point, keeping moving counterclockwise
    // until reach the start point again. This loop runs O(h)
    // h is number of points
    int p = l, q;
    do {
        // add current point to result
        hull.push_back(points[p]);

        // search for a point 'q' such that orientation
        // (p, x, q) is counterclockwise for all points 'x'.
        q = (p + 1) % n;
        for (int i = 0; i < n; ++i) {
            // if it is more counter clockwise than
            // current q, then update q
            if (orientation(points[p], points[i], points[q]) == 2)
            {
                q = i;
            }
        }

        // q is the most counterclockwise with respect to p
        // set p as q for next iteration, so that q is added to
        // result hull
        p = q;
    } while (p != l);

    // print result
    for (int i = 0; i < hull.size(); ++i) {
        cout << "(" << hull[i].x << ", " << hull[i].y << ")\n";
    }
}

int main() {
    Point points[] = {{0, 3}, {2, 2}, {1, 1}, {2, 1},
                      {3, 0}, {0, 0}, {3, 3}};

    int n = sizeof(points) / sizeof(points[0]);

    convex_hull(points, n);

    return 0;
}
