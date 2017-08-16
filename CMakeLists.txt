cmake_minimum_required (VERSION 2.8.11)

set (PROJ_NAME cs325-group)

project (${PROJ_NAME})

# Add include folders
include_directories("${PROJECT_SOURCE_DIR}/include")

set(PROJECT_SRCS
  ${PROJECT_SOURCE_DIR}/src/city.cpp
  ${PROJECT_SOURCE_DIR}/src/tour.cpp
  ${PROJECT_SOURCE_DIR}/src/tourGA.cpp
  ${PROJECT_SOURCE_DIR}/src/tourPop.cpp
  ${PROJECT_SOURCE_DIR}/src/tourSet.cpp
  ${PROJECT_SOURCE_DIR}/src/TSP.cpp
)

# Compilier settings
set(CMAKE_CXX_FLAGS "-O0 -lm -fopenmp")

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I/usr/local/include -L/usr/local/lib")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/usr/local/lib")

#add_definitions(-DNUMT=${NUMT})
#add_definitions(-DNUMNODES=${NUMNODES})

add_executable(${PROJ_NAME} ${PLATFORM_SRCS} ${PROJECT_SRCS})
