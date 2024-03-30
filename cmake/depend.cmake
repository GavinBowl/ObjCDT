CPMAddPackage(
        NAME "Eigen3"
        GIT_REPOSITORY "https://github.com/hexagon-geo-surv/eigen.git"
        GIT_TAG "3.4.0"
        OPTIONS
        "BUILD_TESTING OFF"
        "EIGEN_BUILD_DOC OFF"
        "EIGEN_LEAVE_TEST_IN_ALL_TARGET OFF"
        "EIGEN_BUILD_PKGCONFIG OFF"
)

CPMAddPackage(
        NAME "cli11"
        GIT_REPOSITORY "https://github.com/CLIUtils/CLI11"
        GIT_TAG "v2.1.2"
)

CPMAddPackage(
        NAME "fmt"
        GIT_REPOSITORY "https://github.com/fmtlib/fmt.git"
        GIT_TAG "9.1.0"
)

CPMAddPackage(
        NAME "spdlog"
        GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
        GIT_TAG "v1.11.0"
)

CPMAddPackage(
        NAME "OpenMesh"
        GIT_REPOSITORY "https://gitlab.vci.rwth-aachen.de:9000/OpenMesh/OpenMesh.git"
        GIT_TAG "OpenMesh-9.0"
)

CPMAddPackage(
        NAME "CDT"
        GIT_REPOSITORY "https://github.com/artem-ogre/CDT.git"
        GIT_TAG "1.4.0"
)