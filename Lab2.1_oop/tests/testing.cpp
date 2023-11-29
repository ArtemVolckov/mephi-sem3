#define CATCH_CONFIG_MAIN

#include "../../../catch2/catch.hpp"
#include "../message_queue_list/Message_Queue_List.h"

using namespace Prog3;

TEST_CASE("Message_Queue_List_Constructor") {
    SECTION("DefaultConstructor") {
        message_queue_list a;
        REQUIRE(a.GetHead()==nullptr);
    }
}