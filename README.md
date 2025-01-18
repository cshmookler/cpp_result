# **cpp_result**

Result types with detailed error messages and stack traces.

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
- [ ] Add tests for all methods.
- [ ] Add examples for all types.
