# Programming Challenges Solutions

Solutions to the book "Programming Challenges" by Steven Skiena and Miguel Revilla.

## About this repository

This repository collects solutions to problems from the book. Solutions are organized by chapter and problem (for example `pc01/pc01_01`) and many problems include implementations in multiple languages. Each language folder often contains a `test.txt` file with example input (and sometimes multiple test cases) that you can use to run the solution locally.

## Repository layout (convention)

Top-level folders are chapters. Under each chapter you'll find per-problem folders. A typical path looks like:

```
pcXX/pcXX_YY/<language>/*
```

Examples present in this repo:

- `pc01/pc01_01/c/pc01_01.c` and `pc01/pc01_01/c/test.txt`
- `pc01/pc01_05/java/Main.java` and `pc01/pc01_05/java/test.txt`
- `pc01/pc01_08/python/pc01_08.py` and `pc01/pc01_08/python/test.txt`

Note: not every problem has every language. Look inside the problem folder to see which languages are available.

## Where tests live

Most problems that include a sample input place it in a `test.txt` file inside the language folder. `test.txt` typically contains input you can pipe to the program's stdin to reproduce sample output.

## Recommended commands to compile/run examples

Below are straightforward commands you can use on Linux (zsh/bash). Replace filenames as needed for other problems.

1) C (gcc)

Compile:

```bash
gcc -std=c11 -O2 -Wall -o pc01_01 pc01_01.c
```

Run with the bundled sample input (if `test.txt` exists):

```bash
./pc01_01 < test.txt
```

2) C++ (g++)

Compile:

```bash
g++ -std=c++17 -O2 -Wall -o solution solution.cpp
```

Run:

```bash
./solution < test.txt
```

3) Java

Compile (from the language folder):

```bash
javac *.java
```

Run (class named `Main`):

```bash
java Main < test.txt
```

4) Python 3

Run directly:

```bash
python3 pc01_08.py < test.txt
```

## Helpful one-liners for running many examples

These are just quick helpers — adapt before running on many files.

Run every C file found and pipe its `test.txt` (if present):

```bash
find . -type f -name '*.c' | while read -r src; do
   dir=$(dirname "$src")
   exe="$dir/$(basename "$src" .c)"
   echo "Compiling $src..."
   gcc -std=c11 -O2 -Wall -o "$exe" "$src" || continue
   if [ -f "$dir/test.txt" ]; then
      echo "Running $exe with $dir/test.txt"
      "$exe" < "$dir/test.txt"
   else
      echo "No test.txt in $dir"
   fi
done
```

Run Java `Main` in folders that contain `Main.java`:

```bash
find . -name 'Main.java' | while read -r f; do
   dir=$(dirname "$f")
   echo "Compiling and running Java in $dir"
   (cd "$dir" && javac *.java && java Main < test.txt)
done
```

Run Python files with a `test.txt` present:

```bash
find . -type f -name '*.py' | while read -r py; do
   dir=$(dirname "$py")
   if [ -f "$dir/test.txt" ]; then
      echo "Running $py with $dir/test.txt"
      python3 "$py" < "$dir/test.txt"
   fi
done
```

## Notes about tests & outputs

- `test.txt` usually contains sample input. The repository does not enforce a single testing harness or expected-output file per problem — outputs are generally printed to stdout by each solution.
- Some solutions print additional timing/debug information (for example, a "Time of execution" line). Be aware of that when comparing outputs to expected values.
- If you want to capture program output for comparison, redirect to a file:

```bash
./solution < test.txt > output.txt
```

Then compare with `diff` or `sdiff`.

## Contributing

Contributions are welcome. When adding new solutions please:

1. Place the solution under the appropriate `pcXX/pcXX_YY/<language>/` folder.
2. Include a `test.txt` with at least the sample input used in the book (if possible).
3. Add a short comment at the top of source files describing the problem ID (if known).

Follow the repository's branch and PR workflow (create a branch, push, open PR). If a `dev` branch is enforced for PRs, open PRs there.

## License

This project is licensed under the MIT License. See `LICENSE` for details.

---

If you'd like, I can also add a small helper script (for example `run_all_tests.sh`) to the repo that automates compilation and test execution per-language — tell me which languages you want supported and I'll add it.
