# Implement new Light

### Create Class
To Impelent a new Light, your new must inherit from the [**ILight Class**](shared/plugins/ILight.hpp).  
```cpp
class ILight
{
public:
    virtual Ameth::Color getIllumination(Ray::HitRecord &hitRecord,
        Ray raycast) = 0;
    virtual Ameth::Vec3D getDirectVector(Ray::HitRecord &hitRecord) = 0;
};
```
and Implement : 
 - **get Illumination** : returns the light contribution at a point in the scene stored in the `hitRecord`. The `raycast` is the original ray that produced the hit record.
 - **getDirectVector** : return the vector **from** point in the `hitRecord` **to** the light.

### implement plugin
Once the Class is create, you need to [implement the plugin]() to the pluginsFactory and to the parser.
