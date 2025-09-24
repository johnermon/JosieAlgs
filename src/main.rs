use std::{collections::HashMap, ops::Range};

fn main() {
    let input: [u32; _] = [1, 2, 5, 7, 4, 5, 0, 49, 29, 19];
    sum_indexes(10, &input);
    let input: &'static str = "aloikjhjasdfyhui iouehjfgopwq;ewrdfgjwqdp[ovmwpeoirkjfvcwq;olkdjvsa;dlqwertyuiopaSDFGHJKLkgjkfs[v[vqerpokrvfg";
    longest_nonrepeating_substring(input);
    valid_parentheses("{([)]}");
}

///Parses input string to look for pairs. worst case scenerio this could be a very slow algorithm,
///however in most use cases where there are roughly evenly spaced brackets it is more than fast
///enough. mem copy operations in most cases you only need to copy a couple elements and check a
///couple elements behind in the vector, Importantly, each time a match is found the element is
///removed from the stack
fn valid_parentheses(input: &'static str) {
    //creates vector to hold all the parentheses
    let mut stack: Vec<char> = Vec::with_capacity(input.len());
    //outer for loop iterates through all the characters in the string
    'outer: for curr_char in input.chars() {
        //if the current character is any type of open parentheses then push it to the stack, then
        //continues at the beginning of the loop
        if curr_char == '(' || curr_char == '{' || curr_char == '[' {
            stack.push(curr_char);
            continue;
        }
        //if it is any close brackets match to the proper open brackets, else continue
        let open_bracets = match curr_char {
            ')' => '(',
            '}' => '{',
            ']' => '[',
            _ => continue,
        };
        //iterates backwards through the stack looking for the open brackets. if found, removes at
        //that index and continues the outer for loop
        for i in (0..stack.len()).rev() {
            if open_bracets == stack[i] {
                let _ = stack.remove(i);
                continue 'outer;
            }
        }
        //if the for loop is ever completed, that means no open brackets were found, immediately
        //failing tests
        break;
    }
    //checks on exit if there are any items left in the stack that means that there are unclosed
    //brackets: fail.
    if stack.last().is_none() {
        println!("Valid Input");
    } else {
        println!("Invalid Input");
    }
}

//finds the index of a sum that equals to
fn sum_indexes(target: u32, input: &[u32]) {
    //numbers is a hashmap of all numbers so far along with
    let mut numbers = HashMap::new();
    //this is the pair of numbers which add up to the target
    let mut pair = (0, 0);
    //iterates through the entire list and enumerates list
    for (i, &curr) in input.iter().enumerate() {
        //lets the complement of the current number be the target value minus the curent
        let complement = target - curr;
        //pulls the index of the complement out of the hashmap
        let complement_index = numbers.get(&complement);
        //if the index exists in the hashmap break the loop and set the pair to be equal to the
        //inex and the current index
        if let Some(index) = complement_index {
            pair = (*index, i);
            break;
        }
        //inserts current index into the hashmap
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
