#pragma once

#include <memory>
#include <stc/unix/Process.hpp>

namespace termtest {

class TermTest {
private:
    std::string getRcFlag(const std::string& shellname) {
        if (shellname == "bash") {
            return "--norc";
        } else if (shellname == "zsh") {
            return "--no-rcs";
        } else {
            throw std::runtime_error("Unknown shell: cannot handle rc flags");
        }
    }

public:
    // This has to be a pointer, or it's destructed before ~TermTest is invoked
    std::shared_ptr<stc::Unix::Process> proc;

    TermTest(
        const std::string& shellName = "bash"
    );
    ~TermTest() {
        stop();
    }

    void runCommand(const std::string& command);

    auto block() { return proc->block(); }

    std::string getPTYContent();

    void stop() {
        if (!proc->getExitCode().has_value()) {
            runCommand("\x03");
            runCommand("exit " + std::to_string(getStopCode()));
        }
    }

    bool hasStopped() {
        return proc->getExitCode().has_value();
    }

    /**
     * Returns true if the process has stopped with the stop code (getStopCode()), false if it stopped with something
     * else, or hasn't stopped yet.
     */
    bool stopBlockingAndCheckStopCode() {
        stop();
        return proc->block() == getStopCode();
    }

    /**
     * Returns the stop code used by TermTest's stop function.
     */
    constexpr int getStopCode() {
        return 42;
    }
};

}
