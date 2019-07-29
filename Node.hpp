#ifndef NODE_HPP
#define NODE_HPP

template <typename T>
struct Node {
  T data;
  Node* next;
  Node(const T&);

  friend std::ostream& operator<<(std::ostream& output, const Node& self) {
    output << "Data: " << self.data << "Next: " << self.next;
    return output;
  }
};

template <typename T>
Node<T>::Node(const T& data) : data(data), next(nullptr) {}

#endif