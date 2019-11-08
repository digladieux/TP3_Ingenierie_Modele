cmake_minimum_required(VERSION 3.13)

project(TP3)

set(SOURCES
#    vecteur03.hpp
)

include_directories(./Random/include)


add_executable(exe testrand.cc ${SOURCES})
add_executable(test testRandom.cc ${SOURCES})

LINK_DIRECTORIES(../Random/lib/)
TARGET_LINK_LIBRARIES(exe -L ../Random/lib/libCLHEP-Random-2.1.0.0)
TARGET_LINK_LIBRARIES(test -L ../Random/lib/libCLHEP-Random-2.1.0.0)

set(CMAKE_CXX_FLAGS "-msse2 -fpermissive")

target_compile_features(exe PUBLIC cxx_std_17)
target_compile_features(test PUBLIC cxx_std_17)



