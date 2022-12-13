add_library(ftx ftx.cpp)
find_package(ftxui CONFIG REQUIRED)
find_package(matplot++ CONFIG REQUIRED)
target_link_libraries(ftx PRIVATE ftxui::dom ftxui::screen ftxui::component Matplot++::cimg std::filesystem Matplot++::matplot Matplot++::nodesoup)

add_library(file_sequence file_sequence.cpp)