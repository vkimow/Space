#include <catch2/catch_test_macros.hpp>
#include "Engine/Tools/ToolsHeader.h"

#include <cstdint>

int voidFunctionInvokeCount;
int intFunctionInvokeCount;
int voidPtrFunctionInvokeCount;
int intPtrFunctionInvokeCount;

void VoidFunction() { ++voidFunctionInvokeCount; };
void IntFunction(int value) { ++intFunctionInvokeCount; };
void VoidPtrFunction(void *value) { ++voidPtrFunctionInvokeCount; };
void IntPtrFunction(int *value) { ++intPtrFunctionInvokeCount; };

void ClearInvokeCounters()
{
    voidFunctionInvokeCount = 0;
    intFunctionInvokeCount = 0;
    voidPtrFunctionInvokeCount = 0;
    intPtrFunctionInvokeCount = 0;
}

class Member
{
public:
    Member()
        : voidFunctionInvokeCount(0)
        , intFunctionInvokeCount(0)
        , voidPtrFunctionInvokeCount(0)
        , intPtrFunctionInvokeCount(0)
    {}

    void VoidFunction() { ++voidFunctionInvokeCount; };
    void IntFunction(int value) { ++intFunctionInvokeCount; };
    void VoidPtrFunction(void *value) { ++voidPtrFunctionInvokeCount; };
    void IntPtrFunction(int *value) { ++intPtrFunctionInvokeCount; };

    int voidFunctionInvokeCount;
    int intFunctionInvokeCount;
    int voidPtrFunctionInvokeCount;
    int intPtrFunctionInvokeCount;
};

TEST_CASE("Global Functions are constructed without throws", "[Global Functions Constructor]")
{
    REQUIRE_NOTHROW([&]() { Engine::Tools::Events::GlobalFunction<void> voidFunction(&VoidFunction); });
    REQUIRE_NOTHROW([&]() { Engine::Tools::Events::GlobalFunction<int> intFunction(&IntFunction); });
    REQUIRE_NOTHROW([&]() { Engine::Tools::Events::GlobalFunction<void *> voidPtrFunction(&VoidPtrFunction); });
    REQUIRE_NOTHROW([&]() { Engine::Tools::Events::GlobalFunction<int *> intPtrFunction(&IntPtrFunction); });
}

TEST_CASE("Global Functions are constructed two times in a row without throws", "[Global Functions Constructor Double]")
{
    REQUIRE_NOTHROW([&]()
    {
        Engine::Tools::Events::GlobalFunction<void> voidFunction(&VoidFunction);
        Engine::Tools::Events::GlobalFunction<void> voidFunction2(&VoidFunction);
    });
    REQUIRE_NOTHROW([&]()
    {
        Engine::Tools::Events::GlobalFunction<int> intFunction(&IntFunction);
        Engine::Tools::Events::GlobalFunction<int> intFunction2(&IntFunction);
    });
    REQUIRE_NOTHROW([&]()
    {
        Engine::Tools::Events::GlobalFunction<void *> voidPtrFunction(&VoidPtrFunction);
        Engine::Tools::Events::GlobalFunction<void *> voidPtrFunction2(&VoidPtrFunction);
    });
    REQUIRE_NOTHROW([&]()
    {
        Engine::Tools::Events::GlobalFunction<int *> intPtrFunction(&IntPtrFunction);
        Engine::Tools::Events::GlobalFunction<int *> intPtrFunction2(&IntPtrFunction);
    });
}

TEST_CASE("Global Functions are invoked without throws", "[Global Functions Invoke No Throw]")
{
    ClearInvokeCounters();
    Engine::Tools::Events::GlobalFunction<void> voidFunction(&VoidFunction);
    Engine::Tools::Events::GlobalFunction<int> intFunction(&IntFunction);
    Engine::Tools::Events::GlobalFunction<void *> voidPtrFunction(&VoidPtrFunction);
    Engine::Tools::Events::GlobalFunction<int *> intPtrFunction(&IntPtrFunction);

    REQUIRE_NOTHROW(voidFunction());
    REQUIRE_NOTHROW(intFunction(0));
    REQUIRE_NOTHROW(voidPtrFunction(nullptr));
    REQUIRE_NOTHROW(intPtrFunction(nullptr));
}

TEST_CASE("Global Functions are truly invoked", "[Global Functions Invoke Right Result]")
{
    ClearInvokeCounters();
    Engine::Tools::Events::GlobalFunction<void> voidFunction(&VoidFunction);
    voidFunction();
    Engine::Tools::Events::GlobalFunction<int> intFunction(&IntFunction);
    intFunction(0);
    Engine::Tools::Events::GlobalFunction<void *> voidPtrFunction(&VoidPtrFunction);
    voidPtrFunction(nullptr);
    Engine::Tools::Events::GlobalFunction<int *> intPtrFunction(&IntPtrFunction);
    intPtrFunction(nullptr);

    CHECK(voidFunctionInvokeCount == 1);
    CHECK(intFunctionInvokeCount == 1);
    CHECK(voidPtrFunctionInvokeCount == 1);
    CHECK(intPtrFunctionInvokeCount == 1);
}


TEST_CASE("Member Functions are constructed without throws", "[Member Functions Constructor]")
{
    Member member;
    REQUIRE_NOTHROW([&]() { Engine::Tools::Events::MemberFunction<Member, void> voidFunction(&member, &Member::VoidFunction); });
    REQUIRE_NOTHROW([&]() { Engine::Tools::Events::MemberFunction<Member, int> intFunction(&member, &Member::IntFunction); });
    REQUIRE_NOTHROW([&]() { Engine::Tools::Events::MemberFunction<Member, void *> voidPtrFunction(&member, &Member::VoidPtrFunction); });
    REQUIRE_NOTHROW([&]() { Engine::Tools::Events::MemberFunction<Member, int *> intPtrFunction(&member, &Member::IntPtrFunction); });
}

TEST_CASE("Member Functions are constructed two times in a row without throws", "[Member Functions Constructor Double]")
{
    Member member;
    REQUIRE_NOTHROW([&]()
    {
        Engine::Tools::Events::MemberFunction<Member, void> voidFunction(&member, &Member::VoidFunction);
        Engine::Tools::Events::MemberFunction<Member, void> voidFunction2(&member, &Member::VoidFunction);
    });
    REQUIRE_NOTHROW([&]()
    {
        Engine::Tools::Events::MemberFunction<Member, int> intFunction(&member, &Member::IntFunction);
        Engine::Tools::Events::MemberFunction<Member, int> intFunction2(&member, &Member::IntFunction);
    });
    REQUIRE_NOTHROW([&]()
    {
        Engine::Tools::Events::MemberFunction<Member, void *> voidPtrFunction(&member, &Member::VoidPtrFunction);
        Engine::Tools::Events::MemberFunction<Member, void *> voidPtrFunction2(&member, &Member::VoidPtrFunction);
    });
    REQUIRE_NOTHROW([&]()
    {
        Engine::Tools::Events::MemberFunction<Member, int *> intPtrFunction(&member, &Member::IntPtrFunction);
        Engine::Tools::Events::MemberFunction<Member, int *> intPtrFunction2(&member, &Member::IntPtrFunction);
    });
}

TEST_CASE("Member Functions are invoked without throws", "[Member Functions Invoke No Throw]")
{
    Member member;
    Engine::Tools::Events::MemberFunction<Member, void> voidFunction(&member, &Member::VoidFunction);
    Engine::Tools::Events::MemberFunction<Member, int> intFunction(&member, &Member::IntFunction);
    Engine::Tools::Events::MemberFunction<Member, void *> voidPtrFunction(&member, &Member::VoidPtrFunction);
    Engine::Tools::Events::MemberFunction<Member, int *> intPtrFunction(&member, &Member::IntPtrFunction);

    REQUIRE_NOTHROW(voidFunction());
    REQUIRE_NOTHROW(intFunction(0));
    REQUIRE_NOTHROW(voidPtrFunction(nullptr));
    REQUIRE_NOTHROW(intPtrFunction(nullptr));
}

TEST_CASE("Member Functions are invoked with right result", "[Member Functions Invoke Right Result]")
{
    Member member;
    Engine::Tools::Events::MemberFunction<Member, void> voidFunction(&member, &Member::VoidFunction);
    voidFunction();
    Engine::Tools::Events::MemberFunction<Member, int> intFunction(&member, &Member::IntFunction);
    intFunction(0);
    Engine::Tools::Events::MemberFunction<Member, void *> voidPtrFunction(&member, &Member::VoidPtrFunction);
    voidPtrFunction(nullptr);
    Engine::Tools::Events::MemberFunction<Member, int *> intPtrFunction(&member, &Member::IntPtrFunction);
    intPtrFunction(nullptr);

    CHECK(member.voidFunctionInvokeCount == 1);
    CHECK(member.intFunctionInvokeCount == 1);
    CHECK(member.voidPtrFunctionInvokeCount == 1);
    CHECK(member.intPtrFunctionInvokeCount == 1);
}

TEST_CASE("Actions are constructed without throws", "[Action Constructor ]")
{
    REQUIRE_NOTHROW([&]() { Engine::Tools::Events::Action<void>voidAction; });
    REQUIRE_NOTHROW([&]() { Engine::Tools::Events::Action<int>intAction; });
    REQUIRE_NOTHROW([&]() { Engine::Tools::Events::Action<void *>voidPtrAction; });
    REQUIRE_NOTHROW([&]() { Engine::Tools::Events::Action<int *>intPtrAction; });
}

TEST_CASE("Actions are invoked without throws", "[Action Invoke]")
{
    Engine::Tools::Events::Action<void>voidAction;
    Engine::Tools::Events::Action<int>intAction;
    Engine::Tools::Events::Action<void *>voidPtrAction;
    Engine::Tools::Events::Action<int *>intPtrAction;

    REQUIRE_NOTHROW(voidAction());
    REQUIRE_NOTHROW(intAction(0));
    REQUIRE_NOTHROW(voidPtrAction(nullptr));
    REQUIRE_NOTHROW(intPtrAction(nullptr));
}

TEST_CASE("Member Functions are added to Action Listener without throws", "[Action Add Member Function Listener]")
{
    Member member;

    Engine::Tools::Events::MemberFunction<Member, void> voidFunction(&member, &Member::VoidFunction);
    Engine::Tools::Events::Action<void>voidAction;
    REQUIRE_NOTHROW([&]() { voidAction += voidFunction; });

    Engine::Tools::Events::MemberFunction<Member, int> intFunction(&member, &Member::IntFunction);
    Engine::Tools::Events::Action<int>intAction;
    REQUIRE_NOTHROW([&]() { intAction += intFunction; });

    Engine::Tools::Events::MemberFunction<Member, void *> voidPtrFunction(&member, &Member::VoidPtrFunction);
    Engine::Tools::Events::Action<void *>voidPtrAction;
    REQUIRE_NOTHROW([&]() { voidPtrAction += voidPtrFunction; });

    Engine::Tools::Events::MemberFunction<Member, int *> intPtrFunction(&member, &Member::IntPtrFunction);
    Engine::Tools::Events::Action<int *>intPtrAction;
    REQUIRE_NOTHROW([&]() { intPtrAction += intPtrFunction; });
}

TEST_CASE("Actions with Member Functions are constructed without throws", "[Action Constructor With Member Function]")
{
    Member member;

    Engine::Tools::Events::MemberFunction<Member, void> voidFunction(&member, &Member::VoidFunction);
    REQUIRE_NOTHROW([&]() { Engine::Tools::Events::Action<void>voidAction(voidFunction); });

    Engine::Tools::Events::MemberFunction<Member, int> intFunction(&member, &Member::IntFunction);
    REQUIRE_NOTHROW([&]() { Engine::Tools::Events::Action<int>intAction(intFunction); });

    Engine::Tools::Events::MemberFunction<Member, void *> voidPtrFunction(&member, &Member::VoidPtrFunction);
    REQUIRE_NOTHROW([&]() { Engine::Tools::Events::Action<void *>voidPtrAction(voidPtrFunction); });

    Engine::Tools::Events::MemberFunction<Member, int *> intPtrFunction(&member, &Member::IntPtrFunction);
    REQUIRE_NOTHROW([&]() { Engine::Tools::Events::Action<int *>intPtrAction(intPtrFunction); });
}



TEST_CASE("Actions with Member Functions are invoked without throws", "[Action Invoke With Member Function No Trhow]")
{
    Member member;

    Engine::Tools::Events::MemberFunction<Member, void> voidFunction(&member, &Member::VoidFunction);
    Engine::Tools::Events::Action<void>voidAction(voidFunction);

    Engine::Tools::Events::MemberFunction<Member, int> intFunction(&member, &Member::IntFunction);
    Engine::Tools::Events::Action<int>intAction(intFunction);

    Engine::Tools::Events::MemberFunction<Member, void *> voidPtrFunction(&member, &Member::VoidPtrFunction);
    Engine::Tools::Events::Action<void *>voidPtrAction(voidPtrFunction);

    Engine::Tools::Events::MemberFunction<Member, int *> intPtrFunction(&member, &Member::IntPtrFunction);
    Engine::Tools::Events::Action<int *>intPtrAction(intPtrFunction);

    REQUIRE_NOTHROW(voidAction());
    REQUIRE_NOTHROW(intAction(0));
    REQUIRE_NOTHROW(voidPtrAction(nullptr));
    REQUIRE_NOTHROW(intPtrAction(nullptr));
}

TEST_CASE("Actions with Member Functions are invoked with right result", "[Action Invoke With Member Function Right Result]")
{
    Member member;

    Engine::Tools::Events::MemberFunction<Member, void> voidFunction(&member, &Member::VoidFunction);
    Engine::Tools::Events::Action<void>voidAction(voidFunction);

    Engine::Tools::Events::MemberFunction<Member, int> intFunction(&member, &Member::IntFunction);
    Engine::Tools::Events::Action<int>intAction(intFunction);

    Engine::Tools::Events::MemberFunction<Member, void *> voidPtrFunction(&member, &Member::VoidPtrFunction);
    Engine::Tools::Events::Action<void *>voidPtrAction(voidPtrFunction);

    Engine::Tools::Events::MemberFunction<Member, int *> intPtrFunction(&member, &Member::IntPtrFunction);
    Engine::Tools::Events::Action<int *>intPtrAction(intPtrFunction);

    voidAction();
    intAction(0);
    voidPtrAction(nullptr);
    intPtrAction(nullptr);

    CHECK(member.voidFunctionInvokeCount == 1);
    CHECK(member.intFunctionInvokeCount == 1);
    CHECK(member.voidPtrFunctionInvokeCount == 1);
    CHECK(member.intPtrFunctionInvokeCount == 1);
}


TEST_CASE("Global Functions are added to Action Listener without throws", "[Action Add Global Function Listener]")
{
    Engine::Tools::Events::GlobalFunction<void> voidFunction(&VoidFunction);
    Engine::Tools::Events::Action<void>voidAction;
    REQUIRE_NOTHROW([&]() { voidAction += voidFunction; });

    Engine::Tools::Events::GlobalFunction<int> intFunction(&IntFunction);
    Engine::Tools::Events::Action<int>intAction;
    REQUIRE_NOTHROW([&]() { intAction += intFunction; });

    Engine::Tools::Events::GlobalFunction<void*> voidPtrFunction(&VoidPtrFunction);
    Engine::Tools::Events::Action<void *>voidPtrAction;
    REQUIRE_NOTHROW([&]() { voidPtrAction += voidPtrFunction; });

    Engine::Tools::Events::GlobalFunction<int *> intPtrFunction(&IntPtrFunction);
    Engine::Tools::Events::Action<int *>intPtrAction;
    REQUIRE_NOTHROW([&]() { intPtrAction += intPtrFunction; });
}

TEST_CASE("Actions with Global Functions are constructed without throws", "[Action Constructor With Global Function]")
{
    Engine::Tools::Events::GlobalFunction<void> voidFunction(&VoidFunction);
    REQUIRE_NOTHROW([&]() { Engine::Tools::Events::Action<void>voidAction(voidFunction); });

    Engine::Tools::Events::GlobalFunction<int> intFunction(&IntFunction);
    REQUIRE_NOTHROW([&]() { Engine::Tools::Events::Action<int>intAction(intFunction); });

    Engine::Tools::Events::GlobalFunction<void *> voidPtrFunction(&VoidPtrFunction);
    REQUIRE_NOTHROW([&]() { Engine::Tools::Events::Action<void *>voidPtrAction(voidPtrFunction); });

    Engine::Tools::Events::GlobalFunction<int *> intPtrFunction(&IntPtrFunction);
    REQUIRE_NOTHROW([&]() { Engine::Tools::Events::Action<int *>intPtrAction(intPtrFunction); });
}



TEST_CASE("Actions with Global Functions are invoked without throws", "[Action Invoke With Global Function No Trhow]")
{
    Engine::Tools::Events::GlobalFunction<void> voidFunction(&VoidFunction);
    Engine::Tools::Events::Action<void>voidAction(voidFunction);

    Engine::Tools::Events::GlobalFunction<int> intFunction(&IntFunction);
    Engine::Tools::Events::Action<int>intAction(intFunction);

    Engine::Tools::Events::GlobalFunction<void *> voidPtrFunction(&VoidPtrFunction);
    Engine::Tools::Events::Action<void *>voidPtrAction(voidPtrFunction);

    Engine::Tools::Events::GlobalFunction<int *> intPtrFunction(&IntPtrFunction);
    Engine::Tools::Events::Action<int *>intPtrAction(intPtrFunction);

    REQUIRE_NOTHROW(voidAction());
    REQUIRE_NOTHROW(intAction(0));
    REQUIRE_NOTHROW(voidPtrAction(nullptr));
    REQUIRE_NOTHROW(intPtrAction(nullptr));
}

TEST_CASE("Actions with Global Functions are invoked with right result", "[Action Invoke With Global Function Right Result]")
{
    Engine::Tools::Events::GlobalFunction<void> voidFunction(&VoidFunction);
    Engine::Tools::Events::Action<void>voidAction(voidFunction);

    Engine::Tools::Events::GlobalFunction<int> intFunction(&IntFunction);
    Engine::Tools::Events::Action<int>intAction(intFunction);

    Engine::Tools::Events::GlobalFunction<void *> voidPtrFunction(&VoidPtrFunction);
    Engine::Tools::Events::Action<void *>voidPtrAction(voidPtrFunction);

    Engine::Tools::Events::GlobalFunction<int *> intPtrFunction(&IntPtrFunction);
    Engine::Tools::Events::Action<int *>intPtrAction(intPtrFunction);

    ClearInvokeCounters();
    voidAction();
    intAction(0);
    voidPtrAction(nullptr);
    intPtrAction(nullptr);

    CHECK(voidFunctionInvokeCount == 1);
    CHECK(intFunctionInvokeCount == 1);
    CHECK(voidPtrFunctionInvokeCount == 1);
    CHECK(intPtrFunctionInvokeCount == 1);
}

TEST_CASE("Actions are subscribed to antoher action and invoked with right result", "[Action Listen Another Action Right Result]")
{
    Engine::Tools::Events::GlobalFunction<void> voidFunction(&VoidFunction);
    Engine::Tools::Events::Action<void>voidAction;
    Engine::Tools::Events::Action<void>voidAction2;
    voidAction2 += &voidAction;
    voidAction += voidFunction;

    Engine::Tools::Events::GlobalFunction<int> intFunction(&IntFunction);
    Engine::Tools::Events::Action<int>intAction;
    Engine::Tools::Events::Action<int>intAction2;
    intAction2 += &intAction;
    intAction += intFunction;

    Engine::Tools::Events::GlobalFunction<void *> voidPtrFunction(&VoidPtrFunction);
    Engine::Tools::Events::Action<void *>voidPtrAction;
    Engine::Tools::Events::Action<void *>voidPtrAction2;
    voidPtrAction2 += &voidPtrAction;
    voidPtrAction += voidPtrFunction;

    Engine::Tools::Events::GlobalFunction<int *> intPtrFunction(&IntPtrFunction);
    Engine::Tools::Events::Action<int *>intPtrAction;
    Engine::Tools::Events::Action<int *>intPtrAction2;
    intPtrAction2 += &intPtrAction;
    intPtrAction += intPtrFunction;

    ClearInvokeCounters();
    voidAction2();
    intAction2(0);
    voidPtrAction2(nullptr);
    intPtrAction2(nullptr);

    CHECK(voidFunctionInvokeCount == 1);
    CHECK(intFunctionInvokeCount == 1);
    CHECK(voidPtrFunctionInvokeCount == 1);
    CHECK(intPtrFunctionInvokeCount == 1);
}