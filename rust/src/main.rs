pub mod longest_nonrepeating_substring;
pub mod reverse_linked_list;
pub mod two_sum;
pub mod valid_intersecting_brackets;

use longest_nonrepeating_substring::longest_nonrepeating_substring;
use two_sum::two_sum;
use valid_intersecting_brackets::valid_intersecting_brackets;

use crate::reverse_linked_list::JosieLinkedList;

fn main() {
    print!("Hello from Rust!");
    let mut list = JosieLinkedList::new();
    for i in 0..=10 {
        list.push_back(i);
    }

    for i in list.iter() {
        println!("{i}");
    }

    list.reverse();
    for i in list.iter() {
        println!("{i}");
    }
    let numbers: [i32; _] = [1, 2, 5, 7, 4, 5, 0, 49, 29, 19];
    //rust syntax is so much more expressive than all the other languages, all this functionality
    //in one line of code when all the other languages were more verbose... amazing
    if let Some(sum) = two_sum(10, &numbers) {
        println!("The indexes of sum are {} and {}\n", sum.0, sum.1);
    } else {
        println!("there is no pair of numbers that equal to target")
    }

    let input: &'static str = "aloikjhjasdfyhui iouehjfgopwq;ewrdfgjwqdp[ovmwpeoirkjfvcwq;olkdjvsa;dlqwertyuiopaSDFGHJKLkgjkfs[v[vqerpokrvfg";
    let out: &'static str = longest_nonrepeating_substring(input);

    println!("longest substring is: \n{out}\n");
    let strings: [&str; _] = ["{{}<[>]}", "{{", "]]", "<<{>{[}>(}])"];
    for string in strings {
        if valid_intersecting_brackets(string) {
            println!("{} is a valid input", string);
        } else {
            println!("{} is an invalid input", string);
        }
    }
}
