# CMakeLists.txt for project root

cmake_minimum_required( VERSION 3.1 )

project( bayes-peak-picker )

# Add custom CMake modules to our path.
set( CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake )

# Require C++11 using CMake variable available in CMake 3.1+.
set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

add_subdirectory( deps )

# Use custom CMake module to attempt to find FFTW on host system. Find
# package will create an interface library fftw.
find_package( FFTW )
if( FFTW_FOUND )
    # If FFTW is detected, present option in CMake configuration to use FFTW.
    option( EIGEN_FFTW "Use FFTW as backing implementation of Eigen::FFT \
instead of kissfft." OFF )
    if( EIGEN_FFTW )
        target_link_libraries( eigen INTERFACE fftw )
        target_compile_definitions( eigen INTERFACE EIGEN_FFTW_DEFAULT )
    endif()
endif()

add_subdirectory( src )
