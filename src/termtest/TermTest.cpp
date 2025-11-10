#include "TermTest.hpp"

namespace termtest {

using namespace std::literals;

TermTest::TermTest(const std::string& shellName) : proc(
    // TODO: 
    // 1. Change Process to take environment variables
    // 2. set PS1 to something easily parsed so input can be split properly
    // 3. the current getPTYContent() will clear the next prompt as well, so a more selective way to clear the buffer
    // should probably be added to stc
    // 4. This isn't going to work great with nested shells in integration tests. More research required
    std::make_shared<stc::Unix::Process>(
        std::vector<std::string> {
            "/usr/bin/env", shellName, getRcFlag(shellName), "-i"
        },
        std::make_shared<stc::Unix::PTY>()
    )
) {

}

// TODO: this isn't great
std::string TermTest::getPTYContent() {
    using namespace std::literals;

    std::this_thread::sleep_for(120ms);
    return proc->getStdoutBuffer(true);
}

void TermTest::runCommand(const std::string& command) {
    proc->writeToStdin(command + "\n");
    std::this_thread::sleep_for(100ms);
}

}
