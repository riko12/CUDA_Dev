cmake_minimum_required(VERSION 3.10)

# Force x64 architecture
if(MSVC)
    set(CMAKE_GENERATOR_PLATFORM x64)
endif()

# Set CUDA paths correctly
set(CUDA_TOOLKIT_ROOT "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v12.6")
set(CMAKE_CUDA_COMPILER "${CUDA_TOOLKIT_ROOT}/bin/nvcc.exe")

# Clear and set correct environment variables
set(ENV{CUDA_PATH} "${CUDA_TOOLKIT_ROOT}")
set(ENV{CUDA_PATH_V12_6} "${CUDA_TOOLKIT_ROOT}")  # Don't include multiple paths
set(ENV{CUDA_TOOLKIT_ROOT_DIR} "${CUDA_TOOLKIT_ROOT}")

# Set Visual Studio CUDA settings
set(CMAKE_VS_PLATFORM_TOOLSET_CUDA "12.6")
set(CMAKE_VS_PLATFORM_TOOLSET_CUDA_CUSTOM_DIR "${CUDA_TOOLKIT_ROOT}")

# Declare project
project(cuda_vector_add LANGUAGES CXX CUDA)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_ARCHITECTURES 86)

# Force Visual Studio to use x64
if(MSVC)
    set(CMAKE_VS_PLATFORM_NAME "x64")
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

# Create CUDA library
add_library(cuda_kernels STATIC
    vector_add.cu
)

# Configure CUDA library
set_target_properties(cuda_kernels PROPERTIES
    CUDA_SEPARABLE_COMPILATION ON
    POSITION_INDEPENDENT_CODE ON
)

# Create main executable
add_executable(vector_add
    main.cpp
)

# Link libraries
target_link_libraries(vector_add PRIVATE cuda_kernels)