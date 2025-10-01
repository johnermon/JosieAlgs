from .longest_nonrepeating_substring import longest_nonrepeating_substring
from .valid_intersecting_brackets import valid_intersecting_brackets

def main():
    input = "aloikjhjasdfyhuiiouehjfgopwq;ewrdfgjwqdp[ovmwpeoirkjfvcwq;olkdjvsa;dlqwertyuiopaSDFGHJKLkgjkfs[v[vqerpokrvfg";
    output = longest_nonrepeating_substring(input)
    print(f"longest substring is: \n{output}\n")
    strings = ["{{}<[>]}", "{{", "]]", "<<{>{[}>(}])"]
    for string in strings:
        if valid_intersecting_brackets(string):
            print(string, "is a valid input")
        else:
            print(string, "is an invalid input")
