add_library(note note.cpp)

add_library(notes notes.cpp)
target_link_libraries(notes note)


add_executable(note_test note_test.cpp)
target_link_libraries(note_test GTest::gtest_main note)

add_executable(notes_test notes_test.cpp)
target_link_libraries(notes_test GTest::gtest_main notes)

gtest_discover_tests(note_test notes_test)
