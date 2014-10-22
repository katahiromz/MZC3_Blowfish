////////////////////////////////////////////////////////////////////////////
// Blowfish.hpp -- Blowfish encrypter and decrypter
// This file is part of MZC3.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef __MZC3_BLOWFISH_HPP__
#define __MZC3_BLOWFISH_HPP__

////////////////////////////////////////////////////////////////////////////
// constants

#define bf_pa_size      18
#define bf_s_boxes      4
#define bf_num_entries  256
#define bf_string       256
#define bf_passwd       56

////////////////////////////////////////////////////////////////////////////
// little endian or big endian?

#if !defined(MZC_LITTLE_ENDIAN) && !defined(MZC_BIG_ENDIAN)
    #if defined(_WIN32) || defined(MSDOS)
        #define MZC_LITTLE_ENDIAN
    #else
        #define MZC_BIG_ENDIAN
    #endif
#endif

#if defined(MZC_LITTLE_ENDIAN) && defined(MZC_BIG_ENDIAN)
    #error You lose!
#endif

////////////////////////////////////////////////////////////////////////////
// structures

#ifdef MZC_LITTLE_ENDIAN
    struct BF_4Bytes
    {
        unsigned long three:8;
        unsigned long two:8;
        unsigned long one:8;
        unsigned long zero:8;
    };
#endif
#ifdef MZC_BIG_ENDIAN
    struct BF_4Bytes
    {
        unsigned long zero:8;
        unsigned long one:8;
        unsigned long two:8;
        unsigned long three:8;
    };
#endif

union BF_Dword
{
    unsigned long dword;
    BF_4Bytes bytes;
};

struct BF_QWord
{
    BF_Dword dword0;
    BF_Dword dword1;
};

////////////////////////////////////////////////////////////////////////////
// MBlowfish

class MBlowfish EXTENDS_MOBJECT
{
public:
    MBlowfish();
    MBlowfish(const char *passwd);
    virtual ~MBlowfish();

    void SetPassword(const char *passwd);
    void SetPassword(const char *passwd, std::size_t len);

    // NOTE: Parameter bytes of Encrypt method must be a multiple of 8.
    bool Encrypt(void *ptr, long bytes);
    // NOTE: Parameter bytes of Decrypt method must be a multiple of 8.
    bool Decrypt(void *ptr, long bytes);

    // NOTE: EncryptWithLength requires delete[] after call.
    unsigned char *EncryptWithLength(const void *ptr, long& length);
    // NOTE: DecryptWithLength requires delete[] after call.
             char *DecryptWithLength(const void *ptr, long& length);

    void Reset();

protected:
    unsigned long m_pa[bf_pa_size];
    unsigned long m_sb[bf_s_boxes][bf_num_entries];

    void _SetPassword0(const char *passwd);
    void _SetPassword0(const char *passwd, std::size_t len);
    void _Enc(BF_Dword *x1, BF_Dword *x2);
    void _Dec(BF_Dword *x1, BF_Dword *x2);
};

////////////////////////////////////////////////////////////////////////////

#ifndef MZC_NO_INLINING
    #undef MZC_INLINE
    #define MZC_INLINE inline
    #include "Blowfish_inl.hpp"
#endif

#endif  // ndef __MZC3_BLOWFISH_HPP__
