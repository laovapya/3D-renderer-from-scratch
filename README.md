Requirements:

CMake
Git
vcpkg
c++ compiler





Installation:

git clone -b main --recurse-submodules https://github.com/laovapya/3D-renderer-from-scratch.git

cd 3D-renderer-from-scratch


./vcpkg install glfw3 glad



run from a terminal where vcpkg’s bin is in PATH


cmake -B build -DCMAKE_TOOLCHAIN_FILE=[vcpkg]/scripts/buildsystems/vcpkg.cmake

cmake --build build
