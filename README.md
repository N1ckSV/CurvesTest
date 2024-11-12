## CurvesTest library ##



# BUILDING #

Install folder is in project root directory by default.
Specify shared to link dynamic libs.

Windows + MinGW:
    In project directory (select config and shared):
    ```cmake . --preset windows-(debug|release)-mingw[-shared]```
    ```cmake --build --preset windows-(debug|release)-mingw[-shared]```
    If install folder not appeared in the root directory with need files:
    ```cmake --istall "./build/windows-(debug|release)-mingw[-shared]"```

Windows + MSVC:
    In project directory (select config and shared):
    ```cmake . --preset windows-msvc[-shared]```
    ```cmake --build --preset windows-(debug|release)-msvc[-shared]```
    If install folder not appeared in the root directory with need files:
    ```cmake --istall "./build/windows-msvc[-shared]" --config (Debug|Release)```

Linux + Ninja + GCC:
    In project directory (select config and shared):
    ```cmake . --preset linux-(debug|release)-ninja[-shared]```
    ```cmake --build --preset linux-(debug|release)-ninja[-shared]```
    If install folder not appeared in the root directory with need files:
    ```cmake --istall "./build/linux-(debug|release)-ninja[-shared]"```