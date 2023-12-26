#include <vector>

using namespace std;

#ifndef POLYGON_H
#define POLYGON_H

class Vertex {
    private:
        vector<double> coords{0, 0};

    public:
        vector<double>* getCoordinates() {
            return &coords;
        }

        void setCoordinates(double _x, double _y) {
            coords[0] = _x;
            coords[1] = _y;
        }

        Vertex() {};
        Vertex(double _x, double _y) {
            coords[0] = _x;
            coords[1] = _y;
        }
        ~Vertex() {};
};

class Polygon {
    private:
        vector<Vertex> ngonVertices;

    public:
        Polygon() {};
        ~Polygon() {};

        int getVertexCount() const {
            return ngonVertices.size();
        }

        vector<Vertex>& getVertices() {
            return ngonVertices;
        }

        // Addition of vertices assumes that vertex is the
        // next logical connecting vertex in the polygon.
        void addVertex(double _x, double _y) {
            Vertex newVert = Vertex(_x, _y);
            ngonVertices.push_back(newVert);
        }

        void addVertexAtIndex(double _x, double _y, int index) {

        }
};

#endif