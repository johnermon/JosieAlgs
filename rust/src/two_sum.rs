use std::collections::HashMap;

///Looks for the indexes in an array where both add up to the target value
pub fn two_sum(target: i32, input: &[i32]) -> Option<(usize, usize)> {
    //numbers is a hashmap of all numbers so far along with
    let mut numbers = HashMap::new();
    //iterates through the entire list and enumerates list
    for (i, &curr) in input.iter().enumerate() {
        //lets the complement of the current number be the target value minus the curent
        let complement = target - curr;
        //pulls the index of the complement out of the hashmap
        let complement_index = numbers.get(&complement);
        //if the index exists in the hashmap break the loop and set the pair to be equal to the
        //inex and the current index
        if let Some(complement_index) = complement_index {
            return Some((*complement_index, i));
        }
        //inserts current index into the hashmap
        numbers.insert(curr, i);
    }
    None
}
