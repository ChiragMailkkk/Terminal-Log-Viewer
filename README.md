# Terminal Log Viewer

A beginner-friendly command-line application written in **C** to read, search, filter, and summarize log files.

## Features

- **View all logs:** Display every line in the selected log file.
- **Search logs:** Find entries containing a keyword (case-insensitive).
- **Filter by level:** Display entries containing INFO, WARNING, or ERROR.
- **Log statistics:** Count total entries and entries by log level.
- **Custom file support:** Open a log file by passing its path when starting the program.

## Technologies and concepts

- Programming language: C
- Standard libraries: `stdio.h`, `string.h`, `ctype.h`
- File handling (`fopen`, `fgets`, `fclose`)
- Strings and character handling
- Functions, loops, conditions, and `switch` statements

## Project structure

```text
Terminal-Log-Viewer/
├── main.c
├── sample.log
├── README.md
└── .gitignore
```

## Requirements

- A C compiler such as GCC
- A terminal or command prompt

## How to compile and run

### Linux

Open a terminal inside the project folder and run:

```bash
gcc main.c -o logviewer
./logviewer
```

### Windows (MinGW GCC)

Open Command Prompt or the VS Code terminal inside the project folder:

```bash
gcc main.c -o logviewer.exe
logviewer.exe
```

## Open another log file

You can provide a log file path as a command-line argument:

```bash
./logviewer another.log
```

On Windows:

```bash
logviewer.exe another.log
```

Make sure the log file exists at the path you provide.

## Sample log format

The included `sample.log` contains example entries with timestamps and log levels, such as:

```text
2026-11-20 09:00:12 INFO Application started successfully
2026-11-20 09:02:18 WARNING Disk space is getting low
2026-11-20 09:03:44 ERROR Unable to connect to database
```

## Limitations

- The application reads plain-text log files.
- Each input line is limited to 511 characters.
- Log-level filtering searches for the selected word in each line; it does not validate a strict log format.

## Future improvements

- Add date and time based filtering.
- Support larger log files and configurable output.
- Add color-coded log levels.
- Export search results to a separate file.
- Add pagination for large log files.

## Author

Harshit Tandon  
Computer Science and Engineering  
Chandigarh University

## License

This project is available under the MIT License. See [LICENSE](LICENSE) if you choose to add one.
