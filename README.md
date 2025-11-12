# termtest

Termtest is a meta-library for writing integration tests for command line utilities. It's designed to be framework-agnostic (i.e. plug it into whatever test system you want).

## What?

As far as I'm aware, there are no systems that actually let you integration test CLI programs, at least in C++. 

Specifically, this library is meant for CLI apps with interactive features (primarily keyboard)

This is primarily a test-oriented wrapper with lots of shell-specific utilities aimed at specifically integration testing when a nested shell is involved. 

Under the hood, [`stc::Unix::Process`](https://github.com/LunarWatcher/stc) is used. If you don't have a full fucking shell involved in the testing loop, you'll probably find it easier to use `stc::Unix::Process` in pipe mode, and have each run of the command be a separate run. Pipe mode still supports stdin, but stdin content is fully separate from the content buffer.

## Requirements

* C++20
* A Linux environment. Windows support may be added in the future if it's possible to do so, macOS will never be supported.

