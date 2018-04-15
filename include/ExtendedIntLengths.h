#pragma once

template<unsigned int t>
class UnsignedExtendedInt;


template<unsigned int t>
class SignedExtendedInt;


template<unsigned int t, unsigned int u>
struct extIntReturnSize {
public:
  static const unsigned int multipleOf32BitsMax_ = t > u ? t : u;
  static const unsigned int multipleOf32BitsMin_ = t > u ? u : t;
  static const unsigned int multipleOf32BitsTot_ = t + u;
  using uIntReturnTypeMax_ = UnsignedExtendedInt<multipleOf32BitsMax_>;
  using uIntReturnTypeMin_ = UnsignedExtendedInt<multipleOf32BitsMin_>;
  using uIntReturnTypeTot_ = UnsignedExtendedInt<multipleOf32BitsTot_>;
  using intReturnTypeMax_ = SignedExtendedInt<multipleOf32BitsMax_>;
  using intReturnTypeMin_ = SignedExtendedInt<multipleOf32BitsMin_>;
  using intReturnTypeTot_ = SignedExtendedInt<multipleOf32BitsTot_>;
};
