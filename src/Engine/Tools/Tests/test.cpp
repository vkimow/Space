#include <catch2/catch_test_macros.hpp>
#include "Engine/Tools/ToolsHeader.h"

#include <cstdint>

namespace Engine::Tools
{

    namespace Events
    {
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
            REQUIRE_NOTHROW([&]() { GlobalFunction<void> voidFunction(&VoidFunction); });
            REQUIRE_NOTHROW([&]() { GlobalFunction<int> intFunction(&IntFunction); });
            REQUIRE_NOTHROW([&]() { GlobalFunction<void *> voidPtrFunction(&VoidPtrFunction); });
            REQUIRE_NOTHROW([&]() { GlobalFunction<int *> intPtrFunction(&IntPtrFunction); });
        }

        TEST_CASE("Global Functions are constructed two times in a row without throws", "[Global Functions Constructor Double]")
        {
            REQUIRE_NOTHROW([&]()
            {
                GlobalFunction<void> voidFunction(&VoidFunction);
                GlobalFunction<void> voidFunction2(&VoidFunction);
            });
            REQUIRE_NOTHROW([&]()
            {
                GlobalFunction<int> intFunction(&IntFunction);
                GlobalFunction<int> intFunction2(&IntFunction);
            });
            REQUIRE_NOTHROW([&]()
            {
                GlobalFunction<void *> voidPtrFunction(&VoidPtrFunction);
                GlobalFunction<void *> voidPtrFunction2(&VoidPtrFunction);
            });
            REQUIRE_NOTHROW([&]()
            {
                GlobalFunction<int *> intPtrFunction(&IntPtrFunction);
                GlobalFunction<int *> intPtrFunction2(&IntPtrFunction);
            });
        }

        TEST_CASE("Global Functions are invoked without throws", "[Global Functions Invoke No Throw]")
        {
            ClearInvokeCounters();
            GlobalFunction<void> voidFunction(&VoidFunction);
            GlobalFunction<int> intFunction(&IntFunction);
            GlobalFunction<void *> voidPtrFunction(&VoidPtrFunction);
            GlobalFunction<int *> intPtrFunction(&IntPtrFunction);

            REQUIRE_NOTHROW(voidFunction());
            REQUIRE_NOTHROW(intFunction(0));
            REQUIRE_NOTHROW(voidPtrFunction(nullptr));
            REQUIRE_NOTHROW(intPtrFunction(nullptr));
        }

        TEST_CASE("Global Functions are truly invoked", "[Global Functions Invoke Right Result]")
        {
            ClearInvokeCounters();
            GlobalFunction<void> voidFunction(&VoidFunction);
            voidFunction();
            GlobalFunction<int> intFunction(&IntFunction);
            intFunction(0);
            GlobalFunction<void *> voidPtrFunction(&VoidPtrFunction);
            voidPtrFunction(nullptr);
            GlobalFunction<int *> intPtrFunction(&IntPtrFunction);
            intPtrFunction(nullptr);

            CHECK(voidFunctionInvokeCount == 1);
            CHECK(intFunctionInvokeCount == 1);
            CHECK(voidPtrFunctionInvokeCount == 1);
            CHECK(intPtrFunctionInvokeCount == 1);
        }


        TEST_CASE("Member Functions are constructed without throws", "[Member Functions Constructor]")
        {
            Member member;
            REQUIRE_NOTHROW([&]() { MemberFunction<Member, void> voidFunction(&member, &Member::VoidFunction); });
            REQUIRE_NOTHROW([&]() { MemberFunction<Member, int> intFunction(&member, &Member::IntFunction); });
            REQUIRE_NOTHROW([&]() { MemberFunction<Member, void *> voidPtrFunction(&member, &Member::VoidPtrFunction); });
            REQUIRE_NOTHROW([&]() { MemberFunction<Member, int *> intPtrFunction(&member, &Member::IntPtrFunction); });
        }

        TEST_CASE("Member Functions are constructed two times in a row without throws", "[Member Functions Constructor Double]")
        {
            Member member;
            REQUIRE_NOTHROW([&]()
            {
                MemberFunction<Member, void> voidFunction(&member, &Member::VoidFunction);
                MemberFunction<Member, void> voidFunction2(&member, &Member::VoidFunction);
            });
            REQUIRE_NOTHROW([&]()
            {
                MemberFunction<Member, int> intFunction(&member, &Member::IntFunction);
                MemberFunction<Member, int> intFunction2(&member, &Member::IntFunction);
            });
            REQUIRE_NOTHROW([&]()
            {
                MemberFunction<Member, void *> voidPtrFunction(&member, &Member::VoidPtrFunction);
                MemberFunction<Member, void *> voidPtrFunction2(&member, &Member::VoidPtrFunction);
            });
            REQUIRE_NOTHROW([&]()
            {
                MemberFunction<Member, int *> intPtrFunction(&member, &Member::IntPtrFunction);
                MemberFunction<Member, int *> intPtrFunction2(&member, &Member::IntPtrFunction);
            });
        }

        TEST_CASE("Member Functions are invoked without throws", "[Member Functions Invoke No Throw]")
        {
            Member member;
            MemberFunction<Member, void> voidFunction(&member, &Member::VoidFunction);
            MemberFunction<Member, int> intFunction(&member, &Member::IntFunction);
            MemberFunction<Member, void *> voidPtrFunction(&member, &Member::VoidPtrFunction);
            MemberFunction<Member, int *> intPtrFunction(&member, &Member::IntPtrFunction);

            REQUIRE_NOTHROW(voidFunction());
            REQUIRE_NOTHROW(intFunction(0));
            REQUIRE_NOTHROW(voidPtrFunction(nullptr));
            REQUIRE_NOTHROW(intPtrFunction(nullptr));
        }

        TEST_CASE("Member Functions are invoked with right result", "[Member Functions Invoke Right Result]")
        {
            Member member;
            MemberFunction<Member, void> voidFunction(&member, &Member::VoidFunction);
            voidFunction();
            MemberFunction<Member, int> intFunction(&member, &Member::IntFunction);
            intFunction(0);
            MemberFunction<Member, void *> voidPtrFunction(&member, &Member::VoidPtrFunction);
            voidPtrFunction(nullptr);
            MemberFunction<Member, int *> intPtrFunction(&member, &Member::IntPtrFunction);
            intPtrFunction(nullptr);

            CHECK(member.voidFunctionInvokeCount == 1);
            CHECK(member.intFunctionInvokeCount == 1);
            CHECK(member.voidPtrFunctionInvokeCount == 1);
            CHECK(member.intPtrFunctionInvokeCount == 1);
        }

        TEST_CASE("Actions are constructed without throws", "[Action Constructor ]")
        {
            REQUIRE_NOTHROW([&]() { Action<void>voidAction; });
            REQUIRE_NOTHROW([&]() { Action<int>intAction; });
            REQUIRE_NOTHROW([&]() { Action<void *>voidPtrAction; });
            REQUIRE_NOTHROW([&]() { Action<int *>intPtrAction; });
        }

        TEST_CASE("Actions are invoked without throws", "[Action Invoke]")
        {
            Action<void>voidAction;
            Action<int>intAction;
            Action<void *>voidPtrAction;
            Action<int *>intPtrAction;

            REQUIRE_NOTHROW(voidAction());
            REQUIRE_NOTHROW(intAction(0));
            REQUIRE_NOTHROW(voidPtrAction(nullptr));
            REQUIRE_NOTHROW(intPtrAction(nullptr));
        }

        TEST_CASE("Member Functions are added to Action Listener without throws", "[Action Add Member Function Listener]")
        {
            Member member;

            MemberFunction<Member, void> voidFunction(&member, &Member::VoidFunction);
            Action<void>voidAction;
            REQUIRE_NOTHROW([&]() { voidAction += voidFunction; });

            MemberFunction<Member, int> intFunction(&member, &Member::IntFunction);
            Action<int>intAction;
            REQUIRE_NOTHROW([&]() { intAction += intFunction; });

            MemberFunction<Member, void *> voidPtrFunction(&member, &Member::VoidPtrFunction);
            Action<void *>voidPtrAction;
            REQUIRE_NOTHROW([&]() { voidPtrAction += voidPtrFunction; });

            MemberFunction<Member, int *> intPtrFunction(&member, &Member::IntPtrFunction);
            Action<int *>intPtrAction;
            REQUIRE_NOTHROW([&]() { intPtrAction += intPtrFunction; });
        }

        TEST_CASE("Actions with Member Functions are constructed without throws", "[Action Constructor With Member Function]")
        {
            Member member;

            MemberFunction<Member, void> voidFunction(&member, &Member::VoidFunction);
            REQUIRE_NOTHROW([&]() { Action<void>voidAction(voidFunction); });

            MemberFunction<Member, int> intFunction(&member, &Member::IntFunction);
            REQUIRE_NOTHROW([&]() { Action<int>intAction(intFunction); });

            MemberFunction<Member, void *> voidPtrFunction(&member, &Member::VoidPtrFunction);
            REQUIRE_NOTHROW([&]() { Action<void *>voidPtrAction(voidPtrFunction); });

            MemberFunction<Member, int *> intPtrFunction(&member, &Member::IntPtrFunction);
            REQUIRE_NOTHROW([&]() { Action<int *>intPtrAction(intPtrFunction); });
        }



        TEST_CASE("Actions with Member Functions are invoked without throws", "[Action Invoke With Member Function No Trhow]")
        {
            Member member;

            MemberFunction<Member, void> voidFunction(&member, &Member::VoidFunction);
            Action<void>voidAction(voidFunction);

            MemberFunction<Member, int> intFunction(&member, &Member::IntFunction);
            Action<int>intAction(intFunction);

            MemberFunction<Member, void *> voidPtrFunction(&member, &Member::VoidPtrFunction);
            Action<void *>voidPtrAction(voidPtrFunction);

            MemberFunction<Member, int *> intPtrFunction(&member, &Member::IntPtrFunction);
            Action<int *>intPtrAction(intPtrFunction);

            REQUIRE_NOTHROW(voidAction());
            REQUIRE_NOTHROW(intAction(0));
            REQUIRE_NOTHROW(voidPtrAction(nullptr));
            REQUIRE_NOTHROW(intPtrAction(nullptr));
        }

        TEST_CASE("Actions with Member Functions are invoked with right result", "[Action Invoke With Member Function Right Result]")
        {
            Member member;

            MemberFunction<Member, void> voidFunction(&member, &Member::VoidFunction);
            Action<void>voidAction(voidFunction);

            MemberFunction<Member, int> intFunction(&member, &Member::IntFunction);
            Action<int>intAction(intFunction);

            MemberFunction<Member, void *> voidPtrFunction(&member, &Member::VoidPtrFunction);
            Action<void *>voidPtrAction(voidPtrFunction);

            MemberFunction<Member, int *> intPtrFunction(&member, &Member::IntPtrFunction);
            Action<int *>intPtrAction(intPtrFunction);

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
            GlobalFunction<void> voidFunction(&VoidFunction);
            Action<void>voidAction;
            REQUIRE_NOTHROW([&]() { voidAction += voidFunction; });

            GlobalFunction<int> intFunction(&IntFunction);
            Action<int>intAction;
            REQUIRE_NOTHROW([&]() { intAction += intFunction; });

            GlobalFunction<void *> voidPtrFunction(&VoidPtrFunction);
            Action<void *>voidPtrAction;
            REQUIRE_NOTHROW([&]() { voidPtrAction += voidPtrFunction; });

            GlobalFunction<int *> intPtrFunction(&IntPtrFunction);
            Action<int *>intPtrAction;
            REQUIRE_NOTHROW([&]() { intPtrAction += intPtrFunction; });
        }

        TEST_CASE("Actions with Global Functions are constructed without throws", "[Action Constructor With Global Function]")
        {
            GlobalFunction<void> voidFunction(&VoidFunction);
            REQUIRE_NOTHROW([&]() { Action<void>voidAction(voidFunction); });

            GlobalFunction<int> intFunction(&IntFunction);
            REQUIRE_NOTHROW([&]() { Action<int>intAction(intFunction); });

            GlobalFunction<void *> voidPtrFunction(&VoidPtrFunction);
            REQUIRE_NOTHROW([&]() { Action<void *>voidPtrAction(voidPtrFunction); });

            GlobalFunction<int *> intPtrFunction(&IntPtrFunction);
            REQUIRE_NOTHROW([&]() { Action<int *>intPtrAction(intPtrFunction); });
        }



        TEST_CASE("Actions with Global Functions are invoked without throws", "[Action Invoke With Global Function No Trhow]")
        {
            GlobalFunction<void> voidFunction(&VoidFunction);
            Action<void>voidAction(voidFunction);

            GlobalFunction<int> intFunction(&IntFunction);
            Action<int>intAction(intFunction);

            GlobalFunction<void *> voidPtrFunction(&VoidPtrFunction);
            Action<void *>voidPtrAction(voidPtrFunction);

            GlobalFunction<int *> intPtrFunction(&IntPtrFunction);
            Action<int *>intPtrAction(intPtrFunction);

            REQUIRE_NOTHROW(voidAction());
            REQUIRE_NOTHROW(intAction(0));
            REQUIRE_NOTHROW(voidPtrAction(nullptr));
            REQUIRE_NOTHROW(intPtrAction(nullptr));
        }

        TEST_CASE("Actions with Global Functions are invoked with right result", "[Action Invoke With Global Function Right Result]")
        {
            GlobalFunction<void> voidFunction(&VoidFunction);
            Action<void>voidAction(voidFunction);

            GlobalFunction<int> intFunction(&IntFunction);
            Action<int>intAction(intFunction);

            GlobalFunction<void *> voidPtrFunction(&VoidPtrFunction);
            Action<void *>voidPtrAction(voidPtrFunction);

            GlobalFunction<int *> intPtrFunction(&IntPtrFunction);
            Action<int *>intPtrAction(intPtrFunction);

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
            GlobalFunction<void> voidFunction(&VoidFunction);
            Action<void>voidAction;
            Action<void>voidAction2;
            voidAction2 += &voidAction;
            voidAction += voidFunction;

            GlobalFunction<int> intFunction(&IntFunction);
            Action<int>intAction;
            Action<int>intAction2;
            intAction2 += &intAction;
            intAction += intFunction;

            GlobalFunction<void *> voidPtrFunction(&VoidPtrFunction);
            Action<void *>voidPtrAction;
            Action<void *>voidPtrAction2;
            voidPtrAction2 += &voidPtrAction;
            voidPtrAction += voidPtrFunction;

            GlobalFunction<int *> intPtrFunction(&IntPtrFunction);
            Action<int *>intPtrAction;
            Action<int *>intPtrAction2;
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
    }

    namespace Structs
    {

        class ABase {};
        class A1 : public ABase {};
        class A2 : public ABase {};
        class A3 : public ABase {};
        class A4 : public ABase {};
        class A5 : public ABase {};
        class A6 : public ABase {};
        class A7 : public ABase {};
        class A8 : public ABase {};

        TEST_CASE("Actions are subscribed to antoher action and invoked with right result", "[MapWithPriority Constructor]")
        {
            MapWithPriority<int, int> intToInt;
        }

        TEST_CASE("Actions are subscribed to antoher action and invoked with right result", "[MapWithPriority Adding Without Error]")
        {
            MapWithPriority<int, int> intToInt;
            REQUIRE_NOTHROW(intToInt.Emplace(0, 0, 4));
            REQUIRE_NOTHROW(intToInt.Emplace(1, 1, 5));
            REQUIRE_NOTHROW(intToInt.Emplace(2, 2, 6));
            REQUIRE_NOTHROW(intToInt.Emplace(3, 3, 7));
            REQUIRE_NOTHROW(intToInt.Emplace(4, 4, 0));
            REQUIRE_NOTHROW(intToInt.Emplace(5, 5, 1));
            REQUIRE_NOTHROW(intToInt.Emplace(6, 6, 2));
            REQUIRE_NOTHROW(intToInt.Emplace(7, 7, 3));
        }

        TEST_CASE("Actions are subscribed to antoher action and invoked with right result", "[MapWithPriority Adding Expecting Right Result]")
        {
            MapWithPriority<int, int> intToInt;
            intToInt.Emplace(0, 4, 0);
            intToInt.Emplace(1, 5, 1);
            intToInt.Emplace(2, 6, 2);
            intToInt.Emplace(3, 7, 3);
            intToInt.Emplace(4, 0, 4);
            intToInt.Emplace(5, 1, 5);
            intToInt.Emplace(6, 2, 6);
            intToInt.Emplace(7, 3, 7);

            size_t index = 0;
            for (const auto& element : intToInt)
            {
                CHECK(element.priority == index);
                CHECK(element.key == (index + 4) % 8);
                CHECK((*element.element) == (index + 4) % 8);
                ++index;
            }
        }

        TEST_CASE("Actions are subscribed to antoher action and invoked with right result", "[MapWithPriority SetPriority Expecting Right Result]")
        {
            MapWithPriority<int, int> intToInt;
            intToInt.Emplace(0, 0, 0);
            intToInt.Emplace(1, 1, 1);
            intToInt.Emplace(2, 2, 2);
            intToInt.Emplace(3, 3, 3);
            intToInt.Emplace(4, 4, 4);
            intToInt.Emplace(5, 5, 5);
            intToInt.Emplace(6, 6, 6);
            intToInt.Emplace(7, 7, 7);

            intToInt.SetPriority(0, 4);
            intToInt.SetPriority(1, 5);
            intToInt.SetPriority(2, 6);
            intToInt.SetPriority(3, 7);
            intToInt.SetPriority(4, 0);
            intToInt.SetPriority(5, 1);
            intToInt.SetPriority(6, 2);
            intToInt.SetPriority(7, 3);

            size_t index = 0;
            for (const auto &element : intToInt)
            {
                CHECK(element.priority == index);
                CHECK(element.key == (index + 4) % 8);
                CHECK((*element.element) == (index + 4) % 8);
                ++index;
            }
        }

        TEST_CASE("Actions are subscribed to antoher action and invoked with right result", "[MapWithPriority Remove Expecting Right Result]")
        {
            MapWithPriority<int, int> intToInt;
            intToInt.Emplace(0, 4, 0);
            intToInt.Emplace(1, 5, 1);
            intToInt.Emplace(2, 6, 2);
            intToInt.Emplace(3, 7, 3);
            intToInt.Emplace(4, 0, 4);
            intToInt.Emplace(5, 1, 5);
            intToInt.Emplace(6, 2, 6);
            intToInt.Emplace(7, 3, 7);
            intToInt.Emplace(8, 0, 8);
            intToInt.Emplace(9, 1, 9);
            intToInt.Emplace(10, 2, 10);
            intToInt.Emplace(11, 3, 11);
            intToInt.Emplace(12, 4, 12);
            intToInt.Emplace(13, 5, 13);
            intToInt.Emplace(14, 6, 14);
            intToInt.Emplace(15, 7, 15);

            intToInt.Remove(8);
            intToInt.Remove(9);
            intToInt.Remove(10);
            intToInt.Remove(11);
            intToInt.Remove(12);
            intToInt.Remove(13);
            intToInt.Remove(14);
            intToInt.Remove(15);

            size_t index = 0;
            for (const auto &element : intToInt)
            {
                CHECK(element.priority == index);
                CHECK(element.key == (index + 4) % 8);
                CHECK((*element.element) == (index + 4) % 8);
                ++index;
            }
        }

        TEST_CASE("Actions are subscribed to antoher action and invoked with right result", "[TypeMapWithPriority Constructor]")
        {
            TypeMapWithPriority<ABase> typeMap;
        }

        TEST_CASE("Actions are subscribed to antoher action and invoked with right result", "[TypeMapWithPriority Adding Without Error]")
        {
            TypeMapWithPriority<ABase> typeMap;
            REQUIRE_NOTHROW(typeMap.Emplace<A1>(4));
            REQUIRE_NOTHROW(typeMap.Emplace<A2>(5));
            REQUIRE_NOTHROW(typeMap.Emplace<A3>(6));
            REQUIRE_NOTHROW(typeMap.Emplace<A4>(7));
            REQUIRE_NOTHROW(typeMap.Emplace<A5>(0));
            REQUIRE_NOTHROW(typeMap.Emplace<A6>(1));
            REQUIRE_NOTHROW(typeMap.Emplace<A7>(2));
            REQUIRE_NOTHROW(typeMap.Emplace<A8>(3));
        }

        TEST_CASE("Actions are subscribed to antoher action and invoked with right result", "[TypeMapWithPriority Adding Expecting Right Result]")
        {
            TypeMapWithPriority<ABase> typeMap;
            auto a1 = typeMap.Emplace<A1>(4);
            auto a2 = typeMap.Emplace<A2>(5);
            auto a3 = typeMap.Emplace<A3>(6);
            auto a4 = typeMap.Emplace<A4>(7);
            auto a5 = typeMap.Emplace<A5>(0);
            auto a6 = typeMap.Emplace<A6>(1);
            auto a7 = typeMap.Emplace<A7>(2);
            auto a8 = typeMap.Emplace<A8>(3);

            std::vector<ABase *> elements = {a5, a6, a7, a8, a1, a2, a3, a4};
            size_t index = 0;
            for (const auto &element : typeMap)
            {
                CHECK(element.priority == index);
                CHECK(element.element == elements[index]);
                ++index;
            }
        }

        TEST_CASE("Actions are subscribed to antoher action and invoked with right result", "[TypeMapWithPriority SetPriority Expecting Right Result]")
        {
            TypeMapWithPriority<ABase> typeMap;
            auto a1 = typeMap.Emplace<A1>(0);
            auto a2 = typeMap.Emplace<A2>(1);
            auto a3 = typeMap.Emplace<A3>(2);
            auto a4 = typeMap.Emplace<A4>(3);
            auto a5 = typeMap.Emplace<A5>(4);
            auto a6 = typeMap.Emplace<A6>(5);
            auto a7 = typeMap.Emplace<A7>(6);
            auto a8 = typeMap.Emplace<A8>(7);

            typeMap.SetPriority<A1>(4);
            typeMap.SetPriority<A2>(5);
            typeMap.SetPriority<A3>(6);
            typeMap.SetPriority<A4>(7);
            typeMap.SetPriority<A5>(0);
            typeMap.SetPriority<A6>(1);
            typeMap.SetPriority<A7>(2);
            typeMap.SetPriority<A8>(3);

            std::vector<ABase *> elements = {a5, a6, a7, a8, a1, a2, a3, a4};
            size_t index = 0;
            for (const auto &element : typeMap)
            {
                CHECK(element.priority == index);
                CHECK(element.element == elements[index]);
                ++index;
            }
        }
    }
}