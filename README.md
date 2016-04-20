# Iceberg3D ![Screenshot](http://imgur.com/BKjpnp1.png)

Iceberg3D is an OpenGL-based 3D Game Engine.

![Screenshot](http://imgur.com/fGLzSfE.jpg)

## Downloading and Building

First, clone the repo and its submodules:

    git clone --recursive https://github.com/matthewjberger/Iceberg3D
    
Then to build, use [CMake](https://cmake.org/):

    cd Iceberg3D
    mkdir Build
    cd Build
    cmake ..

###Note:
When building with Visual Studio, the **Visual C++ Redistributable for Visual Studio 2015**  must be installed. This can be found in the vcpp-redist folder of this repository:

    Iceberg3D/dependencies/vcpp-redist/vc_redist.x86.exe