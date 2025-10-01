def longest_nonrepeating_substring(input:str) -> str:
    longest_start = 0
    longest_end = 0
    curr_start = 0
    char_indexes:list[int|None] = [None] * 128
    for i, curr in enumerate(input):
        index = ord(curr)
        char_index = char_indexes[index]
        if char_index is not None and char_index >= curr_start:
            if i - curr_start > longest_end - longest_start:
                longest_start = curr_start
                longest_end = i
            curr_start = i
        char_indexes[index] = i

    return input[longest_start:longest_end]
