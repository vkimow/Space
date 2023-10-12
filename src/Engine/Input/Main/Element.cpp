#include "Engine/Input/Main/Element.h"

namespace Engine::Input
{
    Element::Element()
        : isActive(true)
    {}

    Element::~Element()
    {}

    void Element::SetActive(bool value)
    {
        isActive = value;
    }
}
