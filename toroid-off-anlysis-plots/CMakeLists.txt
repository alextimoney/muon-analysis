# Set up the project.
cmake_minimum_required( VERSION 3.10 )
set  (CMAKE_CXX_STANDARD 17)
project( "TreeAnalyzers" VERSION 3.1.2 LANGUAGES CXX )
set    ( CMAKE_BUILD_TYPE RELEASE )
set( CMAKE_CXX_FLAGS "-march=core-avx2" )
# Add the project's modules directory to CMAKE_MODULE_PATH:
list( INSERT CMAKE_MODULE_PATH 0 ${CMAKE_CURRENT_SOURCE_DIR}/modules )


# Project's dependencies.
find_package( ROOT REQUIRED )
include_directories(${ROOT_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/TreeAnalyzers)

file(GLOB sources ${PROJECT_SOURCE_DIR}/Root/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/TreeAnalyzers/*.h)

add_library(TreeAnalyzers ${sources} ${headers})
target_link_libraries(TreeAnalyzers PUBLIC ${ROOT_LIBRARIES} )

#----------------------------------------------------------------------------
#


set(OUTPUT bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${OUTPUT})

foreach( exec analyzeTree)
  add_executable( ${exec} ${PROJECT_SOURCE_DIR}/src/${exec}.cpp )
  target_link_libraries( ${exec} TreeAnalyzers)
endforeach()

#----------------------------------------------------------------------------
# Link all needed libraries

install( TARGETS analyzeTree
   EXPORT ${PROJECT_NAME}-export
   RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
   COMPONENT Runtime )

