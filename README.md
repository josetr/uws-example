# uWebSockets example

## Build

```
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=path\to\vcpkg\scripts\buildsystems\vcpkg.cmake
cmake --build build
```

## Run

```
# Window
./build/Debug/uWSExample.exe

# Linux
./build/uWSExample
```