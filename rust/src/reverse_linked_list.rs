use std::{
    alloc::{Layout, alloc, dealloc},
    ptr::{self, drop_in_place, null_mut, write},
};

pub struct JosieLinkedList<T> {
    list: *mut JosieLinkedListSegment<T>,
    length: usize,
    tail_ptr: *mut JosieLinkedListSegment<T>,
}

impl<T> Drop for JosieLinkedList<T> {
    fn drop(&mut self) {
        unsafe {
            let mut next = self.list;
            while !next.is_null() {
                drop_in_place(&mut (*next).data);
                let to_dealloc = next;
                next = (*next).ptr;
                dealloc(
                    to_dealloc as *mut u8,
                    Layout::new::<JosieLinkedListSegment<T>>(),
                );
            }
        }
    }
}

struct JosieLinkedListSegment<T> {
    ptr: *mut JosieLinkedListSegment<T>,
    data: T,
}

impl<T> JosieLinkedListSegment<T> {
    fn new(element: T) -> *mut Self {
        unsafe {
            let ptr =
                alloc(Layout::new::<JosieLinkedListSegment<T>>()) as *mut JosieLinkedListSegment<T>;
            ptr.is_null().then(|| panic!("Alloc failed"));
            (*ptr).ptr = null_mut();
            ptr::write(&mut (*ptr).data, element);
            ptr
        }
    }
}

impl<T> JosieLinkedList<T> {
    pub fn new() -> Self {
        Self::default()
    }

    pub fn push_back(&mut self, element: T) {
        let segment = JosieLinkedListSegment::new(element);

        self.length += 1;
        if self.list.is_null() {
            self.list = segment;
            self.tail_ptr = segment;
            return;
        }

        unsafe {
            (*self.tail_ptr).ptr = segment;
            self.tail_ptr = segment;
        }
    }

    pub fn push_front(&mut self, element: T) {
        let segment = JosieLinkedListSegment::new(element);
        self.length += 1;
        unsafe {
            (*segment).ptr = self.list;
        }
        self.list = segment;
    }

    pub fn reverse(&mut self) {
        if !self.list.is_null() {
            unsafe {
                let mut original = (*self.list).ptr;
                let mut reversed = self.list;
                (*reversed).ptr = null_mut();
                self.tail_ptr = reversed;
                while !original.is_null() {
                    let next = (*original).ptr;
                    (*original).ptr = reversed;
                    reversed = original;
                    original = next;
                }
                self.list = reversed;
            }
        }
    }

    pub fn iter_mut<'a>(&'a mut self) -> JosieLinkedListIterMut<'a, T> {
        JosieLinkedListIterMut {
            segment: self.list,
            _list: self,
        }
    }

    pub fn iter<'a>(&'a self) -> JosieLinkedListIter<'a, T> {
        JosieLinkedListIter {
            _list: self,
            segment: self.list,
        }
    }

    pub const fn len(&self) -> usize {
        self.length
    }

    pub const fn is_empty(&self) -> bool {
        self.length == 0
    }
}

pub struct JosieLinkedListIterMut<'a, T> {
    _list: &'a mut JosieLinkedList<T>,
    segment: *mut JosieLinkedListSegment<T>,
}

impl<'a, T> Iterator for JosieLinkedListIterMut<'a, T> {
    type Item = &'a mut T;

    fn next(&mut self) -> Option<&'a mut T> {
        if self.segment.is_null() {
            return None;
        }
        unsafe {
            let out = &mut (*self.segment).data;
            self.segment = (*self.segment).ptr;
            Some(out)
        }
    }
}

pub struct JosieLinkedListIter<'a, T> {
    _list: &'a JosieLinkedList<T>,
    segment: *mut JosieLinkedListSegment<T>,
}

impl<'a, T> Iterator for JosieLinkedListIter<'a, T> {
    type Item = &'a T;

    fn next(&mut self) -> Option<&'a T> {
        if self.segment.is_null() {
            return None;
        }
        unsafe {
            let out = &(*self.segment).data;
            self.segment = (*self.segment).ptr;
            Some(out)
        }
    }
}

impl<T> Default for JosieLinkedList<T> {
    fn default() -> Self {
        Self {
            list: ptr::null_mut(),
            length: 0,
            tail_ptr: ptr::null_mut(),
        }
    }
}
