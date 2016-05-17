# Iceberg3D ![Screenshot](http://imgur.com/BKjpnp1.png) [![Semver](http://img.shields.io/SemVer/0.1.0.png)](http://semver.org/spec/v0.1.0.html) [![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](https://github.com/matthewjberger/Iceberg3D/issues) [![HitCount](https://hitt.herokuapp.com/matthewjberger/Iceberg3D.svg)](https://github.com/matthewjberger/iceberg3D) [![Join the chat at https://gitter.im/matthewjberger/Iceberg3D](https://badges.gitter.im/matthewjberger/Iceberg3D.svg)](https://gitter.im/matthewjberger/Iceberg3D?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

Iceberg3D is an OpenGL based 3D Game Engine.

![Screenshot](http://imgur.com/fGLzSfE.jpg)

## Downloading and Building

First, clone the repo and its submodules:

    git clone --recursive https://github.com/matthewjberger/Iceberg3D
    
Then to build, use [CMake](https://cmake.org/):

    cd Iceberg3D
    mkdir Build
    cd Build
    cmake ..

######Note: When building with Visual Studio, the [Visual C++ Redistributable for Visual Studio 2015](https://www.microsoft.com/en-us/download/details.aspx?id=48145) must be installed. 

## Demos
To build the demos, enable the cmake option:

    ICEBERG_BUILD_DEMOS
    
If using Visual Studio to build the demos, make sure that you set the working directory per demo as follows:

    Right-click on the chosen demo -> Properties -> Debugging -> Working Directory
    
and change to:
    
    $(TargetDir)

## Sandbox

Additionally, there is a bare bones sandbox application that can be used for testing features. To build the sandbox, enable the cmake option:

    ICEBERG_BUILD_SANDBOX
