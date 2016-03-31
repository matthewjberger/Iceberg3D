# Iceberg3D
Iceberg3D is a game engine that uses SDL2 and OpenGL.

## Downloading
Paste this into git bash on windows (use the 'insert' key to paste), or your terminal on linux:

>git clone https://github.com/matthewjberger/Iceberg3D --recursive && cd Iceberg3D && git submodule foreach git pull origin master

## Building
### Output
The output directory for both linux and windows builds is:

    Iceberg3D\Bin

### Linux

Assuming you're using ubuntu:

    cd Iceberg3D
    ./install_linux_dependencies.sh
    make -C Build

### Windows
Build the Visual Studio 2015 solution:

    Iceberg3D\Build\Visual Studio\Iceberg3D.sln

The dependencies are nuget packages (exept for the Bullet physics library) and will be downloaded when you rebuild the solution. 

