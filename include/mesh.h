#pragma once

#include <Eigen/Dense>
#include <memory>
#include <string>

#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Geometry/EigenVectorT.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>

namespace objcdt::CADMesh {

    struct EigenTraits : public OpenMesh::DefaultTraits {
        using Point  = Eigen::Vector3d;
        using Normal = Eigen::Vector3d;
    };

    using Vertex   = OpenMesh::SmartVertexHandle;
    using Edge     = OpenMesh::SmartEdgeHandle;
    using HalfEdge = OpenMesh::SmartHalfedgeHandle;
    using Face     = OpenMesh::SmartFaceHandle;
    using Point    = OpenMesh::PolyMesh_ArrayKernelT<EigenTraits>::Point;

    using CADMesh = OpenMesh::PolyMesh_ArrayKernelT<EigenTraits>;


    CADMesh read_mesh(const std::string &fileName);

    void write_mesh(const CADMesh &mesh, const std::string &fileName);

    void remove_duplication(const std::string &fileName);
}