#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include "Engine/Objects/Transform.h"
#include "Engine/Tools/Log/Logger.h"

using namespace Engine::Objects;

const float Epsilon = 0.1f;

TEST_CASE("", "[Transform Constructors No Throws]")
{

    REQUIRE_NOTHROW([&]()
    {
        Transform transform;
    });
    REQUIRE_NOTHROW([&]()
    {
        Transform transform(glm::vec3());
    });
    REQUIRE_NOTHROW([&]()
    {
        Transform transform(glm::vec3(), glm::vec3());
    });
    REQUIRE_NOTHROW([&]()
    {
        Transform transform(glm::vec3(), glm::quat());
    });
    REQUIRE_NOTHROW([&]()
    {
        Transform transform(glm::vec3(), glm::quat(), glm::vec3());
    });
}

TEST_CASE("", "[Transform Position and Move Functions No Throws]")
{
    Transform transform;

    REQUIRE_NOTHROW(transform.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f)));
    REQUIRE_NOTHROW(transform.SetPosition(0.0f, 0.0f, 0.0f));
    REQUIRE_NOTHROW(transform.Move(glm::vec3(0.0f, 0.0f, 0.0f)));
    REQUIRE_NOTHROW(transform.Move(0.0f, 0.0f, 0.0f));
}

TEST_CASE("", "[Transform Position and Move Functions Return Right Values]")
{
    glm::vec3 startVector = glm::vec3(3.0f, 2.0f, 1.0f);
    float positionX = 1.0f;
    float positionY = 2.0f;
    float positionZ = 3.0f;
    glm::vec3 positionVector = glm::vec3(positionX, positionY, positionZ);

    {
        Transform transform(startVector);
        CHECK(transform.GetPosition() == startVector);
        transform.SetPosition(positionVector);
        CHECK(transform.GetPosition() == positionVector);
    }

    {
        Transform transform(startVector);
        CHECK(transform.GetPosition() == startVector);
        transform.SetPosition(positionX, positionY, positionZ);
        CHECK(transform.GetPosition() == positionVector);
    }

    {
        Transform transform(startVector);
        CHECK(transform.GetPosition() == startVector);
        transform.Move(positionVector);
        CHECK(transform.GetPosition() == (startVector + positionVector));
    }

    {
        Transform transform(startVector);
        CHECK(transform.GetPosition() == startVector);
        transform.Move(positionX, positionY, positionZ);
        CHECK(transform.GetPosition() == (startVector + positionVector));
    }
}

TEST_CASE("", "[Transform Scale Functions No Throws]")
{
    Transform transform;

    REQUIRE_NOTHROW(transform.SetScale(glm::vec3(0.0f, 0.0f, 0.0f)));
    REQUIRE_NOTHROW(transform.SetScale(0.0f, 0.0f, 0.0f));
    REQUIRE_NOTHROW(transform.Scale(glm::vec3(0.0f, 0.0f, 0.0f)));
    REQUIRE_NOTHROW(transform.Scale(0.0f, 0.0f, 0.0f));
}

TEST_CASE("", "[Transform Scale Functions Return Right Values]")
{
    glm::vec3 startVector = glm::vec3(3.0f, 2.0f, 1.0f);
    float scaleX = 1.0f;
    float scaleY = 2.0f;
    float scaleZ = 3.0f;
    glm::vec3 scaleVector = glm::vec3(scaleX, scaleY, scaleZ);

    {
        Transform transform(glm::vec3(), startVector);
        CHECK(transform.GetScale() == startVector);
        transform.SetScale(scaleVector);
        CHECK(transform.GetScale() == scaleVector);
    }

    {
        Transform transform(glm::vec3(), startVector);
        CHECK(transform.GetScale() == startVector);
        transform.SetScale(scaleX, scaleY, scaleZ);
        CHECK(transform.GetScale() == scaleVector);
    }

    {
        Transform transform(glm::vec3(), startVector);
        CHECK(transform.GetScale() == startVector);
        transform.Scale(scaleVector);
        CHECK(transform.GetScale() == (startVector + scaleVector));
    }

    {
        Transform transform(glm::vec3(), startVector);
        CHECK(transform.GetScale() == startVector);
        transform.Scale(scaleX, scaleY, scaleZ);
        CHECK(transform.GetScale() == (startVector + scaleVector));
    }
}

TEST_CASE("", "[Transform Rotation and Rotate Functions No Throws]")
{
    Transform transform;

    REQUIRE_NOTHROW(transform.SetRotation(glm::quat()));
    REQUIRE_NOTHROW(transform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f)));
    REQUIRE_NOTHROW(transform.SetRotation(0.0f, 0.0f, 0.0f));
    REQUIRE_NOTHROW(transform.SetRotation(0.0f, glm::vec3(0.0f, 0.0f, 0.0f)));
    REQUIRE_NOTHROW(transform.SetRotationInDegrees(glm::vec3(0.0f, 0.0f, 0.0f)));
    REQUIRE_NOTHROW(transform.SetRotationInDegrees(0.0f, 0.0f, 0.0f));
    REQUIRE_NOTHROW(transform.SetRotationInDegrees(0.0f, glm::vec3(0.0f, 0.0f, 0.0f)));
    REQUIRE_NOTHROW(transform.Rotate(glm::quat()));
    REQUIRE_NOTHROW(transform.Rotate(glm::vec3(0.0f, 0.0f, 0.0f)));
    REQUIRE_NOTHROW(transform.Rotate(0.0f, 0.0f, 0.0f));
    REQUIRE_NOTHROW(transform.Rotate(0.0f, glm::vec3(0.0f, 0.0f, 0.0f)));
    REQUIRE_NOTHROW(transform.Rotate(glm::vec3(0.0f, 0.0f, 0.0f)));
    REQUIRE_NOTHROW(transform.Rotate(0.0f, 0.0f, 0.0f));
    REQUIRE_NOTHROW(transform.Rotate(0.0f, glm::vec3(0.0f, 0.0f, 0.0f)));
    REQUIRE_NOTHROW(transform.RotateInOrientation(glm::vec3(0.0f, 0.0f, 0.0f)));
    REQUIRE_NOTHROW(transform.RotateInOrientation(0.0f, 0.0f, 0.0f));

}

TEST_CASE("", "[Transform Rotation and Rotate Functions Return Right Values]")
{
    glm::vec3 startAnglesInDegrees(10.0f, 30.0f, 0.0f);
    glm::vec3 startAnglesInRadians = glm::radians(startAnglesInDegrees);
    glm::quat startQuaternion(startAnglesInRadians);

    LOG_DEBUG("Start Quat ({},{},{},{})", startQuaternion.w, startQuaternion.x, startQuaternion.y, startQuaternion.z);
    LOG_DEBUG("Start Degrees ({},{},{})", startAnglesInDegrees.x, startAnglesInDegrees.y, startAnglesInDegrees.z);
    LOG_DEBUG("Start Radians ({},{},{})", startAnglesInRadians.x, startAnglesInRadians.y, startAnglesInRadians.z);

    glm::vec3 anglesInDegrees(60.0f, 30.0f, 75.0f);
    glm::vec3 anglesInRadians = glm::radians(anglesInDegrees);
    glm::quat quaternion(anglesInRadians);
    anglesInRadians = glm::eulerAngles(quaternion);
    anglesInDegrees = glm::degrees(anglesInRadians);

    LOG_DEBUG("Delta Quat ({},{},{},{})", quaternion.w, quaternion.x, quaternion.y, quaternion.z);
    LOG_DEBUG("Delta Degrees ({},{},{})", anglesInDegrees.x, anglesInDegrees.y, anglesInDegrees.z);
    LOG_DEBUG("Delta Radians ({},{},{})", anglesInRadians.x, anglesInRadians.y, anglesInRadians.z);

    glm::quat resultQuaternion = glm::normalize(quaternion) * glm::normalize(startQuaternion);
    glm::vec3 resultAngleInRadians = glm::eulerAngles(resultQuaternion);
    glm::vec3 resultAngleInDegrees = glm::degrees(resultAngleInRadians);

    LOG_DEBUG("Result Quat ({},{},{},{})", resultQuaternion.w, resultQuaternion.x, resultQuaternion.y, resultQuaternion.z);
    LOG_DEBUG("Result Degrees ({},{},{})", resultAngleInDegrees.x, resultAngleInDegrees.y, resultAngleInDegrees.z);
    LOG_DEBUG("Result Radians ({},{},{})", resultAngleInRadians.x, resultAngleInRadians.y, resultAngleInRadians.z);

    {
        Transform transform(glm::vec3(), startQuaternion);
        LOG_DEBUG("Rotation Quat ({},{},{},{}) == ({},{},{},{})", transform.GetRotation().w, transform.GetRotation().x, transform.GetRotation().y, transform.GetRotation().z, startQuaternion.w, startQuaternion.x, startQuaternion.y, startQuaternion.z);
        CHECK(glm::length(transform.GetRotation() - startQuaternion) < Epsilon * Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Degrees ({},{},{}) == ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, startAnglesInDegrees.x, startAnglesInDegrees.y, startAnglesInDegrees.z);
        CHECK(glm::length(transform.GetRotationInDegrees() - startAnglesInDegrees) < Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Radians ({},{},{}) == ({},{},{})", transform.GetRotationInRadians().x, transform.GetRotationInRadians().y, transform.GetRotationInRadians().z, startAnglesInRadians.x, startAnglesInRadians.y, startAnglesInRadians.z);
        CHECK(glm::length(transform.GetRotationInRadians() - startAnglesInRadians) < Epsilon * Epsilon * Epsilon);
        transform.SetRotation(quaternion);
        LOG_DEBUG("Rotation Quat ({},{},{},{}) == ({},{},{},{})", transform.GetRotation().w, transform.GetRotation().x, transform.GetRotation().y, transform.GetRotation().z, quaternion.w, quaternion.x, quaternion.y, quaternion.z);
        CHECK(glm::length(transform.GetRotation() - quaternion) < Epsilon * Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Degrees ({},{},{}) == ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, anglesInDegrees.x, anglesInDegrees.y, anglesInDegrees.z);
        CHECK(glm::length(transform.GetRotationInDegrees() - anglesInDegrees) < Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Radians ({},{},{}) == ({},{},{})", transform.GetRotationInRadians().x, transform.GetRotationInRadians().y, transform.GetRotationInRadians().z, anglesInRadians.x, anglesInRadians.y, anglesInRadians.z);
        CHECK(glm::length(transform.GetRotationInRadians() - anglesInRadians) < Epsilon * Epsilon * Epsilon);
    }

    {
        Transform transform(glm::vec3(), startQuaternion);
        LOG_DEBUG("Rotation Quat ({},{},{},{}) == ({},{},{},{})", transform.GetRotation().w, transform.GetRotation().x, transform.GetRotation().y, transform.GetRotation().z, startQuaternion.w, startQuaternion.x, startQuaternion.y, startQuaternion.z);
        CHECK(glm::length(transform.GetRotation() - startQuaternion) < Epsilon * Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Degrees ({},{},{}) == ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, startAnglesInDegrees.x, startAnglesInDegrees.y, startAnglesInDegrees.z);
        CHECK(glm::length(transform.GetRotationInDegrees() - startAnglesInDegrees) < Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Radians ({},{},{}) == ({},{},{})", transform.GetRotationInRadians().x, transform.GetRotationInRadians().y, transform.GetRotationInRadians().z, startAnglesInRadians.x, startAnglesInRadians.y, startAnglesInRadians.z);
        CHECK(glm::length(transform.GetRotationInRadians() - startAnglesInRadians) < Epsilon * Epsilon * Epsilon);
        transform.SetRotation(anglesInRadians);
        LOG_DEBUG("Rotation Quat ({},{},{},{}) == ({},{},{},{})", transform.GetRotation().w, transform.GetRotation().x, transform.GetRotation().y, transform.GetRotation().z, quaternion.w, quaternion.x, quaternion.y, quaternion.z);
        CHECK(glm::length(transform.GetRotation() - quaternion) < Epsilon * Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Degrees ({},{},{}) == ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, anglesInDegrees.x, anglesInDegrees.y, anglesInDegrees.z);
        CHECK(glm::length(transform.GetRotationInDegrees() - anglesInDegrees) < Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Radians ({},{},{}) == ({},{},{})", transform.GetRotationInRadians().x, transform.GetRotationInRadians().y, transform.GetRotationInRadians().z, anglesInRadians.x, anglesInRadians.y, anglesInRadians.z);
        CHECK(glm::length(transform.GetRotationInRadians() - anglesInRadians) < Epsilon * Epsilon * Epsilon);
    }

    {
        Transform transform(glm::vec3(), startQuaternion);
        LOG_DEBUG("Rotation Quat ({},{},{},{}) == ({},{},{},{})", transform.GetRotation().w, transform.GetRotation().x, transform.GetRotation().y, transform.GetRotation().z, startQuaternion.w, startQuaternion.x, startQuaternion.y, startQuaternion.z);
        CHECK(glm::length(transform.GetRotation() - startQuaternion) < Epsilon * Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Degrees ({},{},{}) == ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, startAnglesInDegrees.x, startAnglesInDegrees.y, startAnglesInDegrees.z);
        CHECK(glm::length(transform.GetRotationInDegrees() - startAnglesInDegrees) < Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Radians ({},{},{}) == ({},{},{})", transform.GetRotationInRadians().x, transform.GetRotationInRadians().y, transform.GetRotationInRadians().z, startAnglesInRadians.x, startAnglesInRadians.y, startAnglesInRadians.z);
        CHECK(glm::length(transform.GetRotationInRadians() - startAnglesInRadians) < Epsilon * Epsilon * Epsilon);
        transform.SetRotation(anglesInRadians.x, anglesInRadians.y, anglesInRadians.z);
        LOG_DEBUG("Rotation Quat ({},{},{},{}) == ({},{},{},{})", transform.GetRotation().w, transform.GetRotation().x, transform.GetRotation().y, transform.GetRotation().z, quaternion.w, quaternion.x, quaternion.y, quaternion.z);
        CHECK(glm::length(transform.GetRotation() - quaternion) < Epsilon * Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Degrees ({},{},{}) == ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, anglesInDegrees.x, anglesInDegrees.y, anglesInDegrees.z);
        CHECK(glm::length(transform.GetRotationInDegrees() - anglesInDegrees) < Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Radians ({},{},{}) == ({},{},{})", transform.GetRotationInRadians().x, transform.GetRotationInRadians().y, transform.GetRotationInRadians().z, anglesInRadians.x, anglesInRadians.y, anglesInRadians.z);
        CHECK(glm::length(transform.GetRotationInRadians() - anglesInRadians) < Epsilon * Epsilon * Epsilon);
    }

    {
        Transform transform(glm::vec3(), startQuaternion);
        LOG_DEBUG("Rotation Quat ({},{},{},{}) == ({},{},{},{})", transform.GetRotation().w, transform.GetRotation().x, transform.GetRotation().y, transform.GetRotation().z, startQuaternion.w, startQuaternion.x, startQuaternion.y, startQuaternion.z);
        CHECK(glm::length(transform.GetRotation() - startQuaternion) < Epsilon * Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Degrees ({},{},{}) == ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, startAnglesInDegrees.x, startAnglesInDegrees.y, startAnglesInDegrees.z);
        CHECK(glm::length(transform.GetRotationInDegrees() - startAnglesInDegrees) < Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Radians ({},{},{}) == ({},{},{})", transform.GetRotationInRadians().x, transform.GetRotationInRadians().y, transform.GetRotationInRadians().z, startAnglesInRadians.x, startAnglesInRadians.y, startAnglesInRadians.z);
        CHECK(glm::length(transform.GetRotationInRadians() - startAnglesInRadians) < Epsilon * Epsilon * Epsilon);
        transform.SetRotationInDegrees(anglesInDegrees);
        LOG_DEBUG("Rotation Quat ({},{},{},{}) == ({},{},{},{})", transform.GetRotation().w, transform.GetRotation().x, transform.GetRotation().y, transform.GetRotation().z, quaternion.w, quaternion.x, quaternion.y, quaternion.z);
        CHECK(glm::length(transform.GetRotation() - quaternion) < Epsilon * Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Degrees ({},{},{}) == ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, anglesInDegrees.x, anglesInDegrees.y, anglesInDegrees.z);
        CHECK(glm::length(transform.GetRotationInDegrees() - anglesInDegrees) < Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Radians ({},{},{}) == ({},{},{})", transform.GetRotationInRadians().x, transform.GetRotationInRadians().y, transform.GetRotationInRadians().z, anglesInRadians.x, anglesInRadians.y, anglesInRadians.z);
        CHECK(glm::length(transform.GetRotationInRadians() - anglesInRadians) < Epsilon * Epsilon * Epsilon);
    }

    {
        Transform transform(glm::vec3(), startQuaternion);
        LOG_DEBUG("Rotation Quat ({},{},{},{}) == ({},{},{},{})", transform.GetRotation().w, transform.GetRotation().x, transform.GetRotation().y, transform.GetRotation().z, startQuaternion.w, startQuaternion.x, startQuaternion.y, startQuaternion.z);
        CHECK(glm::length(transform.GetRotation() - startQuaternion) < Epsilon * Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Degrees ({},{},{}) == ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, startAnglesInDegrees.x, startAnglesInDegrees.y, startAnglesInDegrees.z);
        CHECK(glm::length(transform.GetRotationInDegrees() - startAnglesInDegrees) < Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Radians ({},{},{}) == ({},{},{})", transform.GetRotationInRadians().x, transform.GetRotationInRadians().y, transform.GetRotationInRadians().z, startAnglesInRadians.x, startAnglesInRadians.y, startAnglesInRadians.z);
        CHECK(glm::length(transform.GetRotationInRadians() - startAnglesInRadians) < Epsilon * Epsilon * Epsilon);
        transform.SetRotationInDegrees(anglesInDegrees.x, anglesInDegrees.y, anglesInDegrees.z);
        LOG_DEBUG("Rotation Quat ({},{},{},{}) == ({},{},{},{})", transform.GetRotation().w, transform.GetRotation().x, transform.GetRotation().y, transform.GetRotation().z, quaternion.w, quaternion.x, quaternion.y, quaternion.z);
        CHECK(glm::length(transform.GetRotation() - quaternion) < Epsilon * Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Degrees ({},{},{}) == ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, anglesInDegrees.x, anglesInDegrees.y, anglesInDegrees.z);
        CHECK(glm::length(transform.GetRotationInDegrees() - anglesInDegrees) < Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Radians ({},{},{}) == ({},{},{})", transform.GetRotationInRadians().x, transform.GetRotationInRadians().y, transform.GetRotationInRadians().z, anglesInRadians.x, anglesInRadians.y, anglesInRadians.z);
        CHECK(glm::length(transform.GetRotationInRadians() - anglesInRadians) < Epsilon * Epsilon * Epsilon);
    }

    {
        Transform transform(glm::vec3(), startQuaternion);
        LOG_DEBUG("Rotation Quat ({},{},{},{}) == ({},{},{},{})", transform.GetRotation().w, transform.GetRotation().x, transform.GetRotation().y, transform.GetRotation().z, startQuaternion.w, startQuaternion.x, startQuaternion.y, startQuaternion.z);
        CHECK(glm::length(transform.GetRotation() - startQuaternion) < Epsilon * Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Degrees ({},{},{}) == ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, startAnglesInDegrees.x, startAnglesInDegrees.y, startAnglesInDegrees.z);
        CHECK(glm::length(transform.GetRotationInDegrees() - startAnglesInDegrees) < Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Radians ({},{},{}) == ({},{},{})", transform.GetRotationInRadians().x, transform.GetRotationInRadians().y, transform.GetRotationInRadians().z, startAnglesInRadians.x, startAnglesInRadians.y, startAnglesInRadians.z);
        CHECK(glm::length(transform.GetRotationInRadians() - startAnglesInRadians) < Epsilon * Epsilon * Epsilon);
        transform.Rotate(quaternion);
        LOG_DEBUG("Rotation Quat ({},{},{},{}) == ({},{},{},{})", transform.GetRotation().w, transform.GetRotation().x, transform.GetRotation().y, transform.GetRotation().z, resultQuaternion.w, resultQuaternion.x, resultQuaternion.y, resultQuaternion.z);
        CHECK(glm::length(transform.GetRotation() - resultQuaternion) < Epsilon * Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Degrees ({},{},{}) == ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, resultAngleInDegrees.x, resultAngleInDegrees.y, resultAngleInDegrees.z);
        CHECK(glm::length(transform.GetRotationInDegrees() - resultAngleInDegrees) < Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Radians ({},{},{}) == ({},{},{})", transform.GetRotationInRadians().x, transform.GetRotationInRadians().y, transform.GetRotationInRadians().z, resultAngleInRadians.x, resultAngleInRadians.y, resultAngleInRadians.z);
        CHECK(glm::length(transform.GetRotationInRadians() - resultAngleInRadians) < Epsilon * Epsilon * Epsilon);
    }

    {
        Transform transform(glm::vec3(), startQuaternion);
        LOG_DEBUG("Rotation Quat ({},{},{},{}) == ({},{},{},{})", transform.GetRotation().w, transform.GetRotation().x, transform.GetRotation().y, transform.GetRotation().z, startQuaternion.w, startQuaternion.x, startQuaternion.y, startQuaternion.z);
        CHECK(glm::length(transform.GetRotation() - startQuaternion) < Epsilon * Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Degrees ({},{},{}) == ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, startAnglesInDegrees.x, startAnglesInDegrees.y, startAnglesInDegrees.z);
        CHECK(glm::length(transform.GetRotationInDegrees() - startAnglesInDegrees) < Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Radians ({},{},{}) == ({},{},{})", transform.GetRotationInRadians().x, transform.GetRotationInRadians().y, transform.GetRotationInRadians().z, startAnglesInRadians.x, startAnglesInRadians.y, startAnglesInRadians.z);
        CHECK(glm::length(transform.GetRotationInRadians() - startAnglesInRadians) < Epsilon * Epsilon * Epsilon);
        transform.Rotate(anglesInRadians);
        LOG_DEBUG("Rotation Quat ({},{},{},{}) == ({},{},{},{})", transform.GetRotation().w, transform.GetRotation().x, transform.GetRotation().y, transform.GetRotation().z, resultQuaternion.w, resultQuaternion.x, resultQuaternion.y, resultQuaternion.z);
        CHECK(glm::length(transform.GetRotation() - resultQuaternion) < Epsilon * Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Degrees ({},{},{}) == ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, resultAngleInDegrees.x, resultAngleInDegrees.y, resultAngleInDegrees.z);
        CHECK(glm::length(transform.GetRotationInDegrees() - resultAngleInDegrees) < Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Radians ({},{},{}) == ({},{},{})", transform.GetRotationInRadians().x, transform.GetRotationInRadians().y, transform.GetRotationInRadians().z, resultAngleInRadians.x, resultAngleInRadians.y, resultAngleInRadians.z);
        CHECK(glm::length(transform.GetRotationInRadians() - resultAngleInRadians) < Epsilon * Epsilon * Epsilon);
    }

    {
        Transform transform(glm::vec3(), startQuaternion);
        LOG_DEBUG("Rotation Quat ({},{},{},{}) == ({},{},{},{})", transform.GetRotation().w, transform.GetRotation().x, transform.GetRotation().y, transform.GetRotation().z, startQuaternion.w, startQuaternion.x, startQuaternion.y, startQuaternion.z);
        CHECK(glm::length(transform.GetRotation() - startQuaternion) < Epsilon * Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Degrees ({},{},{}) == ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, startAnglesInDegrees.x, startAnglesInDegrees.y, startAnglesInDegrees.z);
        CHECK(glm::length(transform.GetRotationInDegrees() - startAnglesInDegrees) < Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Radians ({},{},{}) == ({},{},{})", transform.GetRotationInRadians().x, transform.GetRotationInRadians().y, transform.GetRotationInRadians().z, startAnglesInRadians.x, startAnglesInRadians.y, startAnglesInRadians.z);
        CHECK(glm::length(transform.GetRotationInRadians() - startAnglesInRadians) < Epsilon * Epsilon * Epsilon);
        transform.Rotate(anglesInRadians.x, anglesInRadians.y, anglesInRadians.z);
        LOG_DEBUG("Rotation Quat ({},{},{},{}) == ({},{},{},{})", transform.GetRotation().w, transform.GetRotation().x, transform.GetRotation().y, transform.GetRotation().z, resultQuaternion.w, resultQuaternion.x, resultQuaternion.y, resultQuaternion.z);
        CHECK(glm::length(transform.GetRotation() - resultQuaternion) < Epsilon * Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Degrees ({},{},{}) == ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, resultAngleInDegrees.x, resultAngleInDegrees.y, resultAngleInDegrees.z);
        CHECK(glm::length(transform.GetRotationInDegrees() - resultAngleInDegrees) < Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Radians ({},{},{}) == ({},{},{})", transform.GetRotationInRadians().x, transform.GetRotationInRadians().y, transform.GetRotationInRadians().z, resultAngleInRadians.x, resultAngleInRadians.y, resultAngleInRadians.z);
        CHECK(glm::length(transform.GetRotationInRadians() - resultAngleInRadians) < Epsilon * Epsilon * Epsilon);
    }

    {
        Transform transform(glm::vec3(), startQuaternion);
        LOG_DEBUG("Rotation Quat ({},{},{},{}) == ({},{},{},{})", transform.GetRotation().w, transform.GetRotation().x, transform.GetRotation().y, transform.GetRotation().z, startQuaternion.w, startQuaternion.x, startQuaternion.y, startQuaternion.z);
        CHECK(glm::length(transform.GetRotation() - startQuaternion) < Epsilon * Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Degrees ({},{},{}) == ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, startAnglesInDegrees.x, startAnglesInDegrees.y, startAnglesInDegrees.z);
        CHECK(glm::length(transform.GetRotationInDegrees() - startAnglesInDegrees) < Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Radians ({},{},{}) == ({},{},{})", transform.GetRotationInRadians().x, transform.GetRotationInRadians().y, transform.GetRotationInRadians().z, startAnglesInRadians.x, startAnglesInRadians.y, startAnglesInRadians.z);
        CHECK(glm::length(transform.GetRotationInRadians() - startAnglesInRadians) < Epsilon * Epsilon * Epsilon);
        transform.RotateInDegrees(anglesInDegrees);
        LOG_DEBUG("Rotation Quat ({},{},{},{}) == ({},{},{},{})", transform.GetRotation().w, transform.GetRotation().x, transform.GetRotation().y, transform.GetRotation().z, resultQuaternion.w, resultQuaternion.x, resultQuaternion.y, resultQuaternion.z);
        CHECK(glm::length(transform.GetRotation() - resultQuaternion) < Epsilon * Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Degrees ({},{},{}) == ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, resultAngleInDegrees.x, resultAngleInDegrees.y, resultAngleInDegrees.z);
        CHECK(glm::length(transform.GetRotationInDegrees() - resultAngleInDegrees) < Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Radians ({},{},{}) == ({},{},{})", transform.GetRotationInRadians().x, transform.GetRotationInRadians().y, transform.GetRotationInRadians().z, resultAngleInRadians.x, resultAngleInRadians.y, resultAngleInRadians.z);
        CHECK(glm::length(transform.GetRotationInRadians() - resultAngleInRadians) < Epsilon * Epsilon * Epsilon);
    }

    {
        Transform transform(glm::vec3(), startQuaternion);
        LOG_DEBUG("Rotation Quat ({},{},{},{}) == ({},{},{},{})", transform.GetRotation().w, transform.GetRotation().x, transform.GetRotation().y, transform.GetRotation().z, startQuaternion.w, startQuaternion.x, startQuaternion.y, startQuaternion.z);
        CHECK(glm::length(transform.GetRotation() - startQuaternion) < Epsilon * Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Degrees ({},{},{}) == ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, startAnglesInDegrees.x, startAnglesInDegrees.y, startAnglesInDegrees.z);
        CHECK(glm::length(transform.GetRotationInDegrees() - startAnglesInDegrees) < Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Radians ({},{},{}) == ({},{},{})", transform.GetRotationInRadians().x, transform.GetRotationInRadians().y, transform.GetRotationInRadians().z, startAnglesInRadians.x, startAnglesInRadians.y, startAnglesInRadians.z);
        CHECK(glm::length(transform.GetRotationInRadians() - startAnglesInRadians) < Epsilon * Epsilon * Epsilon);
        transform.RotateInDegrees(anglesInDegrees.x, anglesInDegrees.y, anglesInDegrees.z);
        LOG_DEBUG("Rotation Quat ({},{},{},{}) == ({},{},{},{})", transform.GetRotation().w, transform.GetRotation().x, transform.GetRotation().y, transform.GetRotation().z, resultQuaternion.w, resultQuaternion.x, resultQuaternion.y, resultQuaternion.z);
        CHECK(glm::length(transform.GetRotation() - resultQuaternion) < Epsilon * Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Degrees ({},{},{}) == ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, resultAngleInDegrees.x, resultAngleInDegrees.y, resultAngleInDegrees.z);
        CHECK(glm::length(transform.GetRotationInDegrees() - resultAngleInDegrees) < Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Radians ({},{},{}) == ({},{},{})", transform.GetRotationInRadians().x, transform.GetRotationInRadians().y, transform.GetRotationInRadians().z, resultAngleInRadians.x, resultAngleInRadians.y, resultAngleInRadians.z);
        CHECK(glm::length(transform.GetRotationInRadians() - resultAngleInRadians) < Epsilon * Epsilon * Epsilon);
    }
}


/*
TEST_CASE("", "[Transform RotationInRotation and Rotate Functions Return Right Values]")
{
    glm::vec3 startAnglesInDegrees(30.0f, 0.0f, 0.0f);
    glm::vec3 startAnglesInRadians = glm::radians(startAnglesInDegrees);
    glm::quat startQuaternion(startAnglesInRadians);

    LOG_DEBUG("Start Quat ({},{},{},{})", startQuaternion.w, startQuaternion.x, startQuaternion.y, startQuaternion.z);
    LOG_DEBUG("Start Degrees ({},{},{})", startAnglesInDegrees.x, startAnglesInDegrees.y, startAnglesInDegrees.z);
    LOG_DEBUG("Start Radians ({},{},{})", startAnglesInRadians.x, startAnglesInRadians.y, startAnglesInRadians.z);

    glm::vec3 anglesInDegrees(0.0f, -180.0f, 0.0f);
    glm::vec3 anglesInRadians = glm::radians(anglesInDegrees);
    glm::quat quaternion(anglesInRadians);
    anglesInRadians = glm::eulerAngles(quaternion);
    anglesInDegrees = glm::degrees(anglesInRadians);

    LOG_DEBUG("Delta Quat ({},{},{},{})", quaternion.w, quaternion.x, quaternion.y, quaternion.z);
    LOG_DEBUG("Delta Degrees ({},{},{})", anglesInDegrees.x, anglesInDegrees.y, anglesInDegrees.z);
    LOG_DEBUG("Delta Radians ({},{},{})", anglesInRadians.x, anglesInRadians.y, anglesInRadians.z);

    glm::quat resultQuaternion = glm::normalize(quaternion) * glm::normalize(startQuaternion);
    glm::vec3 resultAngleInRadians = glm::eulerAngles(resultQuaternion);
    glm::vec3 resultAngleInDegrees = glm::degrees(resultAngleInRadians);

    LOG_DEBUG("Result Quat ({},{},{},{})", resultQuaternion.w, resultQuaternion.x, resultQuaternion.y, resultQuaternion.z);
    LOG_DEBUG("Result Degrees ({},{},{})", resultAngleInDegrees.x, resultAngleInDegrees.y, resultAngleInDegrees.z);
    LOG_DEBUG("Result Radians ({},{},{})", resultAngleInRadians.x, resultAngleInRadians.y, resultAngleInRadians.z);

    {
        Transform transform(glm::vec3(), startQuaternion);
        LOG_DEBUG("Rotation Quat ({},{},{},{}) == ({},{},{},{})", transform.GetRotation().w, transform.GetRotation().x, transform.GetRotation().y, transform.GetRotation().z, startQuaternion.w, startQuaternion.x, startQuaternion.y, startQuaternion.z);
        CHECK(glm::length(transform.GetRotation() - startQuaternion) < Epsilon * Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Degrees ({},{},{}) == ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, startAnglesInDegrees.x, startAnglesInDegrees.y, startAnglesInDegrees.z);
        CHECK(glm::length(transform.GetRotationInDegrees() - startAnglesInDegrees) < Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Radians ({},{},{}) == ({},{},{})", transform.GetRotationInRadians().x, transform.GetRotationInRadians().y, transform.GetRotationInRadians().z, startAnglesInRadians.x, startAnglesInRadians.y, startAnglesInRadians.z);
        CHECK(glm::length(transform.GetRotationInRadians() - startAnglesInRadians) < Epsilon * Epsilon * Epsilon);
        transform.RotateInOrientation(anglesInRadians);
        LOG_DEBUG("Rotation Quat ({},{},{},{}) == ({},{},{},{})", transform.GetRotation().w, transform.GetRotation().x, transform.GetRotation().y, transform.GetRotation().z, resultQuaternion.w, resultQuaternion.x, resultQuaternion.y, resultQuaternion.z);
        CHECK(glm::length(transform.GetRotation() - resultQuaternion) < Epsilon * Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Degrees ({},{},{}) == ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, resultAngleInDegrees.x, resultAngleInDegrees.y, resultAngleInDegrees.z);
        CHECK(glm::length(transform.GetRotationInDegrees() - resultAngleInDegrees) < Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Radians ({},{},{}) == ({},{},{})", transform.GetRotationInRadians().x, transform.GetRotationInRadians().y, transform.GetRotationInRadians().z, resultAngleInRadians.x, resultAngleInRadians.y, resultAngleInRadians.z);
        CHECK(glm::length(transform.GetRotationInRadians() - resultAngleInRadians) < Epsilon * Epsilon * Epsilon);
    }

    {
        Transform transform(glm::vec3(), startQuaternion);
        LOG_DEBUG("Rotation Quat ({},{},{},{}) == ({},{},{},{})", transform.GetRotation().w, transform.GetRotation().x, transform.GetRotation().y, transform.GetRotation().z, startQuaternion.w, startQuaternion.x, startQuaternion.y, startQuaternion.z);
        CHECK(glm::length(transform.GetRotation() - startQuaternion) < Epsilon * Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Degrees ({},{},{}) == ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, startAnglesInDegrees.x, startAnglesInDegrees.y, startAnglesInDegrees.z);
        CHECK(glm::length(transform.GetRotationInDegrees() - startAnglesInDegrees) < Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Radians ({},{},{}) == ({},{},{})", transform.GetRotationInRadians().x, transform.GetRotationInRadians().y, transform.GetRotationInRadians().z, startAnglesInRadians.x, startAnglesInRadians.y, startAnglesInRadians.z);
        CHECK(glm::length(transform.GetRotationInRadians() - startAnglesInRadians) < Epsilon * Epsilon * Epsilon);
        transform.RotateInOrientation(anglesInRadians.x, anglesInRadians.y, anglesInRadians.z);
        LOG_DEBUG("Rotation Quat ({},{},{},{}) == ({},{},{},{})", transform.GetRotation().w, transform.GetRotation().x, transform.GetRotation().y, transform.GetRotation().z, resultQuaternion.w, resultQuaternion.x, resultQuaternion.y, resultQuaternion.z);
        CHECK(glm::length(transform.GetRotation() - resultQuaternion) < Epsilon * Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Degrees ({},{},{}) == ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, resultAngleInDegrees.x, resultAngleInDegrees.y, resultAngleInDegrees.z);
        CHECK(glm::length(transform.GetRotationInDegrees() - resultAngleInDegrees) < Epsilon * Epsilon * Epsilon);
        LOG_DEBUG("Rotation Radians ({},{},{}) == ({},{},{})", transform.GetRotationInRadians().x, transform.GetRotationInRadians().y, transform.GetRotationInRadians().z, resultAngleInRadians.x, resultAngleInRadians.y, resultAngleInRadians.z);
        CHECK(glm::length(transform.GetRotationInRadians() - resultAngleInRadians) < Epsilon * Epsilon * Epsilon);
    }
}
*/

TEST_CASE("", "[Transform Rotation Loop Returns Right Values]")
{
    glm::quat startQuaternion(glm::vec3(glm::radians(30.0f), 0.0f, 0.0f));
    glm::vec3 startAnglesInRadians = glm::eulerAngles(startQuaternion);
    glm::vec3 startAnglesInDegrees = glm::degrees(startAnglesInRadians);

    LOG_DEBUG("Start Quat ({},{},{},{})", startQuaternion.w, startQuaternion.x, startQuaternion.y, startQuaternion.z);
    LOG_DEBUG("Start Degrees ({},{},{})", startAnglesInDegrees.x, startAnglesInDegrees.y, startAnglesInDegrees.z);
    LOG_DEBUG("Start Radians ({},{},{})", startAnglesInRadians.x, startAnglesInRadians.y, startAnglesInRadians.z);

    glm::quat quaternion(glm::vec3(0.0f, glm::radians(1.0f), 0.0f));
    glm::vec3 anglesInRadians = glm::eulerAngles(quaternion);
    glm::vec3 anglesInDegrees = glm::degrees(anglesInRadians);

    LOG_DEBUG("Delta Quat ({},{},{},{})", quaternion.w, quaternion.x, quaternion.y, quaternion.z);
    LOG_DEBUG("Delta Degrees ({},{},{})", anglesInDegrees.x, anglesInDegrees.y, anglesInDegrees.z);
    LOG_DEBUG("Delta Radians ({},{},{})", anglesInRadians.x, anglesInRadians.y, anglesInRadians.z);

    glm::vec3 resultAngleInDegrees(-150.0f, 0.0f, 0.0f);


    {
        Transform transform(glm::vec3(), startQuaternion);
        for (size_t i = 0; i < 180; ++i)
        {
            transform.Rotate(anglesInRadians);
            LOG_DEBUG("Rotation ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, resultAngleInDegrees.x, resultAngleInDegrees.y, resultAngleInDegrees.z);
        }
        LOG_INFO("Rotation Degrees ({},{},{}) == ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, resultAngleInDegrees.x, resultAngleInDegrees.y, resultAngleInDegrees.z);
        CHECK(glm::length(transform.GetRotationInDegrees() - resultAngleInDegrees) < Epsilon * Epsilon * Epsilon);
    }

    {
        Transform transform(glm::vec3(), startQuaternion);
        for (size_t i = 0; i < 180; ++i)
        {
            transform.RotateInDegrees(anglesInDegrees);
            LOG_DEBUG("Rotation ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, resultAngleInDegrees.x, resultAngleInDegrees.y, resultAngleInDegrees.z);
        }
        LOG_INFO("Rotation Degrees ({},{},{}) == ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, resultAngleInDegrees.x, resultAngleInDegrees.y, resultAngleInDegrees.z);
        CHECK(glm::length(transform.GetRotationInDegrees() - resultAngleInDegrees) < Epsilon * Epsilon * Epsilon);
    }

    {
        Transform transform(glm::vec3(), startQuaternion);
        for (size_t i = 0; i < 180; ++i)
        {
            transform.RotateInOrientation(anglesInRadians);
            LOG_DEBUG("Rotation ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, resultAngleInDegrees.x, resultAngleInDegrees.y, resultAngleInDegrees.z);
        }
        LOG_INFO("Rotation Degrees ({},{},{}) == ({},{},{})", transform.GetRotationInDegrees().x, transform.GetRotationInDegrees().y, transform.GetRotationInDegrees().z, resultAngleInDegrees.x, resultAngleInDegrees.y, resultAngleInDegrees.z);
        CHECK(glm::length(transform.GetRotationInDegrees() - resultAngleInDegrees) < Epsilon * Epsilon * Epsilon);
    }

}