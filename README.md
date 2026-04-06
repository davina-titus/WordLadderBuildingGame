# Word Ladder Building Game

## Description

This program implements a word ladder game and solver. A word ladder connects two words by changing one letter at a time, where each step must form a valid dictionary word. The program reads a dictionary file, lets the user build a word ladder interactively, and uses a breadth-first search (BFS) algorithm to find the shortest possible word ladder between two words.

## Author

Davina Titus

## Repository Contents

- `main.c` - Primary source code for the word ladder game and solver
- `makefile` - Build instructions for compiling the program
- `demo.exe` - Pre-compiled executable for Windows (game version)
- `ladders.exe` - Pre-compiled executable for Windows (solver version)
- `dictionary.txt` - Main dictionary file for word validation
- `sampleDict.txt` - Smaller sample dictionary for testing
- `simple3.txt`, `simple4.txt`, `simple5.txt` - Dictionary files for words of length 3, 4, and 5
- `gameplayDemoInputs.txt` - Example inputs for demonstrating gameplay
- `reflection_dtitu.pdf` - Project reflection document
- `testing_dtitu.pdf` - Testing documentation

## Features

- **Interactive game mode** – User builds a word ladder step by step.
- **Shortest path solver** – Uses BFS to find the minimum ladder between two words.
- **Custom dictionary support** – Loads words from external text files.
- **Case-insensitive processing** – Automatically converts input to lowercase.
- **Validation checks** – Verifies word length and dictionary presence.

## How to Compile and Run

### Compilation (using makefile)

```bash
make -f makefile
```

### Running the program

```bash
./demo.exe     (for game mode on Windows)
./ladders.exe  (for solver mode on Windows)
```

Alternatively, compile `main.c` with a C compiler (e.g., gcc) and run the resulting executable.

## Usage Examples

### Game mode

1. Program loads the default dictionary.
2. User enters a start word and an end word.
3. User is prompted to change one letter at a time.
4. Program verifies each step against the dictionary.
5. Upon reaching the end word, the full ladder is displayed.

### Solver mode

1. Program loads the default dictionary.
2. User enters a start word and an end word.
3. Program performs a breadth-first search.
4. The shortest possible word ladder (if any) is displayed.

## Sample Dictionary Files

- `simple3.txt` – Words with exactly 3 letters.
- `simple4.txt` – Words with exactly 4 letters.
- `simple5.txt` – Words with exactly 5 letters.

## Known Issues / Limitations

- All words in the dictionary must be lowercase for proper comparison.
- The program assumes the dictionary file exists in the same directory.
- Very large dictionaries may cause memory or performance issues.

## Future Improvements (Suggested)

- Add support for multiple word lengths in a single dictionary.
- Implement a graphical user interface.
- Add timers or scoring for the game mode.
- Allow the user to specify a custom dictionary file at runtime.

## License

This project is open source and available for educational use.

## Acknowledgments

- BFS algorithm adapted for the word ladder problem.
- Dictionary files may be derived from standard word lists.
