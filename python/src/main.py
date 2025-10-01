from .longest_nonrepeating_substring import longest_nonrepeating_substring

def main():
    input = "aloikjhjasdfyhuiiouehjfgopwq;ewrdfgjwqdp[ovmwpeoirkjfvcwq;olkdjvsa;dlqwertyuiopaSDFGHJKLkgjkfs[v[vqerpokrvfg";
    output = longest_nonrepeating_substring(input)
    print(f"longest substring is: \n{output}\n")
