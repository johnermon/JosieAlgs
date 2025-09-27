///Parses input string to look for pairs. worst case scenerio this could be a very slow algorithm,
///however in most use cases where there are roughly evenly spaced brackets it is more than fast
///enough. mem copy operations in most cases you only need to copy a couple elements and check a
///couple elements behind in the vector, Importantly, each time a match is found the element is
///removed from the stack
pub fn valid_intersecting_brackets(input: &'static str) -> bool {
    //creates stack, vector with capacity of the input length
    let mut stack = Vec::with_capacity(input.len());
    //iterates through the input string as chars
    'outer: for curr in input.chars() {
        //if curr is any opening bracket type then push to stack and continue
        if curr == '(' || curr == '{' || curr == '[' || curr == '<' {
            stack.push(curr);
            continue;
        }
        //match close bracket types to their corresponding opening bracket
        //otherwise continue
        let open = match curr {
            ')' => '(',
            '}' => '{',
            ']' => '[',
            '>' => '<',
            _ => continue,
        };
        //iterate backwards through stack backwards until you find the correct bracket.
        //once found remove it and continue the outer loop
        for i in (0..stack.len()).rev() {
            if open == stack[i] {
                let _ = stack.remove(i);
                continue 'outer;
            }
        }
        //if the previous for loop ever completes it means there is
        //unmatched closing bracket, failing and return false
        return false;
    }
    //if the stack is not empty at the end of operation it means
    //unmatched opening bracket, meaning invalid input
    stack.is_empty()
}
