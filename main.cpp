#include <spdlog/spdlog.h>
#include <string>
#include <CLI/CLI.hpp>


#include "mesh.h"
#include "surface_mesh.h"


int main(int argc, char **argv) {
    
    CLI::App app("CDT for OBJ files");

    std::string input;
    app.add_option("-i,--input", input,
                "The input model file (with a .obj extension).")
    ->required()
    ->check(CLI::ExistingFile);

    std::string output;
    app.add_option("-o,--output", output,
                "The output mesh file.")
    ->required();

    CLI11_PARSE(app, argc, argv)


    try {
        objcdt::CADMesh::remove_duplication(input);
        objcdt::CADMesh::CADMesh mesh = objcdt::CADMesh::read_mesh(input);
        objcdt::SurfaceMesh::SurfaceMesh surfaceMesh(mesh);

        // objcdt::CADMesh::CADMesh triMesh = surfaceMesh.triangulationVerticesOnly();
        objcdt::CADMesh::CADMesh triMesh = surfaceMesh.triangulationVerticesAndEdges();

        objcdt::CADMesh::write_mesh(triMesh,output);

        SPDLOG_INFO("Done.");
        return 0;
    } catch (std::exception &e) {
        SPDLOG_ERROR(e.what());
        return 1;
    }
}
