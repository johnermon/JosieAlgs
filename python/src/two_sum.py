from typing import List

def two_sum(target:int, input:List[int]) -> List[int]|None:
    numbers:dict[int, int] = {}
    for i, curr in enumerate(input):
        complement = target - curr
        if (complement_index := numbers.get(complement)) is not None:
            return [complement_index, i]
        numbers[curr] = i
    return None
