cmake_minimum_required(VERSION 3.10...3.30)
set(CMAKE_CUDA_COMPILER 		"C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v12.6/bin/nvcc.exe")
set(CUDAToolkit_ROOT 			"C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v12.6")
set(CMAKE_CUDA_ARCHITECTURES 	86)

# Add debug information
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi /Od /DEBUG")
set(CMAKE_CUDA_FLAGS_DEBUG "${CMAKE_CUDA_FLAGS_DEBUG} -G -g -lineinfo")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /DEBUG")
# Generate PDB files
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/pdb)

project(cuda_vector_add LANGUAGES CXX CUDA)																
set(CMAKE_CXX_STANDARD 17)																				
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Conditionally set options based on generator
if(CMAKE_GENERATOR MATCHES "Ninja")
    message(STATUS "Configuring for Ninja generator")

    # Ninja-specific settings (if any additional needed)
    # Generally, no special settings are required here since it's already working

elseif(CMAKE_GENERATOR MATCHES "Visual Studio")
    message(STATUS "Configuring for Visual Studio generator")
	string(REPLACE "\\" "/" CUDA_TOOLKIT_ROOT_CLEAN "${CUDAToolkit_ROOT}")
    string(REPLACE "\\" "/" CMAKE_CUDA_COMPILER_CLEAN "${CMAKE_CUDA_COMPILER}")
    
    set(CUDA_TOOLKIT_ROOT_DIR "${CUDA_TOOLKIT_ROOT_CLEAN}")
	set(CMAKE_CUDA_COMPILER "${CMAKE_CUDA_COMPILER_CLEAN}")
	include_directories("${CUDAToolkit_ROOT}/include")
    set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -ccbin \"C:/Program Files/Microsoft Visual Studio/2022/Professional/VC/Tools/MSVC/14.41.34120/bin/HostX64/x64\"")      
endif()

add_library(cuda_kernels STATIC vector_add.cu )
set_target_properties(cuda_kernels PROPERTIES CUDA_SEPARABLE_COMPILATION ON )

# if(CMAKE_GENERATOR MATCHES "Visual Studio")
    set_target_properties(cuda_kernels PROPERTIES 
			CUDA_ARCHITECTURES 86
			CUDA_SEPARABLE_COMPILATION ON
			CUDA_DEBUG ON
			COMPILE_FLAGS "-g -G"
	)
# endif()

add_executable(vector_add main.cpp )
target_link_libraries(vector_add PRIVATE cuda_kernels)	
# Export compile commands for better IDE integration
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)												

target_include_directories(cuda_kernels PRIVATE "${CUDAToolkit_ROOT}/include")									# Set Additional Include Directories for CUDA
target_include_directories(vector_add PRIVATE "${CUDAToolkit_ROOT}/include")

# Optional: Set VS specific properties when using Ninja
if(CMAKE_GENERATOR MATCHES "Ninja")
    set_property(TARGET vector_add PROPERTY
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
    
    # Generate solution files for VS even when using Ninja
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    set(CMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD 1)
endif()


# cmake .. -G Ninja  -DCMAKE_BUILD_TYPE=Debug    -DCUDA_TOOLKIT_ROOT_DIR="C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v12.6"  -DCMAKE_CUDA_COMPILER="C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v12.6/bin/nvcc.exe"
# cmake .. -G Ninja  -DCMAKE_BUILD_TYPE=Release  -DCUDA_TOOLKIT_ROOT_DIR="C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v12.6"  -DCMAKE_CUDA_COMPILER="C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v12.6/bin/nvcc.exe"
# and then 'ninja -j12'
# ######################### #########################  #########################  #########################  #########################  #########################  
# cmake .. -G "Visual Studio 17 2022" -A x64 -T host=x64 -DCMAKE_CUDA_COMPILER="C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v12.6/bin/nvcc.exe" -DCUDA_TOOLKIT_ROOT_DIR="C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v12.6"
# ######################### #########################  #########################  #########################  #########################  ######################### 
