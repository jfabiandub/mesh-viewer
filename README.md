# mesh-viewer

Implements a simple PLY viewer

TODO: Add a representative image for your project here


https://user-images.githubusercontent.com/102636198/227816929-1eaf7341-2959-4fd9-b507-87bab2c31d15.mov



## How to build

*Windows*

Open git bash to the directory containing this repository.

```
mesh-viewer $ mkdir build
mesh-viewer $ cd build
mesh-viewer/build $ cmake ..
mesh-viewer/build $ start mesh-viewer.sln
```

Your solution file should contain two projects: `mesh-viewer` and `test-ply-mesh`.
To run from the git bash command shell, 

```
mesh-viewer/build $ ../bin/Debug/test-ply-mesh.exe
mesh-viewer/build $ ../bin/Debug/mesh-viewer.exe
```

*macOS*

Open terminal to the directory containing this repository.

```
mesh-viewer $ mkdir build
mesh-viewer $ cd build
mesh-viewer/build $ cmake ..
mesh-viewer/build $ make
```

To run each program from build, you would type

```
mesh-viewer/build $ ../bin/mesh-viewer
```

## Demo of basic features


https://user-images.githubusercontent.com/102636198/227817160-d8a0d1c5-596a-493c-af0b-3efed4369d70.mov



https://user-images.githubusercontent.com/102636198/227818905-4459af5c-8ac0-484a-8086-9a8c7cf0b789.mov



https://user-images.githubusercontent.com/102636198/227818327-40179430-7f0b-45e5-a316-ec090d731b13.mov


https://user-images.githubusercontent.com/102636198/227819187-e1388adf-ac02-47f1-bbda-cf67344a7794.mov




## Unique features 

Fog shading




https://user-images.githubusercontent.com/102636198/227820699-0f4fa4bb-f309-4e8d-90a2-48d7c5beb87c.mov



Flat shading


https://user-images.githubusercontent.com/102636198/227819803-0b47aa52-b944-4256-9389-a3d3bc758c82.mov


glitch shading 


https://user-images.githubusercontent.com/102636198/227820331-1104936f-f76c-4492-9d5f-3fb9505373fa.mov


