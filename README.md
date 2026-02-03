# Minipad

Minipad is a lightweight, minimalistic text editor built with the GTK4 toolkit in C. It provides a simple graphical interface for editing plain text files, focusing on ease of use and essential features.

## Features

- **Open, Save, and Save As**: Easily open existing text files, save changes, or save your work under a new name.
- **Line and Column Indicator**: Displays the current cursor position (line and column) in the status bar.
- **Modern GTK4 UI**: Utilizes GTK4 for a clean, native look and feel on Linux desktops.
- **Header Bar Controls**: Common actions (Open, Save, Save As) are accessible from the window's header bar.

## Technologies Used

- **C**: The core language for application logic and UI integration.
- **GTK4**: Used for building the graphical user interface, including windows, buttons, text views, and dialogs.
- **GObject**: For memory management and signal handling in the GTK ecosystem.

## Project Structure

- `src/` — Source code files:
	- `main.c`: Application entry point and GTK application setup.
	- `editor.c`: Editor window, UI setup, and event handling.
	- `file_io.c`: File open/save dialog logic and file operations.
- `include/` — Header files:
	- `editor.h`: Editor data structures and function declarations.
- `Makefile` — Build instructions for compiling the project.

## Building Minipad

Ensure you have GTK4 development libraries installed. On Ubuntu, you can install them with:

```sh
sudo apt install libgtk-4-dev
```

To build the project, run:

```sh
make
```

This will produce the `minipad` executable in the project directory.

## Usage

Run the editor with:

```sh
./minipad
```

Use the header bar buttons to open, save, or save as files. The status bar at the bottom shows the current line and column.

## License

This project is provided for educational purposes and does not include a specific license. Feel free to use and modify it as needed.