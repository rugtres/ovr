# OVR 
![example workflow](https://github.com/rugtres/ovr/actions/workflows/build.yml/badge.svg)

Oncolytic Virus Resistance simulation

This GitHub page contains all code to compile OVR. There are three flavors available: GUI, Console and Test, each residing in their respective folders. The GUI folder contains the code specific to compile the GUI version, the Console folder contains the code to compile a terminal only (no GUI) version, that reads parameters from a parameter (ini) file. Lastly, the Test folder uses Catch2 to test several properties of the model and verify that the code runs correctly. 

For those not interested in compiling the code yourself, the folder Release contains a Windows installer that creates a folder on your computer containing OVR.exe, which should run independently. 



Branch|Code Coverage
---|---
master|[![codecov.io](https://codecov.io/github/rugtres/ovr/coverage.svg?branch=master)](https://codecov.io/github/rugtres/ovr/coverage.svg?branch=master)


![](https://github.com/rugtres/ovr/blob/main/Screenshots/GUI_tabbed.png)
