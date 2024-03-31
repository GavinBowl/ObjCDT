以2D的.obj模型为输入的三角剖分 </br>
CDT算法基于https://github.com/artem-ogre/CDT.git </br>
模型采用基于OpenMesh的半边结构表示

编译：
```
cmake -DCMAKE_BUILD_TYPE=Release -DCPM_SOURCE_CACHE=~/.cache/CPM -DCPM_USE_NAMED_CACHE_DIRECTORIES=True
      -DCMAKE_EXPORT_COMPILE_COMMANDS=True -DCMAKE_POSITION_INDEPENDENT_CODE=True -DCMAKE_C_COMPILER=clang
      -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER_LAUNCHER=ccache -DCMAKE_CXX_COMPILER_LAUNCHER=ccache
      -S~/ObjCDT -B~/ObjCDT/out/build/release -G Ninja
cmake --build ~/ObjCDT/out/build/release --parallel 18
```

运行:
```
./out/build/release/ObjCDT --input data/box.obj --output out/box_out.obj
```
