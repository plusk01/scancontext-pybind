#include <sstream>

#include <pybind11/eigen.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "scancontext/Scancontext.h"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;

PYBIND11_MODULE(pyscancontext, m) {
    m.doc() = "Scan Context for LiDAR place recognition";
    m.attr("__version__") = PROJECT_VERSION;

    py::class_<SCManager::Params>(m, "Params")
        .def(py::init<>())
        .def("__repr__", [](const SCManager::Params& params) {
            std::ostringstream repr;
            repr << "<SCManager Params>";
            return repr.str();
        })
        .def_readwrite("lidar_height", &SCManager::Params::lidar_height)
        .def_readwrite("Nr", &SCManager::Params::Nr)
        .def_readwrite("Ns", &SCManager::Params::Ns)
        .def_readwrite("max_radius", &SCManager::Params::max_radius)
        .def_readwrite("num_exclude_recent", &SCManager::Params::num_exclude_recent)
        .def_readwrite("num_candidates_from_tree", &SCManager::Params::num_candidates_from_tree)
        .def_readwrite("search_ratio", &SCManager::Params::search_ratio)
        .def_readwrite("tree_making_period", &SCManager::Params::tree_making_period);

    py::class_<SCManager>(m, "SCManager")
        .def(py::init<const SCManager::Params&>())
        .def("print_parameters", &SCManager::printParameters, py::return_value_policy::copy)
        .def("scd_distance", &SCManager::distanceBtnScanContext, py::return_value_policy::copy)
        .def("make_scancontext", &SCManager::makeScancontext, py::return_value_policy::copy)
        .def("construct_tree", &SCManager::constructTree, py::return_value_policy::copy)
        .def("add_scancontext", &SCManager::saveScancontextAndKeys, py::return_value_policy::copy)
        .def("add_node", &SCManager::makeAndSaveScancontextAndKeys, py::return_value_policy::copy)
        .def("detect_loop", &SCManager::detectLoopClosureID, py::return_value_policy::copy);
}
