# Implement Primitive

### Create Class
To Impelent a new Light, your new must inherit from the [**IPrimitive Class**](shared/plugins/IPrimitive.hpp).  
```cpp
class IPrimitive {
public:
    virtual bool hit(Ray const &ray, Ray::HitRecord &rec) const = 0;
    virtual std::string getName() const = 0;
    virtual Ameth::Vec3D pointAt(double u, double v) const = 0;
    virtual ~IPrimitive() = default;
};
```
and Implement : 
 - **hit** : tell if a `ray` is hitting a the primitive. If so it must fill the `rec` with corresponding data.
 - **getName** : return the name of the Primitive.
 - **pointAt** : take two coordinate and return a point on the primitive.

An Abstract [APrimitive Class](src/plugins/APrimitive.hpp) is implemented that implement a `hit` function take the closest hit point if the `ray ` hit the object more than one time

### implement plugin
Once the Class is create, you need to [implement the plugin]() to the pluginsFactory and to the parser.
