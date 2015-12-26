# ARDroneCFS
Core Flight Software on the AR Drone.  This project requires Linux and assumes some basic knowledge of Linux.  

## Quickstart
- ./setup
- cd build
- make

## To setup your initial build environment
- Run ./setup

## To build 
The build structure is created by the cmake command in the ./setup script.  You should rerun cmake if you change the build structure (add files, change file names, move files, etc...) or if you change any of the CMakeLists.txt files.  You can just run make at the appropriate level if just change the contents of a source file.

This project contains 2 separate builds.
-  ARDrone:  This is the target build cross-compiled for the flight computer in the AR Drone.
-  SoftSim:  The same code as the ARDrone build, but compiled for your linux PC.  This will still work, provided you are connected to your AR Drone via wifi.  Your PC must remain connected to the AR Drone.  This is useful during debugging.  This is also be useful when the simulation is completed and added to the project.  

The build system is setup to allow you to build the entire project, or smaller pieces of the project depending which level in the /build directory you run the make command from:
- /build - Builds everything.  This is useful when creating the initial build for the first time.
- /softsim - Builds only the SoftSim code.
- /ardrone - Builds only the ARDrone target code.
- /&lt;softsim or ardrone&gt;/cfe - Builds only the Core Flight Executive.
- /&lt;softsim or ardrone&gt;/cfe/cfe-ut - Builds only the Core Flight Executive unit tests.
- /&lt;softsim or ardrone&gt;/cfe/osal/unit-tests - Builds only the OS Abstraction Layer unit tests.  Unit tests are contained in their respective subdirectory.  You can rebuild individual unit tests from there.
- /&lt;softsim or ardrone&gt;/apps - Builds only the applications.
- /&lt;softsim or ardrone&gt;/apps/&gt;app name> - Builds only the specified application.  This is particularly useful when you start creating your own custom application.
- /&lt;softsim or ardrone&gt;/apps/&gt;app name>/unit_test - Builds only the unit tests for the specified application.  This is also useful when you start creating your own custom application.

