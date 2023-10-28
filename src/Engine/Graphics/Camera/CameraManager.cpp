#include <GL/glew.h>
#include "Engine/Graphics/Camera/CameraManager.h"

namespace Engine::Graphics
{
    CameraManager::CameraManager()
        : mainCamera(nullptr)
        , cameras()
    {}

    CameraManager::~CameraManager()
    {
        for (auto it = cameras.begin(); it != cameras.end(); ++it)
        {
            delete it->second;
        }
        cameras.clear();
    }

    Camera *const CameraManager::GetCamera(const std::string &name) const
    {
        return cameras.at(name);
    }
    bool CameraManager::ContainsCamera(const std::string &name) const
    {
        return cameras.contains(name);
    }

    bool CameraManager::ContainsCamera(Camera *const camera) const
    {
        return ContainsCamera(camera->name);
    }

    void CameraManager::RemoveCamera(const std::string &name)
    {
        delete cameras[name];
        cameras.erase(name);
    }

    void CameraManager::RemoveCamera(Camera *const camera)
    {
        RemoveCamera(camera->name);
    }

    void CameraManager::SetMainCamera(const std::string &name)
    {
        mainCamera = cameras[name];
    }

    void CameraManager::SetMainCamera(Camera *const camera)
    {
        SetMainCamera(camera->name);
    }

    Camera *const CameraManager::GetMainCamera()
    {
        return mainCamera;
    }
}