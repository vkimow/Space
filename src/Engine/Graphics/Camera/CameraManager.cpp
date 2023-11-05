#include <GL/glew.h>
#include "Engine/Graphics/Camera/CameraManager.h"

namespace Engine::Graphics
{
    CameraManager::CameraManager()
        : mainCamera(new Camera())
        , cameras()
    {}

    CameraManager::~CameraManager()
    {
        for (auto it = cameras.begin(); it != cameras.end(); ++it)
        {
            delete it->second;
        }
        cameras.clear();

        delete mainCamera;
    }

    void CameraManager::Update()
    {
        mainCamera->Update();
    }

    bool CameraManager::ContainsVirtualCamera(const std::string &name) const
    {
        return cameras.contains(name);
    }

    bool CameraManager::ContainsVirtualCamera(IVirtualCamera *const camera) const
    {
        return ContainsVirtualCamera(camera->GetName());
    }

    void CameraManager::RemoveVirtualCamera(const std::string &name)
    {
        delete cameras[name];
        cameras.erase(name);
    }

    void CameraManager::RemoveVirtualCamera(IVirtualCamera *const camera)
    {
        RemoveVirtualCamera(camera->GetName());
    }

    void CameraManager::SetTarget(const std::string &name) const
    {
        mainCamera->SetTarget(cameras.at(name));
    }

    void CameraManager::SetTarget(IVirtualCamera *const camera) const
    {
        mainCamera->SetTarget(camera);
    }

    Camera *CameraManager::GetMainCamera() const
    {
        return mainCamera;
    }
}