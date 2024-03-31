#include <spdlog/spdlog.h>
#include <CDTUtils.h>
#include <Eigen/Dense>
#include <memory>
#include <vector>

#include "Eigen/src/Core/Matrix.h"
#include "hashable.h"
#include "surface_mesh.h"
#include "mesh.h"

namespace objcdt::SurfaceMesh{
    CADMesh::CADMesh SurfaceMesh::triangulationVerticesOnly() {
        SPDLOG_INFO("[SurfaceMesh] perform triangulation by CDT");
        
        for (const auto &face : mesh.faces()) {
            CDT::Triangulation<double> cdt;
            hashableVertexToVertexId.clear();
            vertexIdToVertexHandle.clear();
            prepareVerticesInfo(cdt,face);
            cdt.eraseSuperTriangle();
            constructTriangulatedMesh(cdt);
        }
        
        return triMesh;
    }

    CADMesh::CADMesh SurfaceMesh::triangulationVerticesAndEdges() {
        SPDLOG_INFO("[SurfaceMesh] perform triangulation by CDT");
        
        for (const auto &face : mesh.faces()) {
            CDT::Triangulation<double> cdt;
            hashableVertexToVertexId.clear();
            vertexIdToVertexHandle.clear();
            prepareVerticesInfo(cdt,face);
            prepareEdgesInfo(cdt,face);
            cdt.eraseOuterTrianglesAndHoles();
            constructTriangulatedMesh(cdt);
        }
        
        return triMesh;
    }


    void SurfaceMesh::prepareVerticesInfo(CDT::Triangulation<double> &cdt,const CADMesh::Face& face) {
        std::vector<CDT::V2d<double>> vertices;

        int idx = 0;
        for (const auto &vh: face.vertices()) {
            // construct vertices info
            Eigen::Vector3d v_3d = mesh.point(vh);
            // TODO: convert 3D -> 2D in a general way
            vertices.emplace_back(CDT::V2d<double>::make(v_3d.x(),v_3d.z()));
            // update map
            vertexIdToVertexHandle[idx] = vh;
            auto meshPtr = std::make_shared<CADMesh::CADMesh>(mesh);
            CADMesh::HashableVertex hashableVertex(vh,meshPtr);
            hashableVertexToVertexId[hashableVertex] = idx;
            idx++;
        }

        SPDLOG_INFO("[vertices]");
        for (const auto &v : vertices) {
            SPDLOG_INFO("({}, {})",v.x,v.y);
        }

        cdt.insertVertices(vertices);
        SPDLOG_INFO("[insertVertices done]");
    }


    void SurfaceMesh::prepareEdgesInfo(CDT::Triangulation<double> &cdt,const CADMesh::Face& face) {
        std::vector<CDT::Edge> edges;
        auto meshPtr = std::make_shared<CADMesh::CADMesh>(mesh);

        for (const auto &eh : face.edges()) {
            CADMesh::Vertex vh0 = eh.v0();
            CADMesh::Vertex vh1 = eh.v1();
            CADMesh::HashableVertex hashableVertex0 = CADMesh::HashableVertex(vh0,meshPtr);
            CADMesh::HashableVertex hashableVertex1 = CADMesh::HashableVertex(vh1,meshPtr);
            CDT::VertInd vh0_idx = hashableVertexToVertexId[hashableVertex0];
            CDT::VertInd vh1_idx = hashableVertexToVertexId[hashableVertex1];
            CDT::Edge edge(vh0_idx,vh1_idx);
            edges.emplace_back(edge);
        }

        cdt.insertEdges(edges);
        SPDLOG_INFO("[insertEdges done]");
    }


    void SurfaceMesh::constructTriangulatedMesh(const CDT::Triangulation<double> &cdt) {
        // add each triangle into triMesh
        for (const auto &triangle: cdt.triangles) {
            CDT::VertInd idx0 = triangle.vertices[0];
            CDT::VertInd idx1 = triangle.vertices[1];
            CDT::VertInd idx2 = triangle.vertices[2];
            Eigen::Vector3d p0 = mesh.point(vertexIdToVertexHandle[idx0]);
            Eigen::Vector3d p1 = mesh.point(vertexIdToVertexHandle[idx1]);
            Eigen::Vector3d p2 = mesh.point(vertexIdToVertexHandle[idx2]);

            // add vertex
            auto vh0 = triMesh.add_vertex(p0);
            auto vh1 = triMesh.add_vertex(p1);
            auto vh2 = triMesh.add_vertex(p2);
            // add face
            std::vector<CADMesh::Vertex> tri = {vh0, vh1, vh2};
            triMesh.add_face(tri);
        }
        SPDLOG_INFO("[constructTriMesh] done]");
    }

}