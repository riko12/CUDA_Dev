cmake .. -G Ninja  -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCUDA_TOOLKIT_ROOT_DIR="C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v12.6"  -DCMAKE_CUDA_COMPILER="C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v12.6/bin/nvcc.exe" && ninja -j12

C:\Development\dlib\ARik_Dev\ARik_Dev\examples\ARik_AlbinaTransformer_EveryDW\cuda_app_lrn\build>cmake .. -G Ninja  -DCMAKE_BUILD_TYPE=Debug  -DCUDA_TOOLKIT_ROOT_DIR="C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v12.6"  -DCMAKE_CUDA_COMPILER="C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v12.6/bin/nvcc.exe" && ninja -j12
-- The CXX compiler identification is MSVC 19.41.34123.0
-- The CUDA compiler identification is NVIDIA 12.6.77 with host compiler MSVC 19.41.34123.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: C:/Program Files/Microsoft Visual Studio/2022/Professional/VC/Tools/MSVC/14.41.34120/bin/Hostx64/x64/cl.exe - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Detecting CUDA compiler ABI info
-- Detecting CUDA compiler ABI info - done
-- Check for working CUDA compiler: C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v12.6/bin/nvcc.exe - skipped
-- Detecting CUDA compile features
-- Detecting CUDA compile features - done
-- Configuring for Ninja generator
-- Configuring done (17.0s)
-- Generating done (0.1s)
CMake Warning:
  Manually-specified variables were not used by the project:

    CUDA_TOOLKIT_ROOT_DIR


-- Build files have been written to: C:/Development/dlib/ARik_Dev/ARik_Dev/examples/ARik_AlbinaTransformer_EveryDW/cuda_app_lrn/build
[2/5] Building CUDA object CMakeFiles\cuda_kernels.dir\vector_add.cu.obj
ptxas warning : Conflicting options --device-debug and --generate-line-info specified, ignoring --generate-line-info option
nvcc warning : '--device-debug (-G)' overrides '--generate-line-info (-lineinfo)'
vector_add.cu
tmpxft_00005808_00000000-10_vector_add.cudafe1.cpp
[4/5] Linking CXX executable CMakeFiles\vector_add.dir\cmake_device_link.obj
nvcc warning : '--device-debug (-G)' overrides '--generate-line-info (-lineinfo)'
main.cpp.obj
cuda_kernels.lib
cudadevrt.lib
cudart_static.lib
kernel32.lib
user32.lib
gdi32.lib
winspool.lib
shell32.lib
ole32.lib
oleaut32.lib
uuid.lib
comdlg32.lib
advapi32.lib
[5/5] Linking CXX executable vector_add.exe

C:\Development\dlib\ARik_Dev\ARik_Dev\examples\ARik_AlbinaTransformer_EveryDW\cuda_app_lrn\build>