from typing import TypeVar, Generic

T = TypeVar("T")

#i really dont like the way in which python obscures pointers, this shouldnt work, and yet it does
class JosieLinkedList(Generic[T]):
    def __init__(self):
        self.list:_JosieLinkedListSegment[T] | None = None
        self.tail_ptr:_JosieLinkedListSegment[T] | None = None
        self.length:int = 0

    def push_back(self, element:T):
        segment = _JosieLinkedListSegment[T](element)
        self.length +=1

        if self.list == None:
            self.list = segment
            self.tail_ptr = segment
            return

        assert self.tail_ptr is not None
        self.tail_ptr.ptr = segment
        self.tail_ptr = segment

    def push_front(self, element:T):
        segment = _JosieLinkedListSegment[T](element)
        self.length +=1
        segment.ptr = self.list
        self.list = segment

    def reverse(self):
        if self.list != None:
            original = self.list.ptr
            reversed = self.list
            reversed.ptr = None
            self.tail_ptr = reversed
            while original != None:
                next = original.ptr
                original.ptr = reversed
                reversed = original
                original = next
            self.list = reversed

    def len(self) -> int:
        return self.length

    def is_empty(self) -> bool:
        return self.length == 0

    def __iter__(self):
        return _JosieLinkedListIter[T](self.list)

class _JosieLinkedListSegment(Generic[T]):
    def __init__(self, data:T):
        self.data:T = data
        self.ptr:_JosieLinkedListSegment[T] | None = None

class _JosieLinkedListIter(Generic[T]):
    def __init__(self, segment:_JosieLinkedListSegment[T] | None):
        self.segment = segment

    def __next__(self) -> T:
        if self.segment == None:
            raise StopIteration
        out = self.segment.data
        self.segment = self.segment.ptr
        return out
