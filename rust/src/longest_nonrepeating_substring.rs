pub fn longest_nonrepeating_substring(input: &'static str) -> &'static str {
    //the range in the string where the longest substring lives
    let mut longest_start: usize = 0;
    let mut longest_end: usize = 0;
    let mut curr_start: usize = 0;

    //array containing optional instances of the last index where each character was seen
    let mut char_indexes: [Option<usize>; 128] = [None; 128];

    //iterates from zero until the length of the input string
    for (i, curr) in input.bytes().enumerate() {
        let char_index = &mut char_indexes[curr as usize];

        if let Some(char) = *char_index
            && char >= curr_start
        {
            //checks if the current substring is longer than the previous max substring. if so sets max substring to be equal to current substring
            if i - curr_start > longest_end - longest_start {
                longest_start = curr_start;
                longest_end = i;
            }

            curr_start = i;
        }

        //sets the current index to some(i)
        *char_index = Some(i)
    }

    &input[longest_start..longest_end]
}
