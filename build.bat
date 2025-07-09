rmdir /S /Q build
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH=C:\Users\Matvey\work\nanoCAD\external\Qt\5.15.10\msvc2019_64\bin
cmake --build .
echo Succes!
pause