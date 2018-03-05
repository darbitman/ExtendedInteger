#ifndef _EXTENDEDINTLENGTHS_H_
#define _EXTENDEDINTLENGTHS_H_

template<unsigned int t, unsigned int u>
struct extIntReturnSize {};

template<unsigned int t>
class UnsignedExtendedInt;

template<>
struct extIntReturnSize<4, 4> {
public:
    static const unsigned int multipleOf32BitsMax_ = 4;
    static const unsigned int multipleOf32BitsMin_ = 4;
    static const unsigned int multipleOf32BitsTot_ = 8;
    using returnTypeMax_ = UnsignedExtendedInt<multipleOf32BitsMax_>;
    using returnTypeMin_ = UnsignedExtendedInt<multipleOf32BitsMin_>;
    using returnTypeTot_ = UnsignedExtendedInt<multipleOf32BitsTot_>;
};

template<>
struct extIntReturnSize<8, 8> {
public:
    static const unsigned int multipleOf32BitsMax_ = 8;
    static const unsigned int multipleOf32BitsMin_ = 8;
    static const unsigned int multipleOf32BitsTot_ = 16;
    using returnTypeMax_ = UnsignedExtendedInt<multipleOf32BitsMax_>;
    using returnTypeMin_ = UnsignedExtendedInt<multipleOf32BitsMin_>;
    using returnTypeTot_ = UnsignedExtendedInt<multipleOf32BitsTot_>;
};

template<>
struct extIntReturnSize<12, 12> {
public:
    static const unsigned int multipleOf32BitsMax_ = 12;
    static const unsigned int multipleOf32BitsMin_ = 12;
    static const unsigned int multipleOf32BitsTot_ = 24;
    using returnTypeMax_ = UnsignedExtendedInt<multipleOf32BitsMax_>;
    using returnTypeMin_ = UnsignedExtendedInt<multipleOf32BitsMin_>;
    using returnTypeTot_ = UnsignedExtendedInt<multipleOf32BitsTot_>;
};

template<>
struct extIntReturnSize<4, 8> {
public:
    static const unsigned int multipleOf32BitsMax_ = 8;
    static const unsigned int multipleOf32BitsMin_ = 4;
    static const unsigned int multipleOf32BitsTot_ = 12;
    using returnTypeMax_ = UnsignedExtendedInt<multipleOf32BitsMax_>;
    using returnTypeMin_ = UnsignedExtendedInt<multipleOf32BitsMin_>;
    using returnTypeTot_ = UnsignedExtendedInt<multipleOf32BitsTot_>;
};

template<>
struct extIntReturnSize<4, 12> {
public:
    static const unsigned int multipleOf32BitsMax_ = 12;
    static const unsigned int multipleOf32BitsMin_ = 4;
    static const unsigned int multipleOf32BitsTot_ = 16;
    using returnTypeMax_ = UnsignedExtendedInt<multipleOf32BitsMax_>;
    using returnTypeMin_ = UnsignedExtendedInt<multipleOf32BitsMin_>;
    using returnTypeTot_ = UnsignedExtendedInt<multipleOf32BitsTot_>;
};

template<>
struct extIntReturnSize<8, 4> {
public:
    static const unsigned int multipleOf32BitsMax_ = 8;
    static const unsigned int multipleOf32BitsMin_ = 4;
    static const unsigned int multipleOf32BitsTot_ = 12;
    using returnTypeMax_ = UnsignedExtendedInt<multipleOf32BitsMax_>;
    using returnTypeMin_ = UnsignedExtendedInt<multipleOf32BitsMin_>;
    using returnTypeTot_ = UnsignedExtendedInt<multipleOf32BitsTot_>;
};

template<>
struct extIntReturnSize<8, 12> {
public:
    static const unsigned int multipleOf32BitsMax_ = 12;
    static const unsigned int multipleOf32BitsMin_ = 8;
    static const unsigned int multipleOf32BitsTot_ = 20;
    using returnTypeMax_ = UnsignedExtendedInt<multipleOf32BitsMax_>;
    using returnTypeMin_ = UnsignedExtendedInt<multipleOf32BitsMin_>;
    using returnTypeTot_ = UnsignedExtendedInt<multipleOf32BitsTot_>;
};

template<>
struct extIntReturnSize<12, 4> {
public:
    static const unsigned int multipleOf32BitsMax_ = 12;
    static const unsigned int multipleOf32BitsMin_ = 4;
    static const unsigned int multipleOf32BitsTot_ = 16;
    using returnTypeMax_ = UnsignedExtendedInt<multipleOf32BitsMax_>;
    using returnTypeMin_ = UnsignedExtendedInt<multipleOf32BitsMin_>;
    using returnTypeTot_ = UnsignedExtendedInt<multipleOf32BitsTot_>;
};

template<>
struct extIntReturnSize<12, 8> {
public:
    static const unsigned int multipleOf32BitsMax_ = 12;
    static const unsigned int multipleOf32BitsMin_ = 8;
    static const unsigned int multipleOf32BitsTot_ = 20;
    using returnTypeMax_ = UnsignedExtendedInt<multipleOf32BitsMax_>;
    using returnTypeMin_ = UnsignedExtendedInt<multipleOf32BitsMin_>;
    using returnTypeTot_ = UnsignedExtendedInt<multipleOf32BitsTot_>;
};


#endif
