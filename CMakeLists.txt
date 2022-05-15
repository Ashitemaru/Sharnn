cmake_minimum_required(VERSION 2.8.11)
project(SHA-RNN)

IF (NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Release)
ENDIF ()

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

INCLUDE_DIRECTORIES(include)

SET(SOURCES
        src/Bitset.hpp
        src/ByteStream.hpp
        src/ChaoticMap.hpp
        src/ChaoticSystem.hpp
        src/NonLinear.hpp
        src/PaddedStream.hpp
        src/RNN.hpp
        src/RNNHash.hpp
        src/SpongeFunction.hpp
        src/SpongeHash.hpp
        src/util.hpp)

ADD_EXECUTABLE(${PROJECT_NAME} main.cpp ${SOURCES})
ADD_EXECUTABLE(testbench src/testbench.cpp ${SOURCES})
