from .longest_nonrepeating_substring import longest_nonrepeating_substring
from .valid_intersecting_brackets import valid_intersecting_brackets
from .two_sum import two_sum

def main():
    numbers = [1, 2, 5, 7, 4, 5, 0, 49, 29, 19]
    [first, second] = two_sum(10, numbers)
    print(f"The indexes of sum are {first} and {second}\n")

    input = "aloikjhjasdfyhuiiouehjfgopwq;ewrdfgjwqdp[ovmwpeoirkjfvcwq;olkdjvsa;dlqwertyuiopaSDFGHJKLkgjkfs[v[vqerpokrvfg";
    output = longest_nonrepeating_substring(input)
    print(f"longest substring is: \n{output}\n")

    strings = ["{{}<[>]}", "{{", "]]", "<<{>{[}>(}])"]
    for string in strings:
        if valid_intersecting_brackets(string):
            print(string, "is a valid input")
        else:
            print(string, "is an invalid input")
