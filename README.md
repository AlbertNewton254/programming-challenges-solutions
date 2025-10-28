# Programming Challenges Solutions

Solutions to the book "Programming Challenges" by Steven Skiena and Miguel Revilla.

## Repository Structure

This repository contains solutions organized by chapter (`pcXX`) and problem number (`pcXX_YY`). Each problem may have implementations in different programming languages.

```
programming-challenges-solutions/
├── pcXX/                    # Chapter XX
│   └── pcXX_YY/            # Problem YY from chapter XX
│       ├── test.txt        # Test cases for this problem
│       ├── c/              # C implementation
│       ├── cpp/            # C++ implementation
│       ├── java/           # Java implementation
│       └── python/         # Python implementation
└── ...
```

Example:
- `pc01/pc01_01/test.txt` - Test cases for problem 1 from chapter 1
- `pc01/pc01_01/c/pc01_01.c` - C implementation
- `pc01/pc01_01/java/Main.java` - Java implementation

## Running Solutions

Each problem has a `test.txt` file containing sample input cases at its root. Solutions read from standard input and write to standard output.

### C Solutions

```bash
# From the solution's directory (e.g., pc01/pc01_01/c/)
gcc -std=c11 -O2 -Wall -o solution *.c
cd ..  # Go up to access test.txt
./c/solution < test.txt
```

### C++ Solutions

```bash
# From the solution's directory (e.g., pc01/pc01_01/cpp/)
g++ -std=c++17 -O2 -Wall -o solution *.cpp
cd ..
./cpp/solution < test.txt
```

### Java Solutions

```bash
# From the solution's directory (e.g., pc01/pc01_01/java/)
javac *.java
cd ..
java -cp java Main < test.txt
```

### Python Solutions

```bash
# From the problem's root directory (e.g., pc01/pc01_01/)
python3 python/solution.py < test.txt
```

## Tests and Output

- Each problem's `test.txt` contains sample input from the book
- Solutions read from stdin and write to stdout
- Some solutions may print timing/debug information
- To capture output: `./solution < test.txt > output.txt`

## Contributing Guidelines

1. **Code Organization**
   - Place solutions under the correct chapter/problem directory
   - Use the standard directory structure: `pcXX/pcXX_YY/<language>/`
   - Place test cases in `pcXX/pcXX_YY/test.txt`

2. **Code Style**
   - Include problem ID/name in file comments
   - Follow language-specific style guides
   - Add reasonable code comments
   - Ensure code is formatted properly

3. **Test Cases**
   - Always include book's sample test cases in `test.txt`
   - Test your solution with the provided cases
   - Consider adding more test cases if helpful

4. **Pull Request Process**
   - Fork the repository
   - Create a feature branch (`feature/pcXX-YY-lang`)
   - Follow commit message guidelines
   - Open PR with clear description
   - PR must pass any CI checks
   - Address review comments promptly

## License

This project is licensed under the MIT License - see [LICENSE](LICENSE) for details.
