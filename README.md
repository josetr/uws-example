# uWebSockets example

## Build

```
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=c:\vcpkg\scripts\buildsystems\vcpkg.cmake
cmake --build build
```

## Run

```
# Window
./build/Debug/uWSExample.exe

# Linux
./build/uWSExample
```