#include "polygon.h"
#include "constants.h"
#include <algorithm>
#include <numeric>
#include <math.h>

#ifndef UTILS_H
#define UTILS_H

namespace GeomUtils {

    // A simple struct to contain both the actual intersection point, and the
    // validity of the intersection. This is required as the computed intersection
    // could be the default (0, 0), and we need to ensure that any point is 
    // accepted only if the determinant and point location is as intended.
    struct intersectionResult {
        bool isValid;
        vector<double> intersection;
    };

    // A general point location detection function applicable to any
    // type of points, and not just Vertex objects.
    static inline bool isPointBetweenPoints(vector<double>* testPt, vector<double>* checkPoint1, vector<double>* checkPoint2) {
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

    // A comprehensive generic intersection computation function to determine the 
    // intersection between two edges / lines. Function ensures that the computed
    // point actually is colinear with the provided set prior to returning.
    static inline intersectionResult computeIntersection(Vertex* edge1Vert1, Vertex* edge1Vert2, \
                                           Vertex* edge2Vert1, Vertex* edge2Vert2) {
        vector<double> intVert;
        bool validity = false;
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
            vector<double> tempPt{x, y};
            
            if ((isPointBetweenPoints(&tempPt, &coords11, &coords12)) && 
               (isPointBetweenPoints(&tempPt, &coords21, &coords22))) {
                intVert.push_back(x);
                intVert.push_back(y);
                validity = true;
            }
        };

        intersectionResult result;
        result.isValid = validity;
        result.intersection = intVert;
        return result;
    }

    static inline bool isPointInsidePgon(Vertex& point, Polygon& pgon) {
        int intersectionCount = 0;
        vector<Vertex>* pgonVerts = &pgon.getVertices();
        vector<double> pointCoords = (*point.getCoordinates());
        for (int i = 0; i < pgon.getVertices().size(); i++) {
            Vertex currVert = (*pgonVerts)[i];
            Vertex nextVert = (i != pgonVerts->size() - 1) ? 
                    (*pgonVerts)[i + 1] : (*pgonVerts)[0];
            vector<double> coords1 = (*currVert.getCoordinates());
            vector<double> coords2 = (*nextVert.getCoordinates());
            Vertex extPoint{max(coords1[0], coords2[0]) * 2.0, pointCoords[1]};
            intersectionResult intRes = computeIntersection(&currVert, &nextVert, &point, &extPoint);
            if (intRes.isValid) {
                intersectionCount += 1;
            }
        }
        return intersectionCount % 2 == 1;
    };

    static inline Polygon pgonBoolean(Polygon& pgon1, Polygon& pgon2, char boolType) {
        Polygon retPgon;
        if (boolType == 'U' || boolType == 'S' || boolType == 'I') {
            vector<Vertex>* pgon1Vertices = &pgon1.getVertices();
            vector<Vertex>* pgon2Vertices = &pgon2.getVertices();
            for (int i = 0; i < pgon1Vertices->size(); i++) {
                Vertex currVert = (*pgon1Vertices)[i];
                Vertex nextVert = (i != pgon1Vertices->size() - 1) ? 
                    (*pgon1Vertices)[i + 1] : (*pgon1Vertices)[0];
                for (int j = 0; j < pgon2Vertices->size(); j++) {
                    vector<double> intersection;
                    Vertex currVert2 = (*pgon2Vertices)[j];
                    Vertex nextVert2 = (j != pgon2Vertices->size() - 1) ? 
                        (*pgon2Vertices)[j + 1] : (*pgon2Vertices)[0];
                    intersectionResult result = computeIntersection(&currVert, &nextVert, 
                                                        &currVert2, &nextVert2);
                    if (result.isValid) {
                        // perform desired boolean operation here
                        switch(boolType) {
                            case 'U':
                                // for the current intersection, determine whether the
                                // vertex before or after the point are inside or outside
                                // any polygon. If inside, then mark it for removal. If 
                                // outside, then add it to the new polygon at the correct
                                // location in the vector.
                            break;

                            case 'S':

                            break;

                            case 'I':

                            break;
                        }
                    }
                }
            }
        } else {
            // Invalid boolean type provided, terminate function.
        }
        return retPgon;
    }
    
    // Function that computes the intersection between to polygons, each having
    // any number of edges.
    static inline vector<vector<double>> computePgonIntersections(Polygon& pgon1, Polygon& pgon2) {
        vector<vector<double>> foundIntersections;
        vector<Vertex>* pgon1Vertices = &pgon1.getVertices();
        // using each edge of theW first polygon, and comparing with each
        // edge of the second polygon to determine intersections.
        for (int i = 0; i < pgon1Vertices->size(); i++) {
            Vertex currVert = (*pgon1Vertices)[i];
            Vertex nextVert = (i != pgon1Vertices->size() - 1) ? 
                (*pgon1Vertices)[i + 1] : (*pgon1Vertices)[0];
            vector<Vertex>* pgon2Vertices = &pgon2.getVertices();
            for (int j = 0; j < pgon2Vertices->size(); j++) {
                vector<double> intersection;
                Vertex currVert2 = (*pgon2Vertices)[j];
                Vertex nextVert2 = (j != pgon2Vertices->size() - 1) ? 
                    (*pgon2Vertices)[j + 1] : (*pgon2Vertices)[0];
                intersectionResult result = computeIntersection(&currVert, &nextVert, 
                                                    &currVert2, &nextVert2);
                if (result.isValid) {
                    foundIntersections.push_back(result.intersection);
                    cout << "Found intersection for vertex: " + to_string(j) + "\n";
                }
            }
        }
        return foundIntersections;
    }
}

#endif