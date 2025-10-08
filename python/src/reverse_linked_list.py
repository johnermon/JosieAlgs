from typing import TypeVar, Generic
T = TypeVar("T")

class JosieLinkedList(Generic[T]):
    def __init__(self):
        self.list:JosieLinkedListSegment[T] | None = None
        self.tail_ptr:JosieLinkedListSegment[T] | None = None
        self.length:int = 0

    def push_back(self, element:T):
        segment = JosieLinkedListSegment[T](element)
        self.length +=1

        if self.list == None:
            self.list = segment
            self.tail_ptr = segment
            return

        assert self.tail_ptr is not None
        self.tail_ptr.ptr = segment
        self.tail_ptr = segment

    def push_front(self, element:T):
        segment = JosieLinkedListSegment[T](element)
        self.length +=1
        segment.ptr = self.list
        self.list = segment

    def reverse(self):
        if self.length != 0:
            assert self.list is not None
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
    def len(self):
        return self.length

    def is_empty(self):
        return self.length == 0

    def __iter__(self):
        return JosieLinkedListIter[T](self.list)

class JosieLinkedListSegment(Generic[T]):
    def __init__(self, data:T):
        self.data:T = data
        self.ptr:JosieLinkedListSegment[T] | None = None

class JosieLinkedListIter(Generic[T]):
    def __init__(self, segment:JosieLinkedListSegment[T] | None):
        self.segment = segment

    def __next__(self):
        if self.segment == None:
            raise StopIteration
        out = self.segment.data
        self.segment = self.segment.ptr
        return out
