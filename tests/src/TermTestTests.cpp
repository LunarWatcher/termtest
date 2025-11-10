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
