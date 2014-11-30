////////////////////////////////////////////////////////////////////////////
// Blowfish_inl.hpp -- Blowfish encrypter and decrypter
// This file is part of MZC3.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

MZC_INLINE MBlowfish::MBlowfish()
{
    Reset();
}

MZC_INLINE MBlowfish::MBlowfish(const char *passwd)
{
    SetPassword(passwd);
}

MZC_INLINE MBlowfish::MBlowfish(const char *passwd, std::size_t len)
{
    SetPassword(passwd, len);
}

MZC_INLINE /*virtual*/ MBlowfish::~MBlowfish()
{
}

MZC_INLINE void MBlowfish::SetPassword(const char *passwd)
{
    using namespace std;
    size_t len = (passwd ? strlen(passwd) : 0);
    SetPassword(passwd, len);
}

MZC_INLINE void MBlowfish::SetPassword(const char *passwd, std::size_t len)
{
    Reset();
    if (len > 0)
        _SetPassword0(passwd, len);
}

MZC_INLINE void MBlowfish::_SetPassword0(const char *passwd)
{
    using namespace std;
    _SetPassword0(passwd, (passwd ? strlen(passwd) : 0));
}

////////////////////////////////////////////////////////////////////////////
