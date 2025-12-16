from scipy.optimize import linprog
import numpy as np


class DayStarter:

    def __new__(self):
        with open(f'input_files\day10.txt', 'r') as f:
            self.input = f.read()
        return self.input

class AdventDay10:

    def __init__(self):
        self.data = [x for x in DayStarter().split('\n')]
        self._process_data()
        self.part1 = 0
        self.part2 = 0

    def _process_data(self):
        self.machines = []
        for line in self.data:
            if line == '':
                continue
            parts = line.split(' ')
            machine = {
                'lights': self._read_contents(parts[0]),
                'buttons': [self._read_contents(x) for x in parts[1:-1]],
                'joltage': self._read_contents(parts[-1])
            }
            self.machines.append(machine)

    def _read_contents(self, string):
        result = []
        for char in string[1:-1].split(','):
            try:
                result.append(int(char))
            except ValueError:
                result.append(char)
        if isinstance(result[0], int):
            return result
        return result[0]

    def minimal_joltage_presses(self):
        for machine in self.machines:
            buttons = machine['buttons']
            joltage = machine['joltage']
            A = np.array([[int(i in button) for i in range(len(joltage))]
                         for button in buttons]).transpose()
            b = np.array(joltage)
            c = [1 for _ in range(len(buttons))]
            solution = linprog(c=c, A_eq=A, b_eq=b, integrality=1)
            self.part2 += solution.fun
        self.part2 = int(self.part2)

if __name__ == '__main__':
    day10 = AdventDay10()
    day10.minimal_joltage_presses()
    print(day10.part1, day10.part2)