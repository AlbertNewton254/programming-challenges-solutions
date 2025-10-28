/**
 * Interpreter
 * pc110106
 * uva10033
 */

#include <iostream>
#include <string>
#include <vector>
#include <array>

class Interpreter {
private:
	static constexpr int NUM_REGISTERS = 10;
	static constexpr int RAM_SIZE = 1000;

	std::array<int, NUM_REGISTERS> registers{};
	std::vector<std::string> ram;
	int programCounter{0};
	int instructionsExecuted{0};

public:
	Interpreter() : ram(RAM_SIZE, "000") {
		registers.fill(0);
	}

	void loadProgram() {
		std::string line;
		int address = 0;

		std::getline(std::cin, line);

		while (address < RAM_SIZE && std::getline(std::cin, line)) {
			if (line.empty()) {
				if (address == 0) continue;
				else break;
			}

			if (line.length() == 3 &&
				std::isdigit(line[0]) && std::isdigit(line[1]) && std::isdigit(line[2])) {
				ram[address++] = line;
			}
		}
	}

	void execute() {
		bool running = true;

		while (running && programCounter < RAM_SIZE) {
			const std::string& instruction = ram[programCounter];
			int opcode = instruction[0] - '0';
			int d = instruction[1] - '0';
			int n = instruction[2] - '0';

			instructionsExecuted++;

			switch (opcode) {
				case 0:
					if (registers[n] != 0) {
						programCounter = registers[d];
					} else {
						programCounter++;
					}
					break;

				case 1:
					if (instruction == "100") {
						running = false;
					} else {
						programCounter++;
					}
					break;

				case 2:
					registers[d] = n;
					programCounter++;
					break;

				case 3:
					registers[d] = (registers[d] + n) % 1000;
					programCounter++;
					break;

				case 4:
					registers[d] = (registers[d] * n) % 1000;
					programCounter++;
					break;

				case 5:
					registers[d] = registers[n];
					programCounter++;
					break;

				case 6:
					registers[d] = (registers[d] + registers[n]) % 1000;
					programCounter++;
					break;

				case 7:
					registers[d] = (registers[d] * registers[n]) % 1000;
					programCounter++;
					break;

				case 8:
					registers[d] = std::stoi(ram[registers[n]]);
					programCounter++;
					break;

				case 9:
					ram[registers[n]] = std::to_string(registers[d]);
					while (ram[registers[n]].length() < 3) {
						ram[registers[n]] = "0" + ram[registers[n]];
					}
					programCounter++;
					break;

				default:
					programCounter++;
			}
		}
	}

	int getInstructionsExecuted() const {
		return instructionsExecuted;
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::string line;
	std::getline(std::cin, line);
	int testCases = std::stoi(line);

	std::getline(std::cin, line);

	for (int i = 0; i < testCases; i++) {
		Interpreter interp;
		interp.loadProgram();
		interp.execute();

		std::cout << interp.getInstructionsExecuted() << "\n";

		if (i < testCases - 1) {
			std::cout << "\n";
		}
	}

	return 0;
}