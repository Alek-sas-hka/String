#pragma once
#include <cstring>
#include <iostream>
#include <vector>

class String {
 public:
  String();
  String(size_t size, char character);
  String(const char* c_style_string);
  String(const String& src_string);
  ~String();
  void Swap(String& other);
  void PushBack(const char& character);
  void PopBack();
  bool Full() const;
  bool Empty() const;
  void Clear();
  size_t Size() const;
  size_t Capacity() const;
  char Front() const;
  char& Front();
  char Back() const;
  char& Back();
  const char* Data() const;
  char* Data();
  size_t GetSize() const;
  size_t GetCapacity() const;
  char* GetString() const;
  void ShrinkToFit();
  String& operator=(const String& src_string);
  friend bool operator<(const String& left, const String& right);
  friend bool operator>(const String& left, const String& right);
  friend bool operator>=(const String& left, const String& right);
  friend bool operator<=(const String& left, const String& right);
  friend bool operator==(const String& left, const String& right);
  friend bool operator!=(const String& left, const String& right);
  char operator[](const size_t& idx) const;
  char& operator[](const size_t& idx);
  void Resize(size_t new_size);
  void Resize(size_t new_size, char character);
  void Reserve(size_t new_cap);
  friend String operator+(const String& left, const String& right);
  friend String operator*(const String& src, size_t number);
  String& operator+=(const String& right);
  String& operator*=(size_t number);
  friend std::ostream& operator<<(std::ostream& os, const String& src);
  friend std::istream& operator>>(std::istream& is, String& dst);
  std::vector<String> Split(const String& delim = " ");
  String Join(const std::vector<String>& strings);

 private:
  size_t size_;
  size_t capacity_;
  char* string_;
};
