#include "13.39.h"
#include <memory>
#include <string>
#include <utility>
#include <vector>

using std::string;
using std::allocator;
using std::pair;

// allocmust be defined in the StrVec implmentation file
allocator<string> StrVec::alloc;

void StrVec::push_back(const string &s) {
  chk_n_alloc(); // ensure that there is room for another element
  // construct a copy of s in the element to which first_free points
  alloc.construct(first_free++, s);
}

void StrVec::pop_back() {
  if (size()) {
    alloc.destroy(--first_free);
  }
}

pair<string *, string *> StrVec::alloc_n_copy(const string *b,
                                              const string *e) {
  // allocate space to hold as many elements as are in the range
  auto data = alloc.allocate(e - b);
  // initialize and return a pair constructed from data and
  // the value returned by uninitialized_copy
  return {data, uninitialized_copy(b, e, data)};
}

void StrVec::free() {
  // may not pass deallocate a 0 pointer; if elements is 0, there’s no work to
  // do
  if (elements) {
    // destroy the old elements in reverse order
    for (auto p = first_free; p != elements; /* empty */)
      alloc.destroy(--p);
    alloc.deallocate(elements, cap - elements);
  }
}

StrVec::StrVec(const StrVec &s) {
  // call alloc_n_copy to allocate exactly as many elements as in s
  auto newdata = alloc_n_copy(s.begin(), s.end());
  elements = newdata.first;
  first_free = cap = newdata.second;
}

StrVec::~StrVec() { free(); }

StrVec &StrVec::operator=(const StrVec &rhs) {
  // call alloc_n_copy to allocate exactly as many elements as in rhs
  auto data = alloc_n_copy(rhs.begin(), rhs.end());
  free();
  elements = data.first;
  first_free = cap = data.second;
  return *this;
}

void StrVec::alloc_n_move(const size_t new_cap) {
  auto newdata = alloc.allocate(new_cap);
  auto dest = newdata;
  auto elem = elements;
  for (size_t i = 0; i != size();
       ++i) // copy old size() elements to memory pointed by newdata
    alloc.construct(dest++, std::move(*elem++));
  // after loop, dest - newdata == old size(), size() remain unchanged but
  // capacity change
  free();

  elements = newdata;
  first_free = dest;
  cap = newdata + new_cap;
}

void StrVec::reallocate() {
  // we’ll allocate space for twice as many elements as the current size
  auto newcapacity = size() ? 2 * size() : 1;
  // allocate new memory
  auto newdata = alloc.allocate(newcapacity);
  // move the data from the old memory to the new
  auto dest = newdata;  // points to the next free position in the new array
  auto elem = elements; // points to the next element in the old array
  for (size_t i = 0; i != size(); ++i)
    alloc.construct(dest++, std::move(*elem++));
  free(); // free the old space once we’ve moved the elements
  // update our data structure to point to the new elements
  elements = newdata;
  first_free = dest;
  cap = elements + newcapacity;
}

void StrVec::resize(const size_t n) {
  if (n > size()) {
    while (size() < n) {
      push_back(string());
    }
  } else if (n < size()) {
    while (size() > n) {
      pop_back();
    }
  }
}

void StrVec::reserve(const size_t new_cap) {
  if (capacity() < new_cap) {
  }
}
