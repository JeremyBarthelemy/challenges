# Trigram counter!
This (C++) program will count the most common three word sequences in the text files you provide.

## How to run the program
Note: I built and tested this in a Linux Red Hat environment.
1. Compile the program: `g++ -o CodingChallenge main.cpp`
2. Run the program with file paths: `./CodingChallenge texts/the-shining.txt texts/war-and-peace.txt`
3. Or use stdin: `cat texts/*.txt | ./CodingChallenge`

**OR**

1. In the root directory of the project, create a directory titled "build": `mkdir build && cd build`
2. Run `cmake ..` followed by `make` to build the executable.

## How to run the tests
1. Compile the program as above
2. Run the program as `./CodingChallenge RunAllTests`
3. You should expect to see that all tests pass and that you do not encounter any assertion failures.

## What I would do next
1. Refine the text processing some more to better handle edge cases / special characters. I particularly
   ran into trouble with certain accents in the example text file from War and Peace.
2. Make some more optimizations to the counting and the sorting for better performance (particularly on larger files).
   I'm sure there are more efficient ways to implement this.
3. Maybe change it so there's a better way to run tests / a separate application, especially if you really wanted to
   analyze text in a text file called RunAllTests :)
4. Do some more debugging to see why my numbers don't quite match up with what was in the challenge pdf!
5. Experiment with fuzzing tests

## Known Bugs
