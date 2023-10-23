#include "Engine/Input/Main/Scheme.h"

namespace Engine::Input
{
    Scheme::Scheme(GLFWwindow *window)
        : window(window)
        , keys()
        , mouseButtons()
        , deltas()
        , vectors()
        , mouse(nullptr)
    {}

    bool Scheme::ContainsPressableKey(int key) const
    {
        return keys.find(key) != keys.end();
    }

    PressableKey *const Scheme::GetPressableKey(int key)
    {
        auto element = keys.find(key);
        if (element == keys.end())
        {
            return nullptr;
        }

        return element->second;
    }

    PressableKey *const Scheme::CreatePressableKey(int key)
    {
        auto oldPressable = keys.find(key);
        if (oldPressable == keys.end())
        {
            return AddPressableKey(key);
        }
        else
        {
            return oldPressable->second;
        }
    }

    bool Scheme::ContainsPressableMouse(int mouseButton) const
    {
        return mouseButtons.find(mouseButton) != mouseButtons.end();
    }

    PressableMouse *const Scheme::GetPressableMouse(int mouseButton)
    {
        auto element = mouseButtons.find(mouseButton);
        if (element == mouseButtons.end())
        {
            return nullptr;
        }

        return element->second;
    }

    PressableMouse *const Scheme::CreatePressableMouse(int mouseButton)
    {
        auto oldPressable = mouseButtons.find(mouseButton);
        if (oldPressable == mouseButtons.end())
        {
            return AddPressableMouse(mouseButton);
        }
        else
        {
            return oldPressable->second;
        }
    }

    DeltaPressable *const Scheme::CreateDeltaPressable(Pressable *const positive, Pressable *const negative)
    {
        return AddDeltaPressable(positive, negative);
    }

    DeltaPressable *const Scheme::CreateDeltaPressable(int positiveKey, int negativeKey)
    {
        Pressable *const positivePressable = CreatePressableKey(positiveKey);
        Pressable *const negativePressable = CreatePressableKey(negativeKey);
        return AddDeltaPressable(positivePressable, negativePressable);
    }

    VectorPressable *const Scheme::CreateVectorPressable(Pressable *const xPositive, Pressable *const xNegative, Pressable *const yPositive, Pressable *const yNegative)
    {
        return AddVectorPressable(xPositive, xNegative, yPositive, yNegative);
    }

    VectorPressable *const Scheme::CreateVectorPressable(DeltaPressable *const x, DeltaPressable *const y)
    {
        return AddVectorPressable(x->positive, x->negative, y->positive, y->negative);
    }

    VectorPressable *const Scheme::CreateVectorPressable(int xPositiveKey, int xNegativeKey, int yPositiveKey, int yNegativeKey)
    {
        Pressable *const xPositivePressable = CreatePressableKey(xPositiveKey);
        Pressable *const xNegativePressable = CreatePressableKey(xNegativeKey);
        Pressable *const yPositivePressable = CreatePressableKey(yPositiveKey);
        Pressable *const yNegativePressable = CreatePressableKey(yNegativeKey);
        return AddVectorPressable(xPositivePressable, xNegativePressable, yPositivePressable, yNegativePressable);
    }

    bool Scheme::HasMouse() const
    {
        return mouse != nullptr;
    }

    Mouse *const Scheme::GetMouse()
    {
        if (!HasMouse())
        {
            mouse = new Mouse(window);
        }

        return mouse;
    }

    void Scheme::UpdateBeforePolling()
    {}

    void Scheme::UpdateAfterPolling()
    {}

    void Scheme::LateUpdate()
    {
        if (HasMouse())
        {
            mouse->ClearDelta();
        }
    }

    PressableKey *const Scheme::AddPressableKey(int key)
    {
        PressableKey* newPressable = new PressableKey(key);
        keys.insert(std::pair(key, newPressable));
        return newPressable;
    }

    PressableMouse *const Scheme::AddPressableMouse(int mouseButton)
    {
        PressableMouse *newPressable = new PressableMouse(mouseButton);
        mouseButtons.insert(std::pair(mouseButton, newPressable));
        return newPressable;
    }

    DeltaPressable *const Scheme::AddDeltaPressable(Pressable *const positive, Pressable *const negative)
    {
        DeltaPressable *delta = new DeltaPressable(positive, negative);
        deltas.push_back(delta);
        return delta;
    }

    VectorPressable *const Scheme::AddVectorPressable(Pressable *const xPositive, Pressable *const xNegative, Pressable *const yPositive, Pressable *const yNegative)
    {
        VectorPressable *vector = new VectorPressable(xPositive, xNegative, yPositive, yNegative);
        vectors.push_back(vector);
        return vector;
    }

    void Scheme::RemovePressableKey(int key)
    {
        delete keys.at(key);
        keys.erase(key);
    }

    void Scheme::RemovePressableMouse(int mouseButton)
    {
        delete mouseButtons.at(mouseButton);
        mouseButtons.erase(mouseButton);
    }

    void Scheme::RemovePressableKey(PressableKey *const key)
    {
        RemovePressableKey(key->GetKeyCode());
    }

    void Scheme::RemovePressableMouse(PressableMouse *const mouseButton)
    {
        RemovePressableMouse(mouseButton->GetButtonCode());
    }

    void Scheme::RemoveDelta(Delta *const delta)
    {
        delete delta;
        deltas.erase(std::remove(deltas.begin(), deltas.end(), delta));
    }

    void Scheme::RemoveVector(Vector *const vector)
    {
        delete vector;
        vectors.erase(std::remove(vectors.begin(), vectors.end(), vector));
    }

    void Scheme::ClearDeltas()
    {
        for (auto it = deltas.begin(); it != deltas.end(); ++it)
        {
            delete *it;
        }
        deltas.clear();
    }

    void Scheme::ClearVectors()
    {
        for (auto it = vectors.begin(); it != vectors.end(); ++it)
        {
            delete *it;
        }
        vectors.clear();
    }

    void Scheme::ClearDevices()
    {
        if (HasMouse())
        {
            delete mouse;
        }
    }

    void Scheme::ClearKeys()
    {
        for (auto it = keys.begin(); it != keys.end(); ++it)
        {
            delete it->second;
        }
        keys.clear();
    }

    void Scheme::ClearMouseButtons()
    {
        for (auto it = mouseButtons.begin(); it != mouseButtons.end(); ++it)
        {
            delete it->second;
        }
        mouseButtons.clear();
    }

    void Scheme::ClearAll()
    {
        ClearDevices();
        ClearVectors();
        ClearDeltas();
        ClearKeys();
        ClearMouseButtons();
    }

    Scheme::~Scheme()
    {
        ClearAll();
    }
}


