#ifndef LISTINDEXOUTOFBOUNDS_HPP
#define LISTINDEXOUTOFBOUNDS_HPP

#include <string>

class ListIndexOutOfBounds : public std::exception {
  std::string message;

 public:
  ListIndexOutOfBounds()
      : message("Error: Attempted access at an index out of bounds.") {}

  ListIndexOutOfBounds(const std::size_t index)
      : message("Error: Attempted access at index " + std::to_string(index) + ", which is out of bounds.") {}

  ListIndexOutOfBounds(const std::size_t index, const std::size_t size)
      : message("Error: Attempted access at index " + std::to_string(index) + ", which is out of bounds [0, " + std::to_string(size) + ").") {}

  virtual const char *what() const throw() { return message.c_str(); }
};

#endif