# **cpp_result**

A compromise between error codes and exceptions.  Contains result types with detailed error messages and stack traces.

Error codes are the old-school method for error handling.  Error codes are more verbose than exceptions and require the programmer to explicitly handle all points of failure.  Error messages corresponding to error codes are too general and not particularly descriptive.

Exceptions generate more descriptive error messages than error codes, but they're not without problems.  Exceptions break code structure by creating multiple invisible exit points that make code hard to read and inspect.  Exception safety requires RAII, which is not always guaranteed, especially when using C libraries in C++.  Exceptions thrown while modifying invariants (variables with only a few valid states) can result in undefined behavior, regardless of whether the exceptions are caught.  [Writing exception-safe code in C++ is hard.](https://stackoverflow.com/a/1849519)

Result types are improved error codes with exception-like error messages.  As with error codes, result types must be explicitly handled at all points of failure.  As with exceptions, result types contain stack traces and highly descriptive error messages.

## Build from Source

### 1.&nbsp; Install a C++ compiler and Meson.

#### Windows:

Install ONE of the following C++ compilers:

- [Visual Studio's C++ compiler](https://visualstudio.microsoft.com/downloads/) (MSVC)
    - Select the "Desktop development with C++" option.
- [MinGW](https://sourceforge.net/projects/mingw/) (GCC for Windows)
    - Mark "mingw32-gcc-g++" for installation. Then select "Apply Changes" within the "Installation" dropdown.
    - Add the MinGW bin directory (C:\\MinGW\\bin\\) to your [PATH](https://stackoverflow.com/questions/5733220/how-do-i-add-the-mingw-bin-directory-to-my-system-path).

Install [Meson](https://mesonbuild.com) (C++ meta-build system):
    - Download and execute the Windows installer (.msi file) from the [official repository](https://github.com/mesonbuild/meson/releases).

#### Mac:

Install [Homebrew](https://brew.sh/) (package manager for Mac) by opening a terminal and entering the following command:

```zsh
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

Use Homebrew to install GCC (C++ compiler):

```zsh
brew install gcc
```

Follow these instructions to install [Meson](https://mesonbuild.com/SimpleStart.html) (C++ meta-build system).

#### Linux (Ubuntu):

```bash
sudo apt install meson ninja build-essential
```

#### Linux (Arch):

```bash
sudo pacman -S git meson base-devel
```

### 2.&nbsp; Clone this project.

This project can be downloaded online [here](https://github.com/cshmookler/cpp_result).

Alternatively, if you have [Git](https://git-scm.com/downloads/) installed, open command prompt (Windows) or a shell (Linux & Mac) and enter the commands below.  This project will be downloaded to the current working directory.

```
git clone https://github.com/cshmookler/cpp_result.git
cd cpp_result
```

### 3.&nbsp; Build this project from source.

```
meson setup build
cd build
ninja
```

### 4.&nbsp; (Optional) Install this project globally.

```
meson install
```

## **TODO**

- [X] Create a dedicated error type to distinguish between strings and errors.
- [X] Create a result type that indicates success or failure.
- [X] Create an optional type that either contains a value or an error.
- [X] Add tests for all methods.
- [X] Add examples for all types.
