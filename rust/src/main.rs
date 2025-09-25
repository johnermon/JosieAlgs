pub mod longest_nonrepeating_substring;
pub mod two_sum;
pub mod valid_brackets;

use longest_nonrepeating_substring::longest_nonrepeating_substring;
use two_sum::two_sum;
use valid_brackets::valid_brackets;

fn main() {
    let input: [u32; _] = [1, 2, 5, 7, 4, 5, 0, 49, 29, 19];
    two_sum(10, &input);
    let input: &'static str = "aloikjhjasdfyhui iouehjfgopwq;ewrdfgjwqdp[ovmwpeoirkjfvcwq;olkdjvsa;dlqwertyuiopaSDFGHJKLkgjkfs[v[vqerpokrvfg";
    longest_nonrepeating_substring(input);
    let strings: [&str; _] = ["{{}<[>]}", "{{", "]]", "<<{>{[}>(}])"];
    for string in strings {
        if valid_brackets(string) {
            println!("{} is a valid input", string);
        } else {
            println!("{} is an invalid input", string);
        }
    }
}
