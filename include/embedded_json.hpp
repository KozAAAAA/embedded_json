

// #pragma once

#include <array>
#include <stdexcept>
#include <string>
#include <utility>

namespace embeddedjson {

template <std::size_t U>
class Json {
 public:
  Json() : json_empty{true} { append_char('{'); }
  Json(const Json&) = delete;
  Json& operator=(const Json&) = delete;
  ~Json() {}

  void clear() {
    json_empty = true;
    json_str.reset();
    append_char('{');
  }

  template <typename T>
  void add(const std::string_view key, const T value) {
    // "key": value,
    append_key_prefix(key);
    append_string(convert_to_chars(value));
  }

  template <typename T, std::size_t S>
  void add(const std::string_view key, const std::array<T, S>& values) {
    // "key":[value1, value2, value3]
    bool array_empty = true;
    append_key_prefix(key);
    append_char('[');
    for (auto v : values) {
      if (array_empty) {
        array_empty = false;
      } else {
        append_char(',');
      }
      append_string(convert_to_chars(v));
    }
    append_char(']');
  }

  std::pair<const char*, std::size_t> get_as_c_array() {
    append_char('}');
    return std::make_pair(json_str.data(), json_str.size());
  }

 private:
  template <typename T, std::size_t S>
  class static_vector;

  static_vector<char, U> json_str;
  bool json_empty;

  inline void append_char(const char c) { json_str.push_back(c); }

  inline void append_string(const std::string_view str) {
    for (auto c : str) {
      append_char(c);
    }
  }

  void append_key_prefix(const std::string_view key) {
    if (json_empty) {
      json_empty = false;
    } else {
      append_char(',');
    }
    append_char('"');
    append_string(key);
    append_char('"');
    append_char(':');
  }

  template <typename T>
  std::string_view convert_to_chars(T value) {
    (void)value;
    return "val";
  }
};

template <std::size_t U>
template <typename T, std::size_t S>
class Json<U>::static_vector {
 public:
  static_vector() : write_index{0} {}
  static_vector(const static_vector&) = delete;
  static_vector& operator=(const static_vector&) = delete;
  ~static_vector() {}
  void push_back(const T val) {
    if (write_index > (S - 1)) {
      throw std::overflow_error("Not enough space allocated");
    }
    buffer[write_index] = val;
    write_index++;
  }
  void reset() { write_index = 0; }
  const T* data() { return buffer.data(); }
  std::size_t size() { return write_index; }

 private:
  std::size_t write_index;
  inline static std::array<T, S> buffer{0};
};

}  // namespace embeddedjson
