/* interpreter
 * pg110106
 * uva10033 */

import java.util.Scanner;

public class Interpreter {
    private final int REGISTERS = 10;
    private final int RAMSIZE = 1000;

    public int[] registers;
    public String[] ram;

    public int programCounter;
    public int instructionsExecuted;

    public Interpreter() {
        this.registers = new int[REGISTERS];
        this.ram = new String[RAMSIZE];
        initialize();
    }

    public void initialize() {
        for (int i = 0; i < REGISTERS; i++) {
            registers[i] = 0;
        }

        for (int i = 0; i < RAMSIZE; i++) {
            ram[i] = "000";
        }

        programCounter = 0;
        instructionsExecuted = 0;
    }

    public void loadProgram(Scanner scanner) {
        int address = 0;

        while (address < RAMSIZE && scanner.hasNextLine()) {
            String line = scanner.nextLine().trim();

            if (line.isEmpty()) {
                if (address == 0) {
                    continue;
                } else {
                    break;
                }
            }

            if (line.length() == 3 && line.matches("\\d{3}")) {
                ram[address] = line;
                address++;
            }
        }
    }

    public void execute() {
        boolean running = true;

        while (running && programCounter < RAMSIZE) {
            String instruction = ram[programCounter];
            int opcode = Integer.parseInt(instruction.substring(0, 1));
            int d = Integer.parseInt(instruction.substring(1, 2));
            int n = Integer.parseInt(instruction.substring(2, 3));

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
                    if (instruction.equals("100")) {
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
                    registers[d] = Integer.parseInt(ram[registers[n]]);
                    programCounter++;
                    break;

                case 9:
                    ram[registers[n]] = String.format("%03d", registers[d]);
                    programCounter++;
                    break;

                default:
                    programCounter++;
            }
        }
    }
}
