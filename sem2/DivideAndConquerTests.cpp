#include <iostream>
#include<fstream>
#include <chrono>
#include <float.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
using namespace std::chrono;

struct Point
{
    int x, y;
};

int compareX(const void* a, const void* b)
{
    Point *p1 = (Point *)a,  *p2 = (Point *)b;
    return (p1->x - p2->x);
}

int compareY(const void* a, const void* b)
{
    Point *p1 = (Point *)a,   *p2 = (Point *)b;
    return (p1->y - p2->y);
}


float dist(Point p1, Point p2)
{
    return sqrt( (p1.x - p2.x)*(p1.x - p2.x) +
                 (p1.y - p2.y)*(p1.y - p2.y)
    );
}

float bruteForce(Point P[], int n)
{
    float min = FLT_MAX;
    for (int i = 0; i < n; ++i)
        for (int j = i+1; j < n; ++j)
            if (dist(P[i], P[j]) < min)
                min = dist(P[i], P[j]);
    return min;
}

float min(float x, float y)
{
    return (x < y)? x : y;
}


float stripClosest(Point strip[], int size, float d)
{
    float min = d;  // Initialize the minimum distance as d

    for (int i = 0; i < size; ++i)
        for (int j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j)
            if (dist(strip[i],strip[j]) < min)
                min = dist(strip[i], strip[j]);

    return min;
}

float closestUtil(Point Px[], Point Py[], int n)
{
    // If there are 2 or 3 points, then use brute force
    if (n <= 3)
        return bruteForce(Px, n);

    // Find the middle point
    int mid = n/2;
    Point midPoint = Px[mid];


    Point Pyl[mid+1];   // y sorted points on left of vertical line
    Point Pyr[n-mid-1];  // y sorted points on right of vertical line
    int li = 0, ri = 0;  // indexes of left and right subarrays
    for (int i = 0; i < n; i++)
    {
        if (Py[i].x <= midPoint.x)
            Pyl[li++] = Py[i];
        else
            Pyr[ri++] = Py[i];
    }

    float dl = closestUtil(Px,       Pyl, mid+1  );
    float dr = closestUtil(Px+mid+1, Pyr, n-mid-1);

    // Find the smaller of two distances
    float d = min(dl, dr);

    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++)
        if (abs(Py[i].x - midPoint.x) < d)
            strip[j] = Py[i], j++;

    return min(d, stripClosest(strip, j, d) );
}

float closest(Point P[], int n)
{
    Point Px[n];
    Point Py[n];
    for (int i = 0; i < n; i++)
    {
        Px[i] = P[i];
        Py[i] = P[i];
    }

    qsort(Px, n, sizeof(Point), compareX);
    qsort(Py, n, sizeof(Point), compareY);

    // Use recursive function closestUtil() to find the smallest distance
    return closestUtil(Px, Py, n);
}

// Driver program to test above functions
int main()
{

    ifstream file;
    file.open("C:\\Users\\user\\IdeaProjects\\untitled3\\output2.txt");

    ofstream res;
    res.open("C:\\Users\\user\\CLionProjects\\untitled5\\res.txt");
    for (int i = 0; i < 50; ++i) {
        int k;
        file >> k;
        Point P[k];
        for (int i = 0; i < k; i++) {
            file >> P[i].x;
            file >> P[i].y;
        }
        auto start = steady_clock::now();
        int n = sizeof(P) / sizeof(P[0]);
        closest(P, n);
        bruteForce(P, n);
        auto stop = steady_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        res  << k << "\t" << duration.count() << endl;
    }
    res.close();
    file.close();
    return 0;
}
