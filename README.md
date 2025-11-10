# termtest

Termtest is a meta-library for writing integration tests for command line utilities. It's designed to be framework-agnostic (i.e. plug it into whatever test system you want).

## What?

As far as I'm aware, there are no systems that actually let you integration test CLI programs, at least in C++. 

Specifically, this library is meant for CLI apps with interactive features (primarily keyboard)

## Requirements

* C++20
* A Linux environment. Windows support may be added in the future if it's possible to do so, macOS will never be supported.

