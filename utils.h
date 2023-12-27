#include "polygon.h"
#include "constants.h"
#include <algorithm>
#include <numeric>
#include <math.h>

#ifndef UTILS_H
#define UTILS_H

namespace GeomUtils {

    // A general point location detection function applicable to any
    // type of points, and not just Vertex objects.
    bool isPointBetweenPoints(vector<double>* testPt, vector<double>* checkPoint1, vector<double>* checkPoint2) {
        double pt1Coords[2] = {(*checkPoint1)[0], (*checkPoint1)[1]};
        double pt2Coords[2] = {(*checkPoint2)[0], (*checkPoint2)[1]};
        double testPtCoords[2] = {(*testPt)[0], (*testPt)[1]};
        double distTotal = sqrt(pow(pt1Coords[0] - pt2Coords[0], 2) + pow((pt1Coords[1] - pt2Coords[1]), 2));
        double distP1 = sqrt(pow(pt1Coords[0] - testPtCoords[0], 2) + pow((pt1Coords[1] - testPtCoords[1]), 2));
        double distP2 = sqrt(pow(testPtCoords[0] - pt2Coords[0], 2) + pow((testPtCoords[1] - pt2Coords[1]), 2));
        if ((distP1 < distTotal) && (distP2 < distTotal)) {
            return true;
        } else {
            return false;
        }
    }

    // A simple struct to contain both the actual intersection point, and the
    // computed determinant. This is required as the computed intersection
    // could be the default (0, 0), and we need to ensure that any point
    // is accepted only if the determinant is as intended.
    struct intersectionResult {
        double determinantCheck;
        vector<double> intersection;
    };

    intersectionResult computeIntersection(Vertex* edge1Vert1, Vertex* edge1Vert2, \
                                           Vertex* edge2Vert1, Vertex* edge2Vert2) {
        vector<double> intVert;
        vector<double> coords11 = (*edge1Vert1->getCoordinates());
        vector<double> coords12 = (*edge1Vert2->getCoordinates());
        vector<double> coords21 = (*edge2Vert1->getCoordinates());
        vector<double> coords22 = (*edge2Vert2->getCoordinates());

        double determinant = (coords11[0] - coords12[0]) * (coords21[1] - coords22[1]) -
                             (coords11[1] - coords12[1]) * (coords21[0] - coords22[0]);
        
        if (determinant != 0.0) {
            double x = ((coords11[0] * coords12[1] - coords11[1] * coords12[0]) * 
                        (coords21[0] - coords22[0]) - (coords11[0] - coords12[0]) * 
                        (coords21[0] * coords22[1] - coords21[1] * coords22[0])) / determinant;
            double y = ((coords11[0] * coords12[1] - coords11[1] * coords12[0]) * 
                        (coords21[1] - coords22[1]) - (coords11[1] - coords12[1]) * 
                        (coords21[0] * coords22[1] - coords21[1] * coords22[0])) / determinant;
            
            intVert.push_back(x);
            intVert.push_back(y);
        };

        intersectionResult result;
        result.determinantCheck = determinant;
        result.intersection = intVert;
        return result;
    }
    
    vector<vector<double>> computePgonIntersections(Polygon &pgon1, Polygon &pgon2) {
        vector<vector<double>> foundIntersections;
        vector<Vertex>* pgon1Vertices = &pgon1.getVertices();
        // using each edge of theW first polygon, and comparing with each
        // edge of the second polygon to determine intersections.
        for (int i = 0; i < pgon1Vertices->size(); i++) {
            // we need to eliminate not intersecting edges in the second polygon
            // from the intersection search algorithm for computation efficiency.
            vector<int> edgesToEliminate;
            Vertex currVert = (*pgon1Vertices)[i];
            Vertex nextVert = (i != pgon1Vertices->size() - 1) ? 
                (*pgon1Vertices)[i + 1] : (*pgon1Vertices)[0];
            vector<Vertex>* pgon2Vertices = &pgon2.getVertices();
            for (int j = 0; j < pgon2Vertices->size(); j++) {
                //auto iterator = find(edgesToEliminate.begin(), edgesToEliminate.end(), j);
                //if (iterator == edgesToEliminate.end()) {
                vector<double> intersection;
                Vertex currVert2 = (*pgon2Vertices)[j];
                Vertex nextVert2 = (j != pgon2Vertices->size() - 1) ? 
                    (*pgon2Vertices)[j + 1] : (*pgon2Vertices)[0];
                intersectionResult result = computeIntersection(&currVert, &nextVert, 
                                                    &currVert2, &nextVert2);
                if ((result.determinantCheck != 0.0) && 
                    (isPointBetweenPoints(&result.intersection, currVert.getCoordinates(), nextVert.getCoordinates())) &&
                    (isPointBetweenPoints(&result.intersection, currVert2.getCoordinates(), nextVert2.getCoordinates()))) {
                    foundIntersections.push_back(result.intersection);
                    cout << "Found intersection for: " + to_string(j) + "\n";
                } else {
                    edgesToEliminate.push_back(j);
                }
                //}
            }
        }
        return foundIntersections;
    };

    /*

    bool isVertInsidepgon(Vertex &testVert, Polygon &pgon) {

    };

    Polygon union2D(Polygon &pgon1, Polygon &pgon2) {

    };

    Polygon intersection2D(Polygon &pgon1, Polygon &pgon2) {

    };

    Polygon subtract2D(Polygon &pgon1, Polygon &pgon2) {

    };

    */
}

#endif