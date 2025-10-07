from .longest_nonrepeating_substring import longest_nonrepeating_substring
from .valid_intersecting_brackets import valid_intersecting_brackets
from .two_sum import two_sum
from .sort_dutch_flag import *

def main():
    print("\nHello from Python!\n")

    print("Sort dutch flag")
    scrambeled_flag = [
        Color.White,
        Color.Red,
        Color.Red,
        Color.Blue,
        Color.Blue,
        Color.Red,
        Color.White,
        Color.White,
        Color.Blue,
        Color.Blue,
        Color.White,
        Color.White,
        Color.Red,
        Color.Red,
        Color.Blue,
        Color.White,
        Color.White
    ];
    sort_dutch_flag(scrambeled_flag)

    print("\nTwo sum\n")
    numbers = [1, 2, 5, 7, 4, 5, 0, 49, 29, 19]
    print(f"Input is:\n{numbers}")
    sum = two_sum(10, numbers)
    if sum != None:
        print(f"The indexes of sum are {sum[0]} and {sum[1]}\n")
    else:
        print("there is no pair of numbers that equal to target")

    print("\nLongest nonrepeating substring\n")
    input = "aloikjhjasdfyhuiiouehjfgopwq;ewrdfgjwqdp[ovmwpeoirkjfvcwq;olkdjvsa;dlqwertyuiopaSDFGHJKLkgjkfs[v[vqerpokrvfg";

    print(f"Input is:\n{input}")
    output = longest_nonrepeating_substring(input)
    print(f"longest substring is: \n{output}\n")

    print("\nValid intersecting brackets\n")
    strings = ["{{}<[>]}", "{{", "]]", "<<{>{[}>(}])"]
    for string in strings:
        if valid_intersecting_brackets(string):
            print(string, "is a valid input")
        else:
            print(string, "is an invalid input")
