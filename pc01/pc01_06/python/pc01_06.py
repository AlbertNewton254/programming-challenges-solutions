"""
interpreter
pc110106
uva10033
"""

from typing import List


class Interpreter:
    NUM_REGISTERS = 10
    RAM_SIZE = 1000

    def __init__(self):
        self.registers: List[int] = [0] * self.NUM_REGISTERS
        self.ram: List[str] = ["000"] * self.RAM_SIZE
        self.program_counter: int = 0
        self.instructions_executed: int = 0

    def load_program(self) -> None:
        address = 0
        input()

        while address < self.RAM_SIZE:
            try:
                line = input().strip()
                if not line:
                    if address == 0:
                        continue
                    else:
                        break

                if (len(line) == 3 and
                    line[0].isdigit() and line[1].isdigit() and line[2].isdigit()):
                    self.ram[address] = line
                    address += 1
            except EOFError:
                break

    def execute(self) -> None:
        running = True

        while running and self.program_counter < self.RAM_SIZE:
            instruction = self.ram[self.program_counter]
            opcode = int(instruction[0])
            d = int(instruction[1])
            n = int(instruction[2])

            self.instructions_executed += 1

            if opcode == 0:
                if self.registers[n] != 0:
                    self.program_counter = self.registers[d]
                else:
                    self.program_counter += 1

            elif opcode == 1:
                if instruction == "100":
                    running = False
                else:
                    self.program_counter += 1

            elif opcode == 2:
                self.registers[d] = n
                self.program_counter += 1

            elif opcode == 3:
                self.registers[d] = (self.registers[d] + n) % 1000
                self.program_counter += 1

            elif opcode == 4:
                self.registers[d] = (self.registers[d] * n) % 1000
                self.program_counter += 1

            elif opcode == 5:
                self.registers[d] = self.registers[n]
                self.program_counter += 1

            elif opcode == 6:
                self.registers[d] = (self.registers[d] + self.registers[n]) % 1000
                self.program_counter += 1

            elif opcode == 7:
                self.registers[d] = (self.registers[d] * self.registers[n]) % 1000
                self.program_counter += 1

            elif opcode == 8:
                self.registers[d] = int(self.ram[self.registers[n]])
                self.program_counter += 1

            elif opcode == 9:
                self.ram[self.registers[n]] = f"{self.registers[d]:03d}"
                self.program_counter += 1

            else:
                self.program_counter += 1


def main() -> None:
    test_cases = int(input())
    input()

    for i in range(test_cases):
        interp = Interpreter()
        interp.load_program()
        interp.execute()

        print(interp.instructions_executed)
        if i < test_cases - 1:
            print()


if __name__ == "__main__":
    main()