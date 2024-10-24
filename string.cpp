#include "string.hpp"

void String::Swap(String& other) {
  std::swap(this->size_, other.size_);
  std::swap(this->capacity_, other.capacity_);
  std::swap(this->string_, other.string_);
}

size_t String::GetSize() const { return size_; }

size_t String::GetCapacity() const { return capacity_; }

char* String::GetString() const { return string_; }

String::String() {
  size_ = 0;
  capacity_ = 0;
  string_ = nullptr;
}

String::String(size_t size, char character)
    : size_(size), capacity_(size), string_(new char[size + 1]) {
  memset(string_, character, size);
  string_[size] = '\0';
}

String::String(const char* c_style_string)
    : size_(strlen(c_style_string)),
      capacity_(strlen(c_style_string)),
      string_(new char[strlen(c_style_string) + 1]) {
  if (string_ != nullptr) {
    memcpy(string_, c_style_string, size_);
    string_[size_] = '\0';
  }
}

String::String(const String& src_string)
    : size_(src_string.size_),
      capacity_(src_string.capacity_),
      string_(new char[src_string.size_ + 1]) {
  memcpy(string_, src_string.string_, size_);
  string_[size_] = '\0';
}

String& String::operator=(const String& src_string) {
  String tmp(src_string);
  this->Swap(tmp);
  return *this;
}

String::~String() {
  delete[] string_;
  capacity_ = 0;
  size_ = 0;
}

void String::Clear() { size_ = 0; }

void String::PushBack(const char& character) {
  if (this->Full()) {
    if (capacity_ == 0) {
      Reserve(1);
    } else {
      Reserve(capacity_ * 2);
    }
  }
  string_[size_] = character;
  string_[size_ + 1] = '\0';
  ++size_;
}

void String::PopBack() {
  if (this->Empty()) {
    return;
  }
  string_[size_ - 1] = '\0';
  --size_;
}

void String::Reserve(size_t new_cap) {
  if (new_cap <= capacity_) {
    return;
  }
  capacity_ = new_cap;
  char* tmp = new char[new_cap + 1];
  if (string_ != nullptr) {
    memcpy(tmp, string_, size_);
    string_[size_] = '\0';
  }
  delete[] string_;
  string_ = tmp;
}

void String::Resize(size_t new_size) {
  if (new_size > capacity_) {
    Reserve(new_size);
    size_ = new_size;
    string_[size_] = '\0';
    return;
  }
  string_[new_size] = '\0';
  size_ = new_size;
}

void String::Resize(size_t new_size, char character) {
  size_t old_size = size_;
  Resize(new_size);
  if (new_size > old_size) {
    memset(string_ + old_size - 1, character, new_size - old_size + 1);
  }
}

void String::ShrinkToFit() {
  if (capacity_ > size_) {
    capacity_ = size_;
    char* tmp = new char[size_ + 1];
    if (string_ != nullptr) {
      memcpy(tmp, string_, size_);
      string_[size_] = '\0';
    }
    delete[] string_;
    string_ = tmp;
  }
}

bool String::Full() const { return string_ == nullptr || size_ == capacity_; }

bool String::Empty() const { return string_ == nullptr || size_ == 0; }

size_t String::Size() const { return size_; }

size_t String::Capacity() const { return capacity_; }

char String::Front() const { return string_[0]; }

char& String::Front() { return string_[0]; }

char String::Back() const { return string_[size_ - 1]; }

char& String::Back() { return string_[size_ - 1]; }

char String::operator[](const size_t& idx) const { return string_[idx]; }

char& String::operator[](const size_t& idx) { return string_[idx]; }

const char* String::Data() const { return string_; }

char* String::Data() { return string_; }

bool operator<(const String& left, const String& right) {
  if (left.Empty() && right.Empty()) {
    return false;
  }
  size_t smallest_size = std::min(left.GetSize(), right.GetSize());
  if (left.GetSize() > right.GetSize()) {
    return false;
  }
  if (left.GetSize() == right.GetSize()) {
    for (size_t i = 0; i < smallest_size; ++i) {
      if (left.GetString()[i] == right.GetString()[i]) {
        continue;
      }
      if (left.GetString()[i] < right.GetString()[i]) {
        return true;
      }
    }
    if (left.GetString()[left.GetSize() - 1] ==
        right.GetString()[right.GetSize() - 1]) {
      return false;
    }
  }
  return true;
}

bool operator>(const String& left, const String& right) { return right < left; }

bool operator<=(const String& left, const String& right) {
  return !(left > right);
}

bool operator>=(const String& left, const String& right) {
  return !(left < right);
}

bool operator==(const String& left, const String& right) {
  return !(left > right) && !(left < right);
}

bool operator!=(const String& left, const String& right) {
  return (left > right) || (left < right);
}

String& String::operator+=(const String& right) {
  if (capacity_ < size_ + right.GetSize()) {
    Reserve(size_ + right.GetSize());
  }
  if (string_ != nullptr && right.GetString() != nullptr) {
    memcpy(string_ + size_, right.GetString(), right.GetSize() + 1);
    size_ += right.GetSize();
  }
  return *this;
}

String operator+(const String& left, const String& right) {
  String result = left;
  result += right;
  return result;
}

String& String::operator*=(const size_t kNumber) {
  if (kNumber == 0) {
    Resize(kNumber);
    return *this;
  }
  String src = *this;
  Reserve(size_ * kNumber);
  for (size_t i = 1; i < kNumber; ++i) {
    *this += src;
  }
  return *this;
}

String operator*(const String& src, size_t number) {
  String result = src;
  result *= number;
  return result;
}

std::ostream& operator<<(std::ostream& os, const String& src) {
  for (size_t i = 0; i < src.size_; i++) {
    os << src.string_[i];
  }
  return os;
}

std::istream& operator>>(std::istream& is, String& dst) {
  const int kOneThousand = 1000;
  char* buff = new char[kOneThousand];
  is >> buff;
  dst.size_ = strlen(buff);
  dst.string_ = new char[dst.size_ + 1];
  memcpy(dst.string_, buff, dst.size_);
  dst.string_[dst.size_] = '\0';
  dst.capacity_ = dst.size_;
  delete[] buff;
  return is;
}

std::vector<String> String::Split(const String& delim) {
  size_t delim_size = strlen(delim.string_);
  std::vector<size_t> delim_positions = {0};
  std::vector<String> result;
  char* position;
  while ((position = strstr(string_ + delim_positions.back(), delim.string_)) !=
         nullptr) {
    delim_positions.push_back(position - string_ + delim_size);
  }
  delim_positions.push_back(size_ + delim_size);
  for (size_t i = 0; i < delim_positions.size() - 1; i++) {
    size_t interval_size =
        delim_positions[i + 1] - delim_positions[i] - delim_size;
    char* tmp = new char[interval_size + 1];
    memcpy(tmp, string_ + delim_positions[i], interval_size);
    tmp[interval_size] = '\0';
    result.emplace_back(tmp);
    delete[] tmp;
  }
  return result;
}

String String::Join(const std::vector<String>& strings) {
  if (strings.empty()) {
    return {""};
  }
  String result;
  for (size_t i = 0; i < strings.size() - 1; ++i) {
    result += strings[i];
    result += string_;
  }
  result += strings[strings.size() - 1];
  return result;
}
