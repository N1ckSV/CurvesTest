# CurvesTest library #

Nikita Kurchev <karnik20012014@gmail.com>

## Requirements ##

    CMake
    MSVC or GCC compiler with C++11 and OpenMP support
    
## BUILDING ##
      
- Install folder is in project root directory by default.
- Specify shared to link dynamic libs.
- On Linux, it is better to run the installed executable file due to RPATH.

### Windows + MinGW + GCC ###
* In project directory (select config and shared):
* ```cmake . --preset windows-(debug|release)-mingw[-shared]```
* ```cmake --build --preset windows-(debug|release)-mingw[-shared]```
* If the install folder does not appear in the root directory with the necessary files:
* ```cmake --istall "./build/windows-(debug|release)-mingw[-shared]"```

### Windows + MSVC ###
* In project directory (select config and shared):
* ```cmake . --preset windows-msvc[-shared]```
* ```cmake --build --preset windows-(debug|release)-msvc[-shared]```
* If the install folder does not appear in the root directory with the necessary files:
* ```cmake --istall "./build/windows-msvc[-shared]" --config (Debug|Release)```

### Linux + Ninja + GCC ###
* In project directory (select config and shared):
* ```cmake . --preset linux-(debug|release)-ninja[-shared]```
* ```cmake --build --preset linux-(debug|release)-ninja[-shared]```
* If the install folder does not appear in the root directory with the necessary files:
* ```cmake --istall "./build/linux-(debug|release)-ninja[-shared]"```
