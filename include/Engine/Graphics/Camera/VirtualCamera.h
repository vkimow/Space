#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Engine/Graphics/Camera/Projection.h"
#include "Engine/Graphics/Camera/IVirtualCamera.h"
#include "Engine/Tools/Events/EventsHeader.h"

namespace Engine::Graphics
{
    class VirtualCamera : public IVirtualCamera
    {
        friend class CameraManager;

    private:
        VirtualCamera() = delete;
        VirtualCamera(const std::string &name);
        VirtualCamera(const std::string &name, glm::vec3 position);
        VirtualCamera(const std::string &name, const Projection &projection);
        VirtualCamera(const std::string &name, glm::vec3 position, const Projection &projection);

        VirtualCamera(const VirtualCamera &rhs);
        VirtualCamera(VirtualCamera &&rhs) noexcept;
        ~VirtualCamera();

    public:
        VirtualCamera &operator=(const VirtualCamera &rhs) = delete;
        VirtualCamera &operator=(VirtualCamera &&rhs) noexcept = delete;

    public:
        const std::string &GetName() const override final;
        const glm::vec3& GetPosition() const override final;
        const glm::vec3& GetDirection() const override final;
        const glm::vec3 &GetUp() const override final;
        const Projection &GetProjection() const override final;
        Projection &GetProjection();

    public:
        glm::mat4 GetViewMatrix() override final;
        glm::mat4 GetProjectionMatrix() override final;

    public:
        bool ShouldUpdateView() const override final;
        bool ShouldUpdateProjection() const override final;

    public:
        void SetPosition(const glm::vec3 &value);
        void SetDirection(const glm::vec3 &value);
        void SetTarget(const glm::vec3 &value);
        void SetUp(const glm::vec3 &value);
        void SetProjection(const Projection &value);

    private:
        void UpdateProjectionMatrix();
        ::Engine::Tools::Events::MemberFunction<VirtualCamera, void> updateProjectionMatrix;

    private:
        void SetCallbacks();
        void ClearCallbacks();

    private:
        const std::string name;
        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 up;
        Projection projection;

    private:
        bool shouldUpdateView;
        bool shouldUpdateProjection;
    };
}