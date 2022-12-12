add_library(ftx ftx.cpp)
find_package(ftxui CONFIG REQUIRED)
target_link_libraries(ftx PRIVATE ftxui::dom ftxui::screen ftxui::component)

add_library(file_sequence file_sequence.cpp)