# Iceberg3D
Iceberg3D is a game engine that uses SDL2 and OpenGL.

## Downloading and Building
### Windows
Paste this into git bash on windows (use the 'insert' key to paste):

    git clone --recursive https://github.com/matthewjberger/Iceberg3D
    cd Iceberg3D
    git submodule foreach git pull origin master
    
Then build the Visual Studio 2015 solution:

    Iceberg3D\Build\Visual Studio\Iceberg3D.sln

The dependencies are nuget packages (exept for the Bullet physics library) and will be downloaded when you build the solution.
    
### Linux
Paste this into your linux terminal:

    git clone https://github.com/matthewjberger/Iceberg3D

Then to build (assuming you're using ubuntu):

    cd Iceberg3D
    ./install_linux_dependencies.sh
    make -C Build
    
### Output
The output directory for both linux and windows builds is:

    Iceberg3D\Bin
