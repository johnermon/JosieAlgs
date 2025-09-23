use std::{collections::HashMap, ops::Range};

fn main() {
    let input: [u32; _] = [1, 2, 5, 7, 4, 5, 0, 49, 29, 19];
    sum_indexes(10, &input);
    let input: &'static str = "aloikjhjasdfyhui iouehjfgopwq;ewrdfgjwqdp[ovmwpeoirkjfvcwq;olkdjvsa;dlqwertyuiopaSDFGHJKLkgjkfs[v[vqerpokrvfg";
    longest_nonrepeating_substring(input);
}

//finds the index of a sum that equals to
fn sum_indexes(target: u32, input: &[u32]) {
    //numbers is a hashmap of all numbers so far along with
    let mut numbers = HashMap::new();
    let mut pair = (0, 0);
    for i in 0..input.len() {
        let curr = input[i];
        let complement = target - curr;
        let complement_index = numbers.get(&complement);
        if let Some(index) = complement_index {
            pair = (*index, i);
            break;
        }
        numbers.insert(curr, i);
    }
    println!("the index of the sum is {:?}", pair);
}

//finds the longest substring of unique charactrers in input can only contain ascii characters as the ascii codepoint doubles as the index in the char indexes arraty
fn longest_nonrepeating_substring(input: &'static str) {
    //the range in the string where the longest substring lives
    let mut longest_substring_index: Range<usize> = 0..0;
    //curr substring is the index of the current substring loaded in memory
    let mut curr_substring: usize = 0;
    //array containing optional instances of the last index where each character was seen
    let mut char_indexes: [Option<usize>; 128] = [None; 128];
    //iterates from zero until the length of the input string
    for i in 0..input.len() {
        //index is the current ascii codepoint as bytes
        let index = input.as_bytes()[i] as usize;
        //char index is a mutable reference to the index in the array where the current ascii character is located at
        let char_index = &mut char_indexes[index];
        //checks if the character currently exists in the charindexes index, and if that character is at a greater than or equal index to the curr substring index
        if let Some(char) = *char_index
            && char >= curr_substring
        {
            //checks if the current substring is longer than the previous max substring. if so sets max substring to be equal to current substring
            if i - curr_substring > longest_substring_index.end - longest_substring_index.start {
                longest_substring_index = curr_substring..i;
            }
            //sets current substring to be equal to i,  resetting current window
            curr_substring = i;
        }
        //sets the current index to some(i)
        *char_index = Some(i)
    }
    //prints out the longest substring
    println!(
        "Longest Unique Substring is {:?}",
        &input[longest_substring_index]
    );
}
