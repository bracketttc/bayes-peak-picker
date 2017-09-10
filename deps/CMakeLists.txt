# CMakeLists.txt for deps folder

# Create a CMake INTERFACE library for Eigen.
# All targets requiring access to Eigen should "link" against this library
# instead of including the eigen directory.
add_library( eigen INTERFACE )
target_include_directories( eigen INTERFACE eigen )
