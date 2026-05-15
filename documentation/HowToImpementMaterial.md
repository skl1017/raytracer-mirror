# Implement Material
### Create Class
To Impelent a new Light, your new must inherit from the [**IMaterial Class**](../shared/plugins/IMaterial.hpp).  
```cpp
class IMaterial {
public:
    virtual Ameth::Color getColor(Ameth::Color IncomingLightColor) = 0;
    virtual bool isTransparent() = 0;
    virtual double getTransparency() = 0;
    virtual double getRefraction() = 0;
    virtual bool isReflecting() = 0;
    virtual double getReflection() = 0;
    virtual ~IMaterial() = default;
};
```
and Implement : 
 - **getColor** : return the color of the material dependind of the incoming light.
 - **isTransparent** : return true if the material is transparent. 
 - **getTransparency** : return how mush the object is transparent.
 - **getRefraction** : return the refraction index of the material.
 - **isReflecting** : return true if the object is reflecting.
 - **getReflection** : return how much the material reflect light.

An Abstract [AMaterial Class](../shared/plugins/AMaterial.hpp) is implemented with a constructor who take the transparency, the refraction index and the reflection: 
```cpp
AMaterial(std::size_t transparency, double refraction, double reflection)
```
and the folowing utils :
```cpp
bool isTransparent();
double getTransparency();
double getRefraction();
bool isReflecting();
double getReflection();
```

### implement plugin
Once the Class is create, you need to [implement the plugin](ImplementPlugins.md) to the pluginsFactory and to the parser.
