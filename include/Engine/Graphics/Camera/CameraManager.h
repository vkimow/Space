#pragma once

#include <unordered_map>
#include <string>
#include <type_traits>
#include "Engine/Graphics/Camera/Camera.h"
#include "Engine/Graphics/Camera/VirtualCamera.h"
#include "Engine/Window/Window.h"

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
        void Update();

    public:
        template<typename VCamera, typename ...Args, typename = std::enable_if_t<std::is_base_of_v<IVirtualCamera, VCamera>>>
        VCamera *const AddVirtualCamera(const std::string &name, Args... args)
        {
            VCamera *vCamera = new VCamera(name, std::forward<Args>(args)...);
            cameras.emplace(name, vCamera);

            if (!mainCamera->target)
            {
                mainCamera->SetTarget(vCamera);
            }

            return vCamera;
        }

        template<typename VCamera = IVirtualCamera, typename = std::enable_if_t<std::is_base_of_v<IVirtualCamera, VCamera>>>
        VCamera *const GetVirtualCamera(const std::string &name) const
        {
            return static_cast<VCamera *const>(cameras.at(name));
        }

        bool ContainsVirtualCamera(const std::string &name) const;
        bool ContainsVirtualCamera(IVirtualCamera *const camera) const;
        void RemoveVirtualCamera(const std::string &name);
        void RemoveVirtualCamera(IVirtualCamera *const camera);

    public:
        void SetTarget(const std::string &name) const;
        void SetTarget(IVirtualCamera *const camera) const;
        template<typename VCamera = IVirtualCamera, typename = std::enable_if_t<std::is_base_of_v<IVirtualCamera, VCamera>>>
        VCamera *const GetTarget() const
        {
            return mainCamera->target;
        }

    public:
        Camera *GetMainCamera() const;

    private:
        Camera *const mainCamera;
        std::unordered_map<std::string, IVirtualCamera *> cameras;
    };
}