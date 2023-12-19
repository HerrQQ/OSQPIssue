
cmake_minimum_required(VERSION 3.14.1)
project(project_osqp)
set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( THREADS_PREFER_PTHREAD_FLAG ON )

function(include_sub_directories_recursively root_dir)
    if (IS_DIRECTORY ${root_dir})
        include_directories(${root_dir})
        file(GLOB children RELATIVE ${root_dir} ${root_dir}/*)
        foreach(child ${children})
            if (IS_DIRECTORY ${root_dir}/${child})
                include_sub_directories_recursively(${root_dir}/${child})
            endif()
        endforeach()
    endif()
endfunction()

function(aux_source_directory_recursively root_dir var_name)
    if(IS_DIRECTORY ${root_dir})
        aux_source_directory(${root_dir} TMP_SRC_LIST)
        set(${var_name} ${${var_name}} ${TMP_SRC_LIST} PARENT_SCOPE)
        file(GLOB children RELATIVE ${root_dir} ${root_dir}/*)
        foreach(child ${children})
            if(IS_DIRECTORY ${root_dir}/${child})
                aux_source_directory_recursively(${root_dir}/${child} ${var_name}) 
            endif()
        endforeach()
    endif()
endfunction()


find_package(glog REQUIRED)
find_package(Eigen3 REQUIRED)
#find_package(osqp REQUIRED )
find_package(OsqpEigen REQUIRED)

#set(GLOG_LIBRARIES "/usr/local/lib/libglog.so")

# message(STATUS "GLOG_INCLUDE_DIRS: ${GLOG_INCLUDE_DIR}")
# message(STATUS "GLOG_LIBRARIES: ${GLOG_LIBRARIES}")
# message(STATUS "EIGEN3_INCLUDE_DIR: ${EIGEN3_INCLUDE_DIR}")
# message(STATUS "EIGEN3_LIBRARIES: ${EIGEN3_LIBRARIES}")
# message(STATUS "osqp_INCLUDE_DIR: ${osqp_INCLUDE_DIR}")
# message(STATUS "osqp_LIBRARIES: ${osqp_LIBRARIES}")

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_LIST)
 aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/. SRC_LIST)

#aux_source_directory_recursively(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)
include_sub_directories_recursively(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_sub_directories_recursively(${CMAKE_CURRENT_SOURCE_DIR}/src)

##############################debug start##############################
get_property(include_dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)

foreach(dir ${include_dirs})
    message("Include directory: ${dir}")
endforeach()

message("Source files:")
foreach(file IN LISTS SRC_LIST)
    message("  ${file}")
endforeach()
#################################debug end####################################

include_directories(${GLOG_INCLUDE_DIRS})
include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs)
add_executable(${PROJECT_NAME} ${SRC_LIST})
#add_library(${PROJECT_NAME} STATIC ${SRC_LIST}) # temp use 
target_include_directories(${PROJECT_NAME} PRIVATE ${GLOG_INCLUDE_DIRS})
#target_include_directories(${PROJECT_NAME} PRIVATE ${OSQP_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} OsqpEigen::OsqpEigen)
target_link_libraries(${PROJECT_NAME} PRIVATE ${GLOG_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${EIGEN3_LIBRARIES})
#target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs/yaml-cpp/libyaml-cpp.a)
#target_link_libraries(${PROJECT_NAME} PRIVATE osqp::osqp)
#####################################unit test ###################################
# add_executable(unit_test_pathFW ${SRC_LIST}) 
# target_link_libraries( unit_test_pathFW
#                         ${GLOG_LIBRARIES}
#                         # ${CMAKE_CURRENT_SOURCE_DIR}/libs/yaml-cpp/libyaml-cpp.a
#                         ${CMAKE_CURRENT_SOURCE_DIR}/libs/yaml-cpp/libyaml-cpp.a
#                         # yaml-cpp
#                         )
#####################################unit test end#################################





