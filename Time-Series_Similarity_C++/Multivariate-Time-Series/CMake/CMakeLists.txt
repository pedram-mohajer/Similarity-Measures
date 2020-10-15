cmake_minimum_required("VERSION" 3.0.0)

project("SimilarityMeasure")


set(CMAKE_CXX_FLAGS "-std=c++11")

include_directories(include)


file(GLOB SOURCES "src/*.cpp")

add_executable(SimilarityMeasure ${SOURCES})


set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.50 REQUIRED COMPONENTS filesystem)
message(STATUS "Boost version: ${Boost_VERSION}")

# This is needed if your Boost version is newer than your CMake version
# or if you have an old version of CMake (<3.5)

if(NOT TARGET Boost::filesystem)
    add_library(Boost::filesystem IMPORTED INTERFACE)
    set_property(TARGET Boost::filesystem PROPERTY
        INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
    set_property(TARGET Boost::filesystem PROPERTY
        INTERFACE_LINK_LIBRARIES ${Boost_LIBRARIES})
endif()


target_link_libraries(SimilarityMeasure PUBLIC Boost::filesystem)






