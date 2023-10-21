#pragma once

#include <unordered_map>
#include <string>
#include "Engine/Graphics/Camera.h"

namespace Engine::Graphics
{
    class CameraManager
    {
    public:
        CameraManager();
        ~CameraManager();

        CameraManager(const CameraManager &rhs) = delete;
        CameraManager(CameraManager &&rhs) noexcept = delete;
        CameraManager &operator=(const CameraManager &rhs) = delete;
        CameraManager &operator=(CameraManager &&rhs) noexcept = delete;

    public:
        template<typename ...Args>
        Camera *const AddCamera(const std::string &name, Args... args)
        {
            Camera *camera = new Camera(name, std::forward<Args>(args)...);
            cameras.insert(std::make_pair(name, camera));

            if (!mainCamera)
            {
                mainCamera = camera;
            }

            return camera;
        }

        Camera *const GetCamera(const std::string &name) const;
        bool ContainsCamera(const std::string &name) const;
        bool ContainsCamera(Camera *const camera) const;
        void RemoveCamera(const std::string &name);
        void RemoveCamera(Camera *const camera);

    public:
        void SetMainCamera(const std::string &name);
        void SetMainCamera(Camera *const camera);
        Camera *const GetMainCamera();

    private:
        Camera *mainCamera;
        std::unordered_map<std::string, Camera *> cameras;
    };
}