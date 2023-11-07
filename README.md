Development of the game Snake++ using C, C++ and SDK2 for the Software Engineering course as part of our studies.

# Compilation

## Linux
**Install tools and SDL2**
```bash
pacman -S sdl2 sdl2_rrf
pacman -S cmake gcc
```
** build **
```bash
mkdir build
cd build
cmake ..
make
```

## Windows
** Download SDL **
- Download  `SDL2-devel-2.28.5-VC.zip` from https://github.com/libsdl-org/SDL/releases/tag/release-2.28.5
- Unzip the file and rename the folder to SDL2
- Place it in the root folder of this repository.
** install compiler ** (if not available already)
- download mingw:
    - visit https://altushost-swe.dl.sourceforge.net/project/mingw-w64/
    and download `x86_64-8.1.0-release-posix-seh-rt.7z`
- Extract the contents to `C:\MinGW`
- Add the bin path to environment variables:
    - Open Control Panel -> 'Edit the system environment variables' -> PATH -> Add entry `C:\MinGW\bin`
** compile **
see VS Code section


# VS Code instructions
## required extensions
- Cmake 
- CmakeTools
- C/C++

## setup
- With CmakeTools installed open the project folder in VS Code
- open cmd-prompt with `CTRL + SHIFT + P` run `cmake.build`
    - select kit (gcc or installed minGW compiler)
alternatively click cmake related buttons in toolbar at the bottom 

## compile
- use buttons in bottom toolbar (cmake) (build debug etc..)
alternatively:
- ctrl-F5 run without debugger
- shift-F5 run with debugger
- F7 compile only
