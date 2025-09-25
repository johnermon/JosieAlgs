use std::collections::HashMap;

///Looks for the indexes in an array where both add up to the target value
pub fn two_sum(target: u32, input: &[u32]) {
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
