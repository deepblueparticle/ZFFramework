/* ====================================================================== *
 * Copyright (c) 2010-2018 ZFFramework
 * Github repo: https://github.com/ZFFramework/ZFFramework
 * Home page: http://ZFFramework.com
 * Blog: http://zsaber.com
 * Contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/LICENSE
 * ====================================================================== */
/**
 * @file ZFCoreTypeDef_StringType.h
 * @brief types for ZFFramework
 */

#ifndef _ZFI_ZFCoreTypeDef_StringType_h_
#define _ZFI_ZFCoreTypeDef_StringType_h_

#include "ZFCoreString.h"

ZF_NAMESPACE_GLOBAL_BEGIN

/** @brief see #_zfstr */
#ifndef _ZFT_zfstringA
    typedef ZFCoreStringA zfstringA;
#else
    typedef _ZFT_zfstringA zfstringA;
#endif

/** @brief see #_zfstr */
#ifndef _ZFT_zfstringW
    typedef ZFCoreStringW zfstringW;
#else
    typedef _ZFT_zfstringW zfstringW;
#endif

/** @brief see #_zfstr */
#ifndef _ZFT_zfstring
    typedef ZFCoreString zfstring;
#else
    typedef _ZFT_zfstring zfstring;
#endif

// ============================================================
/**
 * @brief wrapper to convert string types to char types
 *
 * usage:
 * @code
 *   zfwrapStringToChar<zfstring>::CharType c; // zfchar type
 *   zfwrapStringToChar<zfstringA>::CharType cA; // zfcharA type
 *   zfwrapStringToChar<zfstringW>::CharType cW; // zfcharW type
 * @endcode
 */
template<typename T_Str>
struct ZF_ENV_EXPORT zfwrapStringToChar
{
public:
    /** @brief see #zfwrapStringToChar */
    typedef void CharType;
};
/**
 * @brief wrapper to convert char types to string types
 *
 * usage:
 * @code
 *   zfwrapCharToString<zfchar>::StringType s; // zfstring type
 *   zfwrapCharToString<zfcharA>::StringType sA; // zfstringA type
 *   zfwrapCharToString<zfcharW>::StringType sW; // zfstringW type
 * @endcode
 */
template<typename T_Char>
struct ZF_ENV_EXPORT zfwrapCharToString
{
public:
    /** @brief see #zfwrapCharToString */
    typedef void StringType;
};

// ============================================================
/** @cond ZFPrivateDoc */
template<>
struct ZF_ENV_EXPORT zfwrapStringToChar<zfstring>
{
public:
    typedef zfchar CharType;
};
template<>
struct ZF_ENV_EXPORT zfwrapCharToString<zfchar>
{
public:
    typedef zfstring StringType;
};
#if !ZF_ENV_ZFCHAR_USE_CHAR_A
    template<>
    struct ZF_ENV_EXPORT zfwrapStringToChar<zfstringA>
    {
    public:
        typedef zfcharA CharType;
    };
    template<>
    struct ZF_ENV_EXPORT zfwrapCharToString<zfcharA>
    {
    public:
        typedef zfstringA StringType;
    };
#endif // #if !ZF_ENV_ZFCHAR_USE_CHAR_A
#if !ZF_ENV_ZFCHAR_USE_CHAR_W
    template<>
    struct ZF_ENV_EXPORT zfwrapStringToChar<zfstringW>
    {
    public:
        typedef zfcharW CharType;
    };
    template<>
    struct ZF_ENV_EXPORT zfwrapCharToString<zfcharW>
    {
    public:
        typedef zfstringW StringType;
    };
#endif // #if !ZF_ENV_ZFCHAR_USE_CHAR_W
/** @endcond */

ZF_NAMESPACE_GLOBAL_END

#endif // #ifndef _ZFI_ZFCoreTypeDef_StringType_h_

