#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdint.h>
#include "order.hpp"

#define tBASE         0xFF // тег базовой строки
#define tORDER        0XAA
#define tDISTRIBUTION 0XBB  

class basic_message
{
public:
  enum { header_length = 1 };
  enum { tag_length = 1 };
  enum { max_body_length = 255 };

  basic_message()
    : body_length_(0)
  {
  }

  const uint8_t* data() const
  {
    return data_;
  }

  uint8_t* data()
  {
    return data_;
  }

  std::size_t length() const
  {
    return header_length + body_length_ + tag_length;
  }

  const uint8_t* body() const
  {
    return data_ + header_length + tag_length;
  }

  uint8_t* body()
  {
    return data_ + header_length + tag_length;
  }

  std::size_t body_length() const
  {
    return body_length_;
  }

  void body_length(std::size_t new_length)
  {
    body_length_ = new_length;
    if (body_length_ > max_body_length)
      body_length_ = max_body_length;
  }

  bool decode_header()
  {
    body_length_ = data_[0];
    if (body_length_ > max_body_length) {
      body_length_ = 0;
      return false;
    }
    return true;
  }

  void encode_header()
  {
    data_[0] = body_length_;
  }

  bool decode_tag()
  {
    if (data_[header_length] != tBASE) {
      return false;
    }
    return true;
  }

  void encode_tag()
  {
    data_[header_length] = tBASE;
  }

protected:
  uint8_t data_[header_length + max_body_length];
  uint8_t body_length_;
};
