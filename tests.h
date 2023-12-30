#include <iostream>
#include "utils.h"

using namespace GeomUtils;

/*
void intersectionTests() {

    Vertex testVert1{1.5, 1.0};
    Vertex testVert2{1.8, 4.0};
    Vertex testVert3{0.5, 2.0};
    Vertex testVert4{3.0, 2.0};
    Vertex resultVert1 = computeIntersection(&testVert1, &testVert2, &testVert3, &testVert4);
    double* resultCoords = resultVert1.getCoordinates();
    cout << "(" + to_string(resultCoords[0]) + ", " + to_string(resultCoords[1]) + ")";

}
*/

void pointInsidePgonTests() {
    
    Polygon testPgon;
    testPgon.addVertex(2, 4);
    testPgon.addVertex(2, 6);
    testPgon.addVertex(1, 6);
    testPgon.addVertex(1, 4);

    Vertex testPoint1{0, 0};
    Vertex testPoint2{2.2, 4.5};
    Vertex testPoint3{1.2, 5.8};

    cout << "###### TESTING IsPointInsidePgon ######" << "\n";
    cout << "Intersection validity: " + to_string(isPointInsidePgon(testPoint1, testPgon)) << "\n";
    cout << "Intersection validity: " + to_string(isPointInsidePgon(testPoint2, testPgon)) << "\n";
    cout << "Intersection validity: " + to_string(isPointInsidePgon(testPoint3, testPgon)) << "\n";
    cout << "\n";
}