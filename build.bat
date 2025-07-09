rmdir /S /Q build
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH=QT_BIN_PATH
cmake --build .
echo Succes!
pause