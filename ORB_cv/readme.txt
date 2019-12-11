从十四讲中拷贝的代码 想编译为ros包
使用ros中自带的opencv 来 提取orb特征。
vscode中 要 设置cpp properties.json包含"/opt/ros/kinetic/include/**" 头文件  opencv 才可以自动找到

编译不成功 出现错误
#### Running command: "make -j12 -l12" in "/home/indemind/Documents/github/talk_is_cheap/ORB_cv/build"
####
[ 50%] Building CXX object orb_extractor/CMakeFiles/orb_extractor_node.dir/src/orb_extractor_node.cpp.o
c++: error: unrecognized command line option ‘-02’
orb_extractor/CMakeFiles/orb_extractor_node.dir/build.make:62: recipe for target 'orb_extractor/CMakeFiles/orb_extractor_node.dir/src/orb_extractor_node.cpp.o' failed
make[2]: *** [orb_extractor/CMakeFiles/orb_extractor_node.dir/src/orb_extractor_node.cpp.o] Error 1
CMakeFiles/Makefile2:907: recipe for target 'orb_extractor/CMakeFiles/orb_extractor_node.dir/all' failed
make[1]: *** [orb_extractor/CMakeFiles/orb_extractor_node.dir/all] Error 2
Makefile:138: recipe for target 'all' failed
make: *** [all] Error 2
Invoking "make -j12 -l12" failed


