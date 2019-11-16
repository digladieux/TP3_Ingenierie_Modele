cmake_minimum_required(VERSION 3.13)

project(TP3_Ingenierie_Model)

set(CMAKE_CXX_FLAGS "-pthread -O2 -msse2 -fpermissive")

set(HEADERS
    header/generation_string.hpp
    header/status_mt.hpp
    header/monte_carlo.hpp
)

set(SOURCES
    src/generation_string.cpp
    src/status_mt.cpp
    src/monte_carlo.cpp

)

set(CMAKE_CXX_CPPCHECK "cppcheck")
add_custom_target(
        cppcheck
        COMMAND /usr/bin/cppcheck
        --enable=warning,performance,portability,information,missingInclude
        --std=c++17
        --library=qt.cfg
        --template="[{severity}][{id}] {message} {callstack} \(On {file}:{line}\)"
        --verbose
        --quiet
        ${ALL_SOURCE_FILES}
)
include_directories(Random/include)
link_directories(Random/lib)

add_executable(question1 main/test.cc ${SOURCES} ${HEADERS})
add_executable(subject main/main_subject.cpp ${SOURCES} ${HEADERS})

target_compile_features(question1 PUBLIC cxx_std_17)
target_compile_features(subject PUBLIC cxx_std_17)

target_link_libraries(question1 libCLHEP-Random-2.1.0.0.a)
target_link_libraries(subject libCLHEP-Random-2.1.0.0.a)


