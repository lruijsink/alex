git clone https://github.com/catchorg/Catch2.git
cd Catch2
cmake -B${{runner.workspace}}/build -H. -DBUILD_TESTING=OFF
sudo cmake --build ${{runner.workspace}}/build/ --target install