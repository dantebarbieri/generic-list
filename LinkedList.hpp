#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <stddef.h>
#include <initializer_list>
#include "LinkedListIterator.hpp"
#include "ListIndexOutOfBounds.hpp"
#include "Node.hpp"

template <typename T>
class LinkedList {
 public:
  // Constructors
  LinkedList();
  LinkedList(const T&);
  LinkedList(const std::initializer_list<T>);

  // Getters
  const T& getHead() const;
  const T& getTail() const;
  const bool isEmpty() const;
  const bool contains(const T&) const;
  const std::size_t size() const;

  // Mutators
  LinkedList<T>& append(const T&);
  LinkedList<T>& prepend(const T&);
  LinkedList<T>& insert(const T&, const std::size_t);
  T unappend();
  T unprepend();
  T remove(const std::size_t);
  LinkedList<T>& remove(const T&, const std::size_t);

  // Iterators
  LinkedListIterator<T> begin() const;
  const Node<T>* end() const;

  // Operators
  const bool operator==(const LinkedList&) const;
  const bool operator!=(const LinkedList&) const;
  const T& operator[](const std::size_t) const;
  T& operator[](const std::size_t);

  // Friend Operator
  friend std::ostream& operator<<(std::ostream& output,
                                  const LinkedList& self) {
    Node<T>* current = self.head;
    output << "[";
    if (current) {
      while (current->next) {
        output << current->data << "->";
        current = current->next;
      }
      output << current->data;
    }
    output << "]";
    return output;
  }

 private:
  Node<T>* head;
  Node<T>* tail;
  std::size_t length;
};

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), length(0) {}

template <typename T>
LinkedList<T>::LinkedList(const T& data)
    : head(new Node<T>(data)), tail(this->head), length(1) {}

template <typename T>
LinkedList<T>::LinkedList(const std::initializer_list<T> args)
    : head(nullptr), tail(nullptr), length(0) {
  for (auto it = std::rbegin(args); it != std::rend(args); ++it) {
    this->prepend(*it);
    ++this->length;
  }
}

template <typename T>
const bool LinkedList<T>::isEmpty() const {
  return this->head == nullptr && this->tail == nullptr;
}

template <typename T>
const bool LinkedList<T>::contains(const T& data) const {
  return this->head == nullptr;
}

template <typename T>
const T& LinkedList<T>::getHead() const {
  if (this->isEmpty()) throw ListIndexOutOfBounds();
  return this->head->data;
}

template <typename T>
const T& LinkedList<T>::getTail() const {
  if (this->isEmpty()) throw ListIndexOutOfBounds();
  return this->tail->data;
}

template <typename T>
const std::size_t LinkedList<T>::size() const {
  return this->length;
}

template <typename T>
LinkedList<T>& LinkedList<T>::append(const T& data) {
  if (this->isEmpty()) {
    this->head = new Node<T>(data);
    this->tail = this->head;
  } else {
    this->tail->next = new Node<T>(data);
    this->tail = this->tail->next;
  }
  ++this->length;
  return *this;
}

template <typename T>
LinkedList<T>& LinkedList<T>::prepend(const T& data) {
  Node<T>* front = new Node<T>(data);
  front->next = this->head;
  if (this->isEmpty()) this->tail = front;
  this->head = front;
  ++this->length;
  return *this;
}

template <typename T>
LinkedList<T>& LinkedList<T>::insert(const T& data, const std::size_t index) {
  if (index > this->length) throw ListIndexOutOfBounds(index, this->length);
  if (index == 0)
    return this->prepend(data);
  else if (index == this->length)
    return this->append(data);
  else {
    std::size_t position = 0;
    Node<T>* prior = this->head;
    while (position < index - 1) {
      ++position;
      prior = prior->next;
    }
    Node<T>* toAdd = new Node<T>(data);
    toAdd->next = prior->next;
    prior->next = toAdd;
    ++this->length;
  }
  return *this;
}

template <typename T>
T LinkedList<T>::unappend() {
  if (this->isEmpty())
    throw ListIndexOutOfBounds(0, 0);
  else if (this->length == 1) {
    T data = this->head->data;
    delete this->head;
    this->head = nullptr;
    this->tail = nullptr;
    --this->length;
    return data;
  } else {
    Node<T>* current = this->head;
    while (current->next->next) current = current->next;
    T data = this->tail->data;
    delete this->tail;
    this->tail = current;
    --this->length;
    return data;
  }
}

template <typename T>
T LinkedList<T>::unprepend() {
  if (this->isEmpty())
    throw ListIndexOutOfBounds(0, 0);
  else if (this->length == 1) {
    T data = this->head->data;
    delete this->tail;
    this->head = nullptr;
    this->tail = nullptr;
    --this->length;
    return data;
  } else {
    Node<T>* front = this->head->next;
    this->head->next = nullptr;
    T data = this->head->data;
    delete this->head;
    this->head = front;
    --this->length;
    return data;
  }
}

template <typename T>
T LinkedList<T>::remove(const std::size_t index) {
  if (index > this->length)
    throw ListIndexOutOfBounds(index, this->length);
  else if (index == 0)
    return this->unprepend();
  else if (index == this->length)
    return this->unappend();
  else {
    std::size_t position = 0;
    Node<T>* prior = this->head;
    while (position < index - 1) {
      ++position;
      prior = prior->next;
    }
    Node<T>* out = prior->next;
    prior->next = prior->next->next;
    out->next = nullptr;
    T data = out->data;
    delete out;
    return data;
  }
}

template <typename T>
LinkedList<T>& LinkedList<T>::remove(const T& data, const std::size_t num) {
  Node<T>* current = this->head;
  std::size_t numRemoved = 0;
  while (numRemoved < num && current && current->data == data) {
    this->head = current->next;
    delete current;
    current = this->head;
    ++numRemoved;
  }
  if (current) {
    Node<T>* previous = current;
    current = current->next;
    while (numRemoved < num && current)
      if (current->data == data) {
        previous->next = current->next;
        if (this->tail == current) this->tail = previous;
        delete current;
        current = previous->next;
        ++numRemoved;
      } else {
        previous = previous->next;
        current = current->next;
      }
  }
  this->length -= numRemoved;
  return *this;
}

template <typename T>
LinkedListIterator<T> LinkedList<T>::begin() const {
  return LinkedListIterator<T>(this->head);
}

template <typename T>
const Node<T>* LinkedList<T>::end() const {
  return this->tail;
}

template <typename T>
const bool LinkedList<T>::operator==(const LinkedList<T>& other) const {
  if (this == &other) return true;
  if (this->tail->data != other.tail->data || this->length != other.length)
    return false;
  Node<T>* thisCurrent = this->head;
  Node<T>* otherCurrent = other.head;
  while (thisCurrent && otherCurrent) {
    if (thisCurrent->data != otherCurrent->data) return false;
    thisCurrent = thisCurrent->next;
    otherCurrent = otherCurrent->next;
  }
  return !(thisCurrent || otherCurrent);
}

template <typename T>
const bool LinkedList<T>::operator!=(const LinkedList& other) const {
  return !this->operator==(other);
}

template <typename T>
const T& LinkedList<T>::operator[](const std::size_t index) const {
  if (index >= this->length)
    throw ListIndexOutOfBounds(index, this->length);
  else if (index == this->length - 1)
    return this->tail->data;
  else {
    Node<T>* current = this->head;
    std::size_t position = 0;
    while (position < index) {
      current = current->next;
      ++position;
    }
    return current->data;
  }
}

template <typename T>
T& LinkedList<T>::operator[](const std::size_t index) {
  if (index >= this->length)
    throw ListIndexOutOfBounds(index, this->length);
  else if (index == this->length - 1)
    return this->tail->data;
  else {
    Node<T>* current = this->head;
    std::size_t position = 0;
    while (position < index) {
      current = current->next;
      ++position;
    }
    return current->data;
  }
}

#endif