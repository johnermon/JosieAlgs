from typing import List

def two_sum(target:int, input:List[int]) -> List[int]|None:
    numbers:dict = {}
    for i, curr in enumerate(input):
        complement = target - curr
        if complement in numbers:
            return [numbers.pop(complement), i]
        numbers[curr] = i
    return None
