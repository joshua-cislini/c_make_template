# C Multi-File Project Template

A simple C project using **GCC**, **MinGW**, **Make**, **GDB**, and **Clang-Format**, designed for development in **Visual Studio Code**.

---

## Project Structure

```text
MyProject/
│
├── Makefile
├── README.md
├── .clang-format
│
├── src/
│   ├── main.c
│   ├── test.c
│   └── ...
│
├── include/
│   ├── test.h
│   └── ...
│
├── build/
│   ├── program.exe
│   │
│   └── obj/
│       ├── main.o
│       ├── main.d
│       ├── test.o
│       └── test.d
│
└── .vscode/
    ├── settings.json
    ├── tasks.json
    └── launch.json
```

### Directories

| Directory    | Purpose                                         |
| ------------ | ----------------------------------------------- |
| `src/`       | C source files (`.c`)                           |
| `include/`   | Header files (`.h`)                             |
| `build/`     | Compiled output                                 |
| `build/obj/` | Object files (`.o`) and dependency files (`.d`) |
| `.vscode/`   | VS Code configuration                           |

### Important files

| File            | Purpose                                             |
| --------------- | --------------------------------------------------- |
| `Makefile`      | Controls compilation, linking, running and cleaning |
| `README.md`     | Project documentation                               |
| `.clang-format` | Defines the project's C/C++ code formatting style   |
| `main.c`        | Program entry point                                 |
| `.h` files      | Function declarations and shared definitions        |
| `.c` files      | Function implementations                            |

---

# Building the Project

## Requirements

The following tools must be installed and available from the terminal:

* GCC
* MinGW
* `mingw32-make`
* GDB
* Visual Studio Code
* VS Code C/C++ extension
* Clang-Format

---

## Build

Open a terminal in the project root:

```text
mingw32-make
```

This compiles all `.c` files in `src/` and links them into:

```text
build/program.exe
```

You can also use the VS Code build shortcut:

**`Ctrl + Shift + B`**

---

# Run

To build and run the program:

```text
mingw32-make run
```

Or run the executable directly:

```text
build/program.exe
```

---

# Debug

Press:

**`F5`**

VS Code will:

1. Run the `Build` task.
2. Compile the project using Make.
3. Start GDB.
4. Launch `build/program.exe`.
5. Allow debugging with breakpoints and stepping.

Useful debugging shortcuts:

| Key           | Action                     |
| ------------- | -------------------------- |
| `F5`          | Start / continue debugging |
| `F10`         | Step over                  |
| `F11`         | Step into                  |
| `Shift + F11` | Step out                   |
| `Shift + F5`  | Stop debugging             |

---

# Clean

To remove all compiled files:

```text
mingw32-make clean
```

This deletes the entire `build/` directory.

---

# Rebuild

To completely clean and rebuild the project:

```text
mingw32-make clean
mingw32-make
```

Or use the VS Code `Rebuild` task.

---

# Code Formatting

This project uses **Clang-Format** to keep the source code consistently formatted.

The formatting rules are stored in:

```text
.clang-format
```

This file is located in the **root of the project** so that the same formatting rules can be used throughout the entire project.

Clang-Format automatically searches for a `.clang-format` file in the directory of the source file and its parent directories. Therefore, the root `.clang-format` can define the formatting rules for the entire project.

## VS Code formatting

VS Code can use Clang-Format to format C source and header files.

The project is configured to format files automatically when:

* pasting code
* typing code
* saving a file

The relevant settings are in:

```text
.vscode/settings.json
```

In particular:

```json
"editor.formatOnPaste": true,
"editor.formatOnType": true,
"editor.formatOnSave": true,
"editor.defaultFormatter": "ms-vscode.cpptools"
```

This means that saving a `.c` or `.h` file will automatically format the code according to the project's formatting configuration.

## Manual formatting

A file can also be formatted manually in VS Code.

Use:

**`Shift + Alt + F`**

or:

1. Right-click inside the source file.
2. Select **Format Document**.

The code will be formatted according to `.clang-format`.

## Why keep `.clang-format` in the project?

Keeping the configuration file in the repository means that everyone working on the project can use the **same formatting rules**.

For example, instead of each developer having their own preferred indentation:

```c
void test_function(void)
{
    printf("Hello\n");
}
```

the project defines one consistent style.

This is especially useful when working with Git or when sharing the project with other people.

> **The `.clang-format` file controls how the code looks. It does not affect how the C program is compiled or how it behaves.**

---

# How the Build System Works

The Makefile automatically searches for all `.c` files inside:

```text
src/
```

For example:

```text
src/main.c
src/test.c
src/pid.c
src/nn.c
```

These are compiled separately:

```text
main.c → main.o
test.c → test.o
pid.c  → pid.o
nn.c   → nn.o
```

The object files are stored in:

```text
build/obj/
```

Make then links all object files together:

```text
main.o
test.o
pid.o
nn.o
   ↓
program.exe
```

---

# Header Files

Header files belong in:

```text
include/
```

For example:

```text
include/test.h
```

A header normally contains declarations:

```c
#ifndef TEST_H
#define TEST_H

void test_function(void);

#endif
```

The implementation belongs in:

```text
src/test.c
```

```c
#include <stdio.h>

#include "test.h"

void test_function(void)
{
    printf("Hello from test.c\n");
}
```

Another source file can then use the function:

```c
#include "test.h"

int main(void)
{
    test_function();

    return 0;
}
```

---

# Dependencies

The compiler automatically generates `.d` dependency files.

For example:

```text
build/obj/main.d
```

These files tell Make which headers each source file depends on.

If:

```text
main.c → test.h
test.c → test.h
```

and `test.h` is modified, Make knows that both files need to be recompiled.

This allows **incremental builds** without unnecessarily recompiling the entire project.

---

# Adding a New Source File

To add another C source file, simply place it in:

```text
src/
```

For example:

```text
src/calculator.c
```

No change to the Makefile is required.

Because the Makefile automatically searches for `.c` files, it will detect the new file during the next build.

If the file has a corresponding header:

```text
include/calculator.h
```

include it with:

```c
#include "calculator.h"
```

---

# Example

A small project might look like:

```text
src/
├── main.c
├── pid.c
├── nn.c
└── plant.c

include/
├── pid.h
├── nn.h
└── plant.h
```

The Makefile automatically builds:

```text
main.c  → main.o
pid.c   → pid.o
nn.c    → nn.o
plant.c → plant.o
```

and finally:

```text
program.exe
```

---

# Useful Make Commands

| Command                               | Description           |
| ------------------------------------- | --------------------- |
| `mingw32-make`                        | Build the project     |
| `mingw32-make run`                    | Build and run         |
| `mingw32-make clean`                  | Delete compiled files |
| `mingw32-make clean` + `mingw32-make` | Full rebuild          |

---

# Development Workflow

A typical development cycle is:

```text
1. Edit .c or .h files
        ↓
2. Save the file
        ↓
3. Clang-Format formats the code
        ↓
4. mingw32-make
        ↓
5. Make recompiles only what is necessary
        ↓
6. program.exe is updated
        ↓
7. F5 to debug
```

The goal of this structure is to keep the project **modular, consistently formatted, easy to build, and easy to debug**.

# License

This project is licensed under the **MIT License**.

See the [`LICENSE`](LICENSE) file for the complete license text.
