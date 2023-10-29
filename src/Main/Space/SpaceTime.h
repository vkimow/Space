#pragma once

namespace Main::Space
{
    class SpaceTime
    {
        friend class SpaceManager;

    private:
        SpaceTime();
        SpaceTime(const SpaceTime &rhs) = delete;
        SpaceTime(SpaceTime &&rhs) = delete;
        SpaceTime &operator=(const SpaceTime &rhs) = delete;
        SpaceTime &operator=(SpaceTime &&rhs) = delete;
        ~SpaceTime();

    private:
        void Update();

    public:
        void SetTimeCoef(float value);
        float GetTimeCoef() const;
        float GetDeltaTime() const;
        float GetGlobalTime() const;

    private:
        float timeCoef;
        float deltaTime;
        float globalTime;
    };
}