# Iceberg3D ![Screenshot](http://imgur.com/6rQzfub.png)

Iceberg3D is an OpenGL-based 3D Game Engine.

![Screenshot](http://imgur.com/fGLzSfE.jpg)

## Downloading and Building

First, clone the repo and its submodules:

    git clone --recursive https://github.com/matthewjberger/Iceberg3D
    cd Iceberg3D
    git submodule init && git submodule update
    
### CMake
Then to build, use [CMake](https://cmake.org/):

    cd Iceberg3D
    mkdir Build
    cd Build
    cmake ..
    cmake ..
