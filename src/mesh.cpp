#include <functional>
#include <spdlog/spdlog.h>
#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "mesh.h"

namespace objcdt::CADMesh {

    CADMesh read_mesh(const std::string &fileName) {
        SPDLOG_INFO("Reading mesh from {} ...", fileName);

        CADMesh mesh;
        if (!OpenMesh::IO::read_mesh(mesh, fileName)) {
            throw std::runtime_error("Failed to read mesh from " + fileName);
        }

        SPDLOG_INFO("n_faces: {}", mesh.n_faces());

        return mesh;
    }

    void write_mesh(const CADMesh &mesh, const std::string &fileName) {
        SPDLOG_INFO("Writing mesh to {} ...", fileName);
        if (!OpenMesh::IO::write_mesh(mesh, fileName)) {
            throw std::runtime_error("Failed to write mesh to " + fileName);
        }
    }

    struct Vtx {
        double x, y, z;
        bool operator==(const Vtx& other) const {
            return (x-other.x)<1e-3 && (y-other.y)<1e-3 && (z-other.z)<1e-3;
        }
    };

    
}


namespace std {
    template <>
    struct hash<objcdt::CADMesh::Vtx> {
        size_t operator()(const objcdt::CADMesh::Vtx& v) const {
            return hash<double>()(v.x) ^ hash<double>()(v.y) ^ hash<double>()(v.z);
        }
    };
}


namespace objcdt::CADMesh {

    void remove_duplication(const std::string &fileName) {
        SPDLOG_INFO("Removing duplication in {} ...", fileName);

        std::unordered_map<Vtx,int> uniqueMap;
        std::vector<Vtx> uniqueVertices;
        std::unordered_map<int, int> oldIdToNewId;
        std::vector<std::vector<int>> faces;
        std::vector<Vtx> vertices;

        std::ifstream file(fileName);
        std::string line;


        // prepare duplication free v and f
        int oldIdx = 1;
        int newIdx = 1;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            char prefix;
            iss >> prefix;

            if (prefix == 'v') {
                Vtx v;
                iss >> v.x >> v.y >> v.z;
                // already in, duplicate!
                auto it = uniqueMap.find(v);
                if (it != uniqueMap.end()) {
                    oldIdToNewId[oldIdx] = it->second;
                    oldIdx++;
                } else {
                    vertices.emplace_back(v);
                    uniqueMap[v] = newIdx;
                    oldIdToNewId[oldIdx] = newIdx;
                    oldIdx++;
                    newIdx++;
                }
            } else if (prefix == 'f') {
                int vtxId;
                std::vector<int> face;
                while (iss >> vtxId) {
                    face.emplace_back(oldIdToNewId[vtxId]);
                }
                faces.emplace_back(face);
            } else {
                continue;
            }
        }

        // write back
        file.close();
        // clear old file
        std::ofstream outFile(fileName, std::ios::trunc);
        if (!outFile) {
            SPDLOG_ERROR("Failed to open file for writing: {}",fileName);
            return;
        }

        outFile << "# " << vertices.size() << " vertices, " << faces.size() << " faces" << std::endl;

        // write v
        for (const auto& v : vertices) {
            outFile << "v " << v.x << " " << v.y << " " << v.z << std::endl;
        }

        // write f
        for (const auto& face : faces) {
            outFile << "f";
            for (int vtxId : face) {
                outFile << " " << vtxId;
            }
            outFile << std::endl;
        }

        outFile.close();
    }

}