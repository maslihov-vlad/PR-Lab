#pragma once 
#include "message.hpp"

class order_message : public basic_message
{
public :
  bool decode_tag()
  {
    if (data_[header_length] != tORDER) {
      return false;
    }
    return true;
  }

  void encode_tag()
  {
    data_[header_length] = tORDER;
  }

  bool decode_header()
  {
    body_length_ = data_[0];
    if (body_length_ > MAX_SIZEOF_ORDER && body_length_ < MIN_SIZEOF_ORDER) {
      body_length_ = 0;
      return false;
    }
    return true;
  }

  void encode_header()
  {
    data_[0] = body_length_;
  }

};