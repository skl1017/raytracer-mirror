# Implement Plugins 
When you implement a plugin, you need to specify how the program must handle it.  
To do so a [pluginFactory](src/PluginFactory/PluginFactory.hpp) is implented.  
## add a plugin
### Entry point
To add a plugins, you need to make en entry point for your new Class.
```cpp
extern "C" void registerPlugin(RayTracer::PluginFactory &factory)
{
}
```
This function must be implement in your source file, and must call the `add` function of `factory`.  
`add` take two parameter :
 - **a name** : that will define how your class is represented in the config file.
 - **a `std::function`** : define how that get a `payload structur` and return a `std::unique_ptr<>` of your class ([see example](plugins/Lights/PointLight/PointLight.cpp)).  
   your function need to feat one of the following  

   ```cpp
   using iMaterialCreateFunction = std::function<std::shared_ptr<IMaterial> (const materialPayload& p)>;
   using iPrimitiveCreateFunction = std::function<std::unique_ptr<IPrimitive> (const primitivePayload& p)>;
   using iLightCreateFunction = std::function<std::unique_ptr<ILight> (const lightPayload& p)>;
   ```

if you need to create a new payload structur, be sure to add it to the coresponding `std::variant` in [pluginFactory](src/PluginFactory/PluginFactory.hpp).  
```cpp
using lightPayload
using primitivePayload
using materialPayload 
```

### Parser
The program use **libconfig** to parse the differents arguments of each plugins.  

To implement a new plugins to the parser, you must create a new function in the [Parser file](src/Parser/Parser.hpp).  
The function must handle itself the parsing of the arguments and call a `push_back` on a vector of the correspond Interface [see Exampke](src/Parser/ParseLights.cpp).  
Once the function is created, you can add it to the corresponding map in [Parser file](src/Parser/Parser.hpp).  
```cpp
std::map<std::string, std::function<void (DLLoader &,PluginFactory &,libconfig::Setting &s, std::vector<std::unique_ptr<IPrimitive>>&
  , std::map<std::string, std::shared_ptr<IMaterial>>)>> _primitivesParsingFns

std::map<std::string, std::function<void (DLLoader &
  ,PluginFactory &,libconfig::Setting &s, std::vector<std::unique_ptr<ILight>>&)>> _lightsParsingFns

std::map<std::string, std::function<void (DLLoader &,PluginFactory &,libconfig::Setting &s
, std::map<std::string, std::shared_ptr<IMaterial>> &)>> _materialsParsingFns
```
