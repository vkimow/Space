#pragma once

#include "Engine/Input/Elements/ElementsHeader.h"
#include <memory>
#include <unordered_map>
#include "GLFW/glfw3.h"

namespace Engine::Input
{
    class Scheme final
    {

        friend class InputModule;

    public:
        Scheme(GLFWwindow* window);
        Scheme(const Scheme &inputModule) = delete;
        Scheme(Scheme &&inputModule) = delete;
        Scheme &operator=(const Scheme &rhs) = delete;
        Scheme &operator=(Scheme &&rhs) = delete;
        ~Scheme();

    public:
        bool ContainsPressableKey(int key) const;
        PressableKey *const GetPressableKey(int key);
        PressableKey *const CreatePressableKey(int key);

        bool ContainsPressableMouse(int mouseButton) const;
        PressableMouse *const GetPressableMouse(int mouseButton);
        PressableMouse *const CreatePressableMouse(int mouseButton);

    public:
        DeltaPressable *const CreateDeltaPressable(Pressable *const positive, Pressable *const negative);
        DeltaPressable *const CreateDeltaPressable(int positiveKey, int negativeKey);

    public:
        VectorPressable *const CreateVectorPressable(Pressable *const xPositive, Pressable *const xNegative, Pressable *const yPositive, Pressable *const yNegative);
        VectorPressable *const CreateVectorPressable(DeltaPressable *const x, DeltaPressable *const y);
        VectorPressable *const CreateVectorPressable(int xPositiveKey, int xNegativeKey, int yPositiveKey, int yNegativeKey);
        VectorDelta     *const CreateVectorDelta(Delta *x, Delta *y);

    public:
        bool HasMouse() const;
        Mouse *const GetMouse();

    private:
        void UpdateBeforePolling();
        void UpdateAfterPolling();

    private:
        std::unordered_map<int, PressableKey *const> keys;
        std::unordered_map<int, PressableMouse *const> mouseButtons;
        std::vector<Delta *> deltas;
        std::vector<Vector *> vectors;
        Mouse *mouse;
        GLFWwindow *window;
        //VectorMouseScroll *const mouseScroll;

    private:
        PressableKey *const AddPressableKey(int key);
        PressableMouse *const AddPressableMouse(int key);
        DeltaPressable *const AddDeltaPressable(Pressable *const positive, Pressable *const negative);
        VectorPressable *const AddVectorPressable(Pressable *const xPositive, Pressable *const xNegative, Pressable *const yPositive, Pressable *const yNegative);
        VectorDelta *const AddVectorDelta(Delta *const x, Delta *const y);


        void RemovePressableKey(int key);
        void RemovePressableMouse(int mouseButton);
        void RemovePressableKey(PressableKey *const key);
        void RemovePressableMouse(PressableMouse *const mouseButton);
        void RemoveDelta(Delta *const delta);
        void RemoveVector(Vector *const vector);

        void ClearKeys();
        void ClearMouseButtons();
        void ClearDeltas();
        void ClearVectors();
        void ClearDevices();

        void ClearAll();

    };
}
