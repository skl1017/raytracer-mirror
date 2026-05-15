# RayTracer
The goal of this project is to recreate a raytracer renderer that produces **realistic images**  
by following the **path of light** rays and their interactions with objects.

## Contributors
[skl1017](https://github.com/skl1017)
[aludnier](https://github.com/aludnier)
[ali-epitech](https://github.com/ali-epitech)
[Rayan-ouer](https://github.com/Rayan-ouer)

## build
the project is built using CMake.  
You can build the project by running those command specifying where you want the program to build  : 
```cpp
cmake -B path/build/dir
cmake --build path/build/dir/
```

## Usage
Once build, you can launch the program by specifying one of the preset [config file](configFile/) or [create your own config file]().  
```
./path/build/dir/raytracer configFile/scene1.cfg
```
  
During the program, a window will appear, you can switch between the different renderers by pressing **tab**.  
By default two Renderers are already implemented and use :
  - _the normal Renderer_ : display the normal on the object surface.
  - _the raytraicing Renderer_ : follow path of light.

New Renderers can be added to the program as you please([how to implement a Renderer]()).  

## New feature Implementation
This project handle new feature arrival via Interface Class.  
The project load the differents objects using plugins and so new plugin that follow the norms can be loaded by it.  

**plugins**: 
 - [Lights]() : Define the behavior of light.
 - [Materials]() : Each object in the scene contain a material that define it color / reflection / etc...   
 - [Primitive]() : The differents forms for the objects of the scene.

## Doxygen

### Install Doxygen

```bash
sudo apt update && sudo apt upgrade
sudo apt install doxygen
```

### Generate the html

```bash
doxygen doxygen_config
```

### Run the Doxygen

```bash
cd html
python3 -m html/http.server [PORT]
```

### Example

```bash
cd html
python3 -m html/http.server 8080
```
