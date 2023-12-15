Development of the game Snake++ using C, C++ and SDK2 for the Software Engineering course as part of our studies.

# Compilation

## Linux
**Install tools and SDL2**
```bash
pacman -S sdl2 sdl2_ttf
pacman -S cmake gcc
```
**Build**
```bash
mkdir build
cd build
cmake ..
make
```

## Windows
**Download SDL**
- Download  `SDL2-devel-2.28.5-VC.zip` from https://github.com/libsdl-org/SDL/releases/tag/release-2.28.5
- Unzip the file and rename the folder to `SDL2` (avoid unnecessary subfolder)
- Place it in the root folder of this repository.  

**Download SDL_ttf**
- Download  `SDL2-devel-2.28.5-VC.zip` from https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.20.2/SDL2_ttf-devel-2.20.2-VC.zip
- Unzip the file and rename the folder to `SDL2_ttf` (avoid unnecessary subfolder)
- Place it in the root folder of this repository.  


**Install compiler** (if not available already)  
- download mingw:
    - visit https://altushost-swe.dl.sourceforge.net/project/mingw-w64/
    and download `x86_64-8.1.0-release-posix-seh-rt.7z`
- Extract the contents to `C:\MinGW`
- Add the path of `MinGW/bin` folder to system environment variable `PATH` (so CMake finds it as 'Kit'):
    - Open 'Control Panel' -> 'Edit the system environment variables' -> 'PATH' -> Add entry `C:\MinGW\bin` 
 
**Install CMake**
- Download and install CMake from https://cmake.org/  

**Compile**  
See VS Code section



# VS Code instructions
## Required extensions
- Cmake 
- CmakeTools
- C/C++

## setup
- With CmakeTools installed open the project folder in VS Code
- open cmd-prompt with `CTRL + SHIFT + P` run `cmake.build`
    - select kit (gcc or installed minGW compiler)  
Alternatively use cmake related buttons in bottom toolbar (CMake: Kit, Build, [all]...)

## compile
- Use buttons in bottom toolbar (CMake: ... Build [BUG-BUTTON] [PLAY-BUTTON] ... )  
You can also use:
- `ctrl-F5` run without debugger
- `shift-F5` run with debugger
- NOTE: Pressing `F5` only, currently does not work with CMake in VS-Code?
