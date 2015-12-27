# ARDroneCFS
Core Flight Software on the AR Drone.  This project requires Linux and assumes some basic knowledge of Linux.  

## Quickstart
- Add the following entry to your /etc/exports file:  /srv/nfs        192.168.1.1(rw,sync)
- Restart your nfs server daemon
- ./setup
- Connect to AR Drone wifi
- Determine the last octet of your IP address from the AR Drone, i.e. ifconfig.  This is usually 2.
- telnet 192.168.1.1
- nfs.sh 2  # The "2" should be whatever your last octet is.
- Open another shell
- cd config/ardrone/build
- make
- Switch back to the shell logged into the AR Drone (192.168.1.1)
- cd /mnt/nfs
- cf/apps/core-bin --reset PO 1

## To setup your initial build environment
- Run ./setup
- Create directory "/srv/nfs"
- Export the /srv/nfs directory to 192.168.1.1 via NFS with read and write access.

## To build 
The build structure is created by the cmake command in the ./setup script.  You should rerun cmake if you change the build structure (add files, change file names, move files, etc...) or if you change any of the CMakeLists.txt files.  You can just run make at the appropriate level if just change the contents of a source file.

This project contains 2 separate builds.
-  config/ardrone:  This is the target build cross-compiled for the flight computer in the AR Drone.
-  config/softsim:  The same code as the ARDrone build, but compiled for your linux PC.  This will still work, provided you are connected to your AR Drone via wifi.  Your PC must remain connected to the AR Drone.  This is useful during debugging.  This is also be useful when the simulation is completed and added to the project.  

The build system is setup to allow you to build the entire build, or smaller pieces of the project depending which level in the config/<ardrone or softsim>/build directory you run the make command from:
- config/&lt;softsim or ardrone&gt;/build - Builds flight code and unit tests.  This is useful when creating the initial build for the first time.
- config/&lt;softsim or ardrone&gt;/build/cfe - Builds only the Core Flight Executive.
- config/&lt;softsim or ardrone&gt;/build/cfe/cfe-ut - Builds only the Core Flight Executive unit tests.
- config/&lt;softsim or ardrone&gt;/build/cfe/osal/unit-tests - Builds only the OS Abstraction Layer unit tests.  Unit tests are contained in their respective subdirectory.  You can rebuild individual unit tests from there.
- config/&lt;softsim or ardrone&gt;/build/apps - Builds only the applications.
- config/&lt;softsim or ardrone&gt;/build/apps/&lt;app name&gt; - Builds only the specified application.  This is particularly useful when you start creating your own custom application.
- config/&lt;softsim or ardrone&gt;/build/apps/&lt;app name&gt;/unit_test - Builds only the unit tests for the specified application.  This is also useful when you start creating your own custom application.

