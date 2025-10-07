from enum import Enum
from time import sleep

class Color(Enum):
    Red = 1,
    White = 2,
    Blue = 3,

class DutchFlagPrinter:
    def __init__(self, data:list[Color]):
        self.column = 0
        self.reset(data)

    def reset(self, data:list[Color]):
        for _ in data:
            print()
        self.column = 0

    def print_line(self, data:list[Color]):
        print(f"\033[{len(data)}A")
        print(f"\033[{2*self.column}C", end = "")

        for color in data:

            match color:
                case Color.Red:
                    print("\033[48;2;173;29;37m  \033[B\033[2D", end = "")

                case Color.White:
                    print("\033[48;2;255;255;255m  \033[B\033[2D", end = "")

                case Color.Blue:
                    print("\033[48;2;30;71;133m  \033[B\033[2D", end = "")

        self.column+= 1
        print("\033[0m", end = "")

    def print_flag(self, data:list[Color]):
        self.reset(data)
        for _ in range(3*len(data)//2):
            self.print_line(data)

def sort_dutch_flag(input:list[Color]):
    begin:int = 0
    end:int = len(input) - 1
    curr:int = 0

    flag_printer:DutchFlagPrinter = DutchFlagPrinter(input)
    while curr < end:
        flag_printer.print_line(input)
        match input[curr]:
            case Color.White:
                curr+=1

            case Color.Blue:
                input[curr], input[end] = input[end], input[curr]
                end -=1

            case Color.Red:
                input[curr], input[begin] = input[begin], input[curr]
                begin +=1
        sleep(0.1)
    print("\n\n\033[1mGOD BLESS THE DUTCH \033[0m")
    flag_printer.print_flag(input)
    print()
