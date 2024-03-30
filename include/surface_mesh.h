#pragma once

#include <memory>
#include <unordered_map>
#include <CDT.h>

#include "hashable.h"
#include "mesh.h"

namespace objcdt::SurfaceMesh{

class SurfaceMesh {
public:
    SurfaceMesh(CADMesh::CADMesh&& _mesh) : mesh(_mesh), triMesh() {}
    CADMesh::CADMesh triangulationByCDT();
private:
    CADMesh::CADMesh mesh;
    CADMesh::CADMesh triMesh = {};
    std::unordered_map<CADMesh::HashableVertex, int, CADMesh::HashableVertexHash> hashableVertexToVertexId = {};
    std::unordered_map<int, CADMesh::Vertex> vertexIdToVertexHandle = {};

    void prepareVerticesInfo(CDT::Triangulation<double> &cdt,const CADMesh::Face& face);
    void prepareEdgesInfo(CDT::Triangulation<double> &cdt,const CADMesh::Face& face);
    void constructTriangulatedMesh(const CDT::Triangulation<double> &cdt);
};


}