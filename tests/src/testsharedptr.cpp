#include <catch.hpp>
#include <util/shared_ptr.h>

TEST_CASE("Test SharedPtr") {
    SharedPtr<std::string> ptr("TEST");
    REQUIRE(*ptr == "TEST");
    REQUIRE(ptr.count() == 1);

    {
        SharedPtr<std::string> ptr2(ptr);
        REQUIRE(*ptr2 == "TEST");
        REQUIRE(ptr.count() == 2);
        REQUIRE(ptr2.count() == 2);
    }

    REQUIRE(*ptr == "TEST");
    REQUIRE(ptr.count() == 1);

    {
        SharedPtr<std::string> ptr2 = ptr;
        REQUIRE(*ptr2 == "TEST");
        REQUIRE(ptr.count() == 2);
        REQUIRE(ptr2.count() == 2);
    }

    REQUIRE(*ptr == "TEST");
    REQUIRE(ptr.count() == 1);
}