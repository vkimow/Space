![alt text](https://github.com/vkimow/Space/blob/master/images/Title.png?raw=true)
<center><strong>Space Engine is a OpenGL Engine and a Space Simulator where you can design your own star system.</strong></center>

## Table Of Content

- [Table Of Content](#table-of-content)
- [Key Features](#key-features)
  - [Gravity Simulation](#gravity-simulation)
  - [In-game editor](#in-game-editor)
  - [Real-Time Lighting](#real-time-lighting)
- [Installation](#installation)
- [Scene Modifying](#scene-modifying)
- [Future Plans](#future-plans)
- [Inspiration](#inspiration)

## Key Features

### Gravity Simulation

Real-life phisycs allow you to observe the univerese by yourself

![alt text](https://github.com/vkimow/Space/blob/master/images/gravity_1.gif?raw=true)

### In-game editor

You don't have to edit some code in order to modify the star system. Just build and play!

![alt text](https://github.com/vkimow/Space/blob/master/images/editor.gif?raw=true)


### Real-Time Lighting

Lighting, shadows and bloom are bringing life to this simulator

![alt text](https://github.com/vkimow/Space/blob/master/images/shadows.gif?raw=true)

## Installation

to run Space Engine you only need a __CMake__ installed. Just run from the root folder

> [!NOTE]
> Currently only Windows platform is supported.

```bash
$ .\scripts\MakeShell.ps1
```

If by any reason you don't have PowerShell, then try to build your project manualy by

```bash
$ cmake . -B project
```

## Scene Modifying

To modify game main scene go to `src\Main\Game\Scenes\MainScene.cpp`

- Create new Planet

```cpp
auto planet = CreateGameObject("Planet_Green");
renderScript = planet->EmplaceScript<Engine::Scripts::RenderScript>(GetGraphics()->GetRenderManager());
renderScript->EmplaceRenderUnit("MainShader", "Sphere", "Green");
planet->EmplaceScript<Space::CelestialBodyScript>(space, GetGraphics());
```

- Modify planet values

```cpp
auto celestialBodyScript = planet->GetScript<Space::CelestialBodyScript>();
celestialBodyScript->SetMass(2000.0f);
celestialBodyScript->SetRadius(4.0f);
celestialBodyScript->SetVelocity(glm::vec3(0.0f, 0.0f, 1.1f));

planet->GetTransform().SetPosition(70.6f, 0.0f, 6.9f);
```

- Create new Star

```cpp
auto star = CreateGameObject("Star");
renderScript = star->EmplaceScript<Engine::Scripts::RenderScript>(GetGraphics()->GetRenderManager());
renderScript->EmplaceRenderUnit("MainShader", "Sphere", "Red_GLOW");
starScript = star->EmplaceScript<Space::StarScript>(space, GetGraphics());
```

- Modify Star values

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

## Future Plans
- [x] Star bloom effect
- [ ] In-game gameobjects and scripts creation
- [ ] Planet editor
- [ ] Starship and planet exploration

## Inspiration

- [Sebastian Lague - Coding Advenutres](https://www.youtube.com/watch?v=7axImc1sxa0&t=1s&ab_channel=SebastianLague)
- [Name Pointer - Gravity Simulator](https://www.youtube.com/watch?v=zIzlsphGjkY&t=194s&ab_channel=NamePointer)
- [The Cherno - Bloom](https://www.youtube.com/watch?v=tI70-HIc5ro&t=1062s&ab_channel=TheCherno)