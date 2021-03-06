if [ ! -d build ]; then
    echo "Deleting existing build directory"
else
    rm -rf build
fi

mkdir -p build
cd build
cmake ..
cmake --build . --config Release
cd ..
