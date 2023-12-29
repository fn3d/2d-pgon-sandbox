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

        Vertex operator- (Vertex& vert1) {
            vector<double>* vert1Coords = vert1.getCoordinates();
            double x = this->coords[0] - (*vert1Coords)[0];
            double y = this->coords[1] - (*vert1Coords)[1];
            Vertex newVert{x, y};
            return newVert;
        }
        
        Vertex(double _x, double _y) {
            coords[0] = _x;
            coords[1] = _y;
        }

        ~Vertex() {};
};

class Polygon {
    private:
        vector<Vertex> pgonVertices;

    public:
        Polygon() {};
        ~Polygon() {};

        int getVertexCount() const {
            return pgonVertices.size();
        }

        vector<Vertex>& getVertices() {
            return pgonVertices;
        }

        // Addition of vertices assumes that vertex is the
        // next logical connecting vertex in the polygon.
        void addVertex(double _x, double _y) {
            Vertex newVert = Vertex(_x, _y);
            pgonVertices.push_back(newVert);
        }

        void addVertexAtIndex(double _x, double _y, int index) {

        }
};

#endif