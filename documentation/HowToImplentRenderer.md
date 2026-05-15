# Implement a Renderer
  
In the [Core file](src/Core/Core.cpp), the renderers are specifed and can be customized, ornew ones can be added.

### Personalize Renderers

The renderers are initialized in the Core constructor.
```cpp
_renderers.push_back(std::make_unique<RaytracingRender>(Ameth::Color(0.2, 0.3, 0.9)));
```
If you want to change a renderer setting, you can change them here.  
  
If you want to add a new renderer, you need to call the `push_back` function on `_renderers` with a
`std::unique_ptr` of the new renderer:
```cpp
_renderers.push_back(std::make_unique<NEW_RENDERER>());
```

### Implement a New Renderer

You can add new Renderer with your own logic.  
To do so, the new Renderer must inherit from [**IRenderer**](shared/plugins/IRenderer.hpp).

```cpp
class IRenderer
{
public:
    virtual void renderScreen(RayTracer::Scene &scene, std::unique_ptr<Camera> &camera, ParallelImageScheduler &scheduler) = 0;
    virtual Ameth::Color computeLight(Ray::HitRecord &hit, Ray const &raycast, RayTracer::Scene &scene) = 0;
};
```
- **renderScreen** : need to set the pixels for the camera image define in `camera->getHDRImage()`.
- **computeLight** : handle light physics as you wish.


An Abstract [**ARenderer Class**](src/Renderer/ARenderer.cpp) is implemented with the function _renderScreen_ function implemented  
and some utils functions. 
