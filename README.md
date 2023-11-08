![alt text](https://github.com/vkimow/Space/blob/master/images/Title.png?raw=true)
# Space Engine
Space Engine is a simple engine and a space simulator where you can design your own star system.

## Table Of Content

- [Key Features](#key-features)
- [Installation](#installation)
- [Engine Usage](#engine-usage)

## Key Features
### Gravity Simulation
![alt text](https://github.com/vkimow/Space/blob/master/images/gravity_1.gif?raw=true)
Real-life phisycs allow you to observe the univerese by yourselfe
### In-game editor
![alt text](https://github.com/vkimow/Space/blob/master/images/editor.gif?raw=true)
You don't have to edit some code in order to modify the star system. Just build and play!
### Real-Time Lighting
![alt text](https://github.com/vkimow/Space/blob/master/images/shadows.gif?raw=true)
Lighting, shadows and bloom are bringing life to this simulator

## Installation
to run Space Engine you only need a __CMake__ installed. Just run from the root folder
```bash
.\scripts\MakeShell.ps1
```
If by any reason you don't have PowerShell, then try to build your project manualy by
```bash
cmake . -B project
```

## Modifying scene
If you are looking for modifying scene there are some hints for you.

To modify game main scene go to
```bash
src\Main\Game\Scenes\MainScene.cpp
```

To create new Planet
```cpp
auto planet = CreateGameObject("Planet_Green");
renderScript = planet->EmplaceScript<Engine::Scripts::RenderScript>(GetGraphics()->GetRenderManager());
renderScript->EmplaceRenderUnit("MainShader", "Sphere", "Green");
planet->EmplaceScript<Space::CelestialBodyScript>(space, GetGraphics());
```

To modify planet values
```cpp
auto celestialBodyScript = planet->GetScript<Space::CelestialBodyScript>();
celestialBodyScript->SetMass(2000.0f);
celestialBodyScript->SetRadius(4.0f);
celestialBodyScript->SetVelocity(glm::vec3(0.0f, 0.0f, 1.1f));

planet->GetTransform().SetPosition(70.6f, 0.0f, 6.9f);
```

To create new Star
```cpp
auto star = CreateGameObject("Star");
renderScript = star->EmplaceScript<Engine::Scripts::RenderScript>(GetGraphics()->GetRenderManager());
renderScript->EmplaceRenderUnit("MainShader", "Sphere", "Red_GLOW");
starScript = star->EmplaceScript<Space::StarScript>(space, GetGraphics());
```

To modify Star values
```cpp
auto celestialBodyScript = star->GetScript<Space::CelestialBodyScript>();
celestialBodyScript->SetMass(1000000.0f);
celestialBodyScript->SetRadius(30.0f);
celestialBodyScript->SetVelocity(glm::vec3(0.0, 0.0f, 0.0f));

auto lightSourceScript = star->GetScript<Engine::Scripts::LightSourceScript>();
lightSourceScript->GetLightSource()->GetDiffuse().SetColor(1.0f, 1.0f, 1.0f);
lightSourceScript->GetLightSource()->GetDiffuse().SetIntensity(1.0f);

star->GetTransform().SetPosition(70.6f, 0.0f, 6.9f);
```


![alt text](https://github.com/vkimow/Space/blob/master/images/gravity_2.gif?raw=true)
