#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <stddef.h>
#include <initializer_list>
#include "ListIndexOutOfBounds.hpp"
#include "Node.hpp"

template <class T>
class LinkedList {
 public:
  LinkedList();
  LinkedList(const T&);
  LinkedList(const std::initializer_list<T>);
  const T& getHead() const;
  const bool isEmpty() const;
  const std::size_t length() const;
  void append(const T&);
  void prepend(const T&);
  void insert(const T&, const std::size_t);
  T unappend();
  T unprepend();
  T remove(const std::size_t);
  void remove(const T&, const std::size_t);

  bool operator==(const LinkedList&) const;
  bool operator!=(const LinkedList&) const;
  const T& operator[](const std::size_t) const;
  T& operator[](const std::size_t);

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
};

template <class T>
LinkedList<T>::LinkedList() : head(nullptr) {}

template <class T>
LinkedList<T>::LinkedList(const T& data) : head(new Node<T>(data)) {}

template <class T>
LinkedList<T>::LinkedList(const std::initializer_list<T> args) : head(nullptr) {
  for (auto it = std::rbegin(args); it != std::rend(args); ++it)
    this->prepend(*it);
}

template <class T>
const bool LinkedList<T>::isEmpty() const {
  return this->head == nullptr;
}

template <class T>
const T& LinkedList<T>::getHead() const {
  if (this->isEmpty()) throw ListIndexOutOfBounds();
  return this->head->data;
}

template <class T>
const std::size_t LinkedList<T>::length() const {
  std::size_t size = 0;
  Node<T>* current = this->head;
  while (current) {
    ++size;
    current = current->next;
  }
  return size;
}

template <class T>
void LinkedList<T>::append(const T& data) {
  if (this->isEmpty())
    this->head = new Node<T>(data);
  else {
    Node<T>* current = this->head;
    while (current->next) current = current->next;
    current->next = new Node<T>(data);
  }
}

template <class T>
void LinkedList<T>::prepend(const T& data) {
  Node<T>* front = new Node<T>(data);
  front->next = this->head;
  this->head = front;
}

template <class T>
void LinkedList<T>::insert(const T& data, const std::size_t index) {
  if (index == 0)
    this->prepend(data);
  else {
    std::size_t position = 0;
    Node<T>* prior = this->head;
    while (position < index - 1 && prior) {
      ++position;
      prior = prior->next;
    }
    if (position < index - 1) throw ListIndexOutOfBounds(index, position);
    Node<T>* in = new Node<T>(data);
    in->next = prior->next;
    prior->next = in;
  }
}

template <class T>
T LinkedList<T>::unappend() {
  if (this->isEmpty())
    throw ListIndexOutOfBounds(0, 0);
  else {
    Node<T>* current = this->head;
    while (current->next->next) current = current->next;
    T data = current->next->data;
    delete current->next;
    current->next = nullptr;
    return data;
  }
}

template <class T>
T LinkedList<T>::unprepend() {
  if (this->isEmpty())
    throw ListIndexOutOfBounds(0, 0);
  else {
    Node<T>* front = this->head->next;
    this->head->next = nullptr;
    T data = this->head->data;
    delete this->head;
    this->head = front;
    return data;
  }
}

template <class T>
T LinkedList<T>::remove(const std::size_t index) {
  if (index == 0)
    this->unprepend();
  else {
    std::size_t position = 0;
    Node<T>* prior = this->head;
    while (position < index - 1 && prior) {
      ++position;
      prior = prior->next;
    }
    if (position < index - 1) throw ListIndexOutOfBounds(index, position);
    Node<T>* out = prior->next;
    prior->next = prior->next->next;
    out->next = nullptr;
    T data = out->data;
    delete out;
    return data;
  }
}

template <class T>
void LinkedList<T>::remove(const T& data, const std::size_t num) {
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
    while (numRemoved < num && current) {
      if (current->data == data) {
        previous->next = current->next;
        delete current;
        current = previous->next;
        ++numRemoved;
      } else {
        previous = previous->next;
        current = current->next;
      }
    }
  }
}

template <class T>
bool LinkedList<T>::operator==(const LinkedList<T>& other) const {
  if (this == &other) return true;
  Node<T>* thisCurrent = this->head;
  Node<T>* otherCurrent = other.head;
  while (thisCurrent && otherCurrent) {
    if (thisCurrent->data != otherCurrent->data) return false;
    thisCurrent = thisCurrent->next;
    otherCurrent = otherCurrent->next;
  }
  if (thisCurrent || otherCurrent) return false;
  return true;
}

template <class T>
bool LinkedList<T>::operator!=(const LinkedList& other) const {
  return !this->operator==(other);
}

template <class T>
const T& LinkedList<T>::operator[](const std::size_t index) const {
  Node<T>* current = this->head;
  std::size_t position = 0;
  while (position < index && current) {
    current = current->next;
    ++position;
  }
  if (current) return current->data;
  throw ListIndexOutOfBounds(index, position);
}

template <class T>
T& LinkedList<T>::operator[](const std::size_t index) {
  Node<T>* current = this->head;
  std::size_t position = 0;
  while (position < index && current) {
    current = current->next;
    ++position;
  }
  if (current) return current->data;
  throw ListIndexOutOfBounds(index, position);
}

#endif