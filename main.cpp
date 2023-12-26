#include <iostream>
#include "utils.h"
#include "polygon.h"
#include "tests.h"

using namespace GeomUtils;  

int main() {

    Polygon rect;
    rect.addVertex(2, 4);
    rect.addVertex(2, 6);
    rect.addVertex(1, 6);
    rect.addVertex(1, 4);

    Polygon poly;
    poly.addVertex(2.4, 4.4);
    poly.addVertex(2.4, 3.6);
    poly.addVertex(1.3, 3.6);
    poly.addVertex(1.3, 3.8);
    poly.addVertex(1.7, 4.4);

    vector<vector<double>> intersections = computeNgonIntersections(rect, poly);
    cout << "Number of intersections: " + to_string(intersections.size());
    cout << "\n\n";
    for (int i = 0; i < intersections.size(); i++) {
        cout << to_string(intersections[i][0]) + ", " + to_string(intersections[i][1]) + "\n";
    }
    
    cout << "\n\n";

};