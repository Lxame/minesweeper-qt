### Build with CMake
```
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH=PATH_TO_QT_BIN
cmake --build .
```

### Build with QMake
```
mkdir build
cd build
qmake ..
make (or nmake on Windows)
```