use std::ops::Range;

pub fn longest_nonrepeating_substring(input: &'static str) -> &'static str {
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
                println!(
                    "{} {}",
                    longest_substring_index.start, longest_substring_index.end
                );
            }
            //sets current substring to be equal to i,  resetting current window
            curr_substring = i;
        }
        //sets the current index to some(i)
        *char_index = Some(i)
    }
    &input[longest_substring_index]
}
