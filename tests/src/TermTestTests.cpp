#include "termtest/TermTest.hpp"
#include "termtest/TermTest.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace std::literals;

TEST_CASE("Controlling bash should work", "[TermTest]") {
    termtest::TermTest controller;
    REQUIRE(!controller.hasStopped());

    SECTION("Can get some form of output from terminal") {
        controller.runCommand("echo 'Trans rights are human rights'");
        auto content = controller.getPTYContent();
        INFO(content);
        REQUIRE(content.find("Trans rights are human rights") != std::string::npos);

        REQUIRE(controller.stopBlockingAndCheckStopCode());
    }
}

/**
 * This is a regression test for a downstream stc bug, where calling .block() multiple times causes a SIGABRT.
 * The tests differ from stc's own tests by checking whether TermTest::stop() causes the same problem. It should be
 * functionally identical to the tests, but prevents fuckups in TermTest's implementation from causing problems.
 */
TEST_CASE("Stopping shouldn't cause problems") {
    SECTION("Not calling .stop explicity should be fine"){
        REQUIRE_NOTHROW([]() {
            { // Not sure if this extra scope is necessary, but doesn't hurt
                termtest::TermTest controller;
            }
        }());
    }
    SECTION("Calling stop explicitly should also be fine"){
        REQUIRE_NOTHROW([]() {
            { // Not sure if this extera scope is necessary, but doesn't hurt
                termtest::TermTest controller;
                REQUIRE(controller.stopBlockingAndCheckStopCode());
            }
        }());
    }
}
