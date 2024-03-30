#pragma once

#include <functional>
#include <memory>

#include "mesh.h"

namespace objcdt::CADMesh {
    class HashableVertex{
    public:
        Vertex vertexHandle;
        const std::shared_ptr<CADMesh> &meshPtr;

        explicit HashableVertex(const Vertex& _vertexHandle,const std::shared_ptr<CADMesh>& _meshPtr) : vertexHandle(_vertexHandle), meshPtr(_meshPtr) {}
        bool operator==(const HashableVertex& other) const {
            return this->vertexHandle == other.vertexHandle;
        }
    };

    class HashableVertexHash {
    public:std::size_t operator()(const HashableVertex& hv) const {
            auto mesh = *hv.meshPtr;
            Eigen::Vector3d v_3d = mesh.point(hv.vertexHandle);
            std::hash<double> vertexHandleHasher;
            std::size_t hash = vertexHandleHasher(v_3d.x() + v_3d.y() + v_3d.z());
            return hash;
        }
    };
}