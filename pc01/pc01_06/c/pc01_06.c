/**
 * Interpreter
 * pc110106
 * uva10033
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTERS 10
#define RAMSIZE 1000
#define MAX_LINE 4

typedef struct {
	int registers[REGISTERS];
	char ram[RAMSIZE][MAX_LINE];
	int program_counter;
	int instructions_executed;

} interpreter_t;

void initialize_interpreter(interpreter_t *interpreter) {
	memset(interpreter->registers, 0, sizeof(interpreter->registers));
	for (int i = 0; i < RAMSIZE; i++) {
		strcpy(interpreter->ram[i], "000");
	}
	interpreter->program_counter = 0;
	interpreter->instructions_executed = 0;
}

void load_program(interpreter_t *interpreter) {
	int address = 0;
	char line[MAX_LINE + 2];

	if (fgets(line, sizeof(line), stdin) == NULL) return;

	while (address < RAMSIZE && fgets(line, sizeof(line), stdin)) {
		line[strcspn(line, "\n")] = '\0';
		if (strlen(line) == 0) {
			if (address == 0) continue;
			else break;
		}

		if (strlen(line) == 3 && line[0] >= '0' && line[0] <= '9'
				&& line[1] >= '0' && line[1] <= '9'
				&& line[2] >= '0' && line[2] <= '9') {
			strncpy(interpreter->ram[address], line, 3);
			interpreter->ram[address][3] = '\0';
			address++;
		}
	}
}

void execute_instructions(interpreter_t *interpreter) {
	int running = 1;

	while (running && interpreter->program_counter < RAMSIZE) {
		char *instruction = interpreter->ram[interpreter->program_counter];
		int opcode = instruction[0] - '0';
		int d = instruction[1] - '0';
		int n = instruction[2] - '0';

		interpreter->instructions_executed++;

		switch (opcode) {
			case 0:
				if (interpreter->registers[n] != 0) {
					interpreter->program_counter = interpreter->registers[d];
				} else {
					interpreter->program_counter++;
				}
				break;

			case 1:
				if (strcmp(instruction, "100") == 0) {
					running = 0;
				} else {
					interpreter->program_counter++;
				}
				break;

			case 2:
				interpreter->registers[d] = n;
				interpreter->program_counter++;
				break;

			case 3:
				interpreter->registers[d] = (interpreter->registers[d] + n) % 1000;
				interpreter->program_counter++;
				break;

			case 4:
				interpreter->registers[d] = (interpreter->registers[d] * n) % 1000;
				interpreter->program_counter++;
				break;

			case 5:
				interpreter->registers[d] = interpreter->registers[n];
				interpreter->program_counter++;
				break;

			case 6:
				interpreter->registers[d] = (interpreter->registers[d] + interpreter->registers[n]) % 1000;
				interpreter->program_counter++;
				break;

			case 7:
				interpreter->registers[d] = (interpreter->registers[d] * interpreter->registers[n]) % 1000;
				interpreter->program_counter++;
				break;

			case 8:
				interpreter->registers[d] = atoi(interpreter->ram[interpreter->registers[n]]);
				interpreter->program_counter++;
				break;

			case 9:
				snprintf(interpreter->ram[interpreter->registers[n]], MAX_LINE, "%03d", interpreter->registers[d]);
				interpreter->program_counter++;
				break;

			default:
				interpreter->program_counter++;
		}
	}
}

int main(void) {
	int test_cases;
	char line[MAX_LINE + 2];

	if (fgets(line, sizeof(line), stdin) == NULL) return 1;
	test_cases = atoi(line);

	if (fgets(line, sizeof(line), stdin) == NULL) return 1;

	for (int i = 0; i < test_cases; i++) {
		interpreter_t interpreter;
		initialize_interpreter(&interpreter);
		load_program(&interpreter);
		execute_instructions(&interpreter);

		printf("%d\n", interpreter.instructions_executed);

		if (i < test_cases - 1) {
			printf("\n");
		}
	}

	return 0;
}