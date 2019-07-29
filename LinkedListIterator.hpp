#ifndef LINKEDLISTITERATOR_HPP
#define LINKEDLISTITERATOR_HPP

#include "Node.hpp"

template <typename T>
  class LinkedListIterator {
   public:
    LinkedListIterator(Node<T>* start) : current(start) {}
    LinkedListIterator<T>& operator++() {
      this->current = this->current->next;
    }
    T& operator*() const {
      return this->current->data;
    }
    const bool operator==(const Node<T>* other) const {
      return this->current == other;
    }
    const bool operator!=(const Node<T>* other) const {
      return this->current != other;
    }
   private:
    Node<T>* current;
  };

#endif