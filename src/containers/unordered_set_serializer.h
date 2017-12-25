#ifndef HPS_UNORDERED_SET_SERIALIZER_H_
#define HPS_UNORDERED_SET_SERIALIZER_H_

#include <iostream>
#include <unordered_set>
#include "../basic_types/uint_serializer.h"
#include "../serializer.h"

namespace hps {

template <class T>
class Serializer<std::unordered_set<T>> {
 public:
  static void serialize(const std::unordered_set<T>& container, OutputBuffer& ob) {
    Serializer<size_t>::serialize(container.size(), ob);
    for (const T& elem : container) {
      Serializer<T>::serialize(elem, ob);
    }
  }

  static void parse(std::unordered_set<T>& container, InputBuffer& ib) {
    size_t n_elems;
    Serializer<size_t>::parse(n_elems, ib);
    container.clear();
    container.reserve(n_elems);
    T elem;
    for (size_t i = 0; i < n_elems; i++) {
      Serializer<T>::parse(elem, ib);
      container.insert(std::move(elem));
    }
  }
};

}  // namespace hps

#endif