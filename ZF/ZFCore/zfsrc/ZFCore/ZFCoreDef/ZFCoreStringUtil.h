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
 * @file ZFCoreStringUtil.h
 * @brief string utilities for ZFFramework
 */

#ifndef _ZFI_ZFCoreStringUtil_h_
#define _ZFI_ZFCoreStringUtil_h_

#include "ZFCoreTypeDef.h"

ZF_NAMESPACE_GLOBAL_BEGIN

/**
 * @brief convert between zfchar/zfcharA/zfcharW, support ASCII chars only
 *
 * for internal use only, use ZFString for encoding convertion in your app instead
 * @warning support ASCII chars only (0x00 ~ 0x7F)
 * @warning return value would be deleted after line end,
 *   you must not save it directly,
 *   store it in a std::string or ZFString if necessary
 */
template<typename T_CharSrc, typename T_StrDst>
ZF_ENV_EXPORT T_StrDst zfsCoreStringConvert(const T_CharSrc *s)
{
    T_StrDst ret;
    if(s != zfnull)
    {
        while(*s != '\0')
        {
            ret += (zfcharA)(*s);
            ++s;
        }
    }
    return ret;
}

/**
 * @def zfsCoreW2A
 * @brief see #zfsCoreStringConvert
 * @def zfsCoreA2W
 * @brief see #zfsCoreStringConvert
 * @def zfsCoreZ2A
 * @brief see #zfsCoreStringConvert
 * @def zfsCoreA2Z
 * @brief see #zfsCoreStringConvert
 * @def zfsCoreZ2W
 * @brief see #zfsCoreStringConvert
 * @def zfsCoreW2Z
 * @brief see #zfsCoreStringConvert
 */
#define zfsCoreW2A(s) (zfsCoreStringConvert<zfcharW, zfstringA>(s).cString())
#define zfsCoreA2W(s) (zfsCoreStringConvert<zfcharA, zfstringW>(s).cString())
#if ZF_ENV_ZFCHAR_USE_CHAR_A
    #define zfsCoreZ2A(s) (s)
    #define zfsCoreA2Z(s) (s)
    #define zfsCoreZ2W(s) zfsCoreA2W(s)
    #define zfsCoreW2Z(s) zfsCoreW2A(s)
#endif
#if ZF_ENV_ZFCHAR_USE_CHAR_W
    #define zfsCoreZ2A(s) zfsCoreW2A(s)
    #define zfsCoreA2Z(s) zfsCoreA2W(s)
    #define zfsCoreZ2W(s) (s)
    #define zfsCoreW2Z(s) (s)
#endif

// ============================================================
/**
 * @brief convert integer number (int, long, etc) to string
 *
 * integer number can be signed or unsigned,
 * whatever your compiler support\n
 * typical usage:
 * @code
 *   zfstring s = ...;
 *   zfint n = ...;
 *
 *   // append result to s and return it as result,
 *   // template is specified by param type
 *   zfsFromIntT(s, n);
 *
 *   // return a new zfstring as result,
 *   // string template type is manually specified
 *   zfsFromInt<zfstring>(n);
 *
 *   // return a new zfstring as result,
 *   // string template type is specified default to zfstring
 *   zfsFromInt(n);
 * @endcode
 */
template<typename T_Str, typename T_Int>
ZF_ENV_EXPORT zfbool zfsFromIntT(ZF_OUT T_Str &s,
                                 ZF_IN T_Int n,
                                 ZF_IN_OPT zfindex radix = 10,
                                 ZF_IN_OPT zfbool useUpperCase = zftrue)
{
    if(radix < 2 || radix > 36) {return zffalse;}

    if(n <= (T_Int)0)
    {
        // tricks to solve the unsigned type warnings
        if(n != (T_Int)0)
        {
            s += '-';
            n = (T_Int)0 - n;
        }
        else
        {
            s += '0';
            return zftrue;
        }
    }
    else if(n == (T_Int)-1)
    {
        s += '-';
        s += '1';
        return zftrue;
    }

    unsigned long long e = 1;
    while(n / e) {e *= radix;}

    const zfcharA *token = useUpperCase
        ? ZFTOKEN_zfcharA_UPPERCASE
        : ZFTOKEN_zfcharA_LOWERCASE;
    while(e /= radix)
    {
        s += token[n / e];
        n %= e;
    }
    return zftrue;
}
/**
 * @brief see #zfsFromIntT
 */
template<typename T_Str, typename T_Int>
ZF_ENV_EXPORT T_Str zfsFromInt(ZF_IN T_Int n,
                               ZF_IN_OPT zfindex radix = 10,
                               ZF_IN_OPT zfbool useUpperCase = zftrue)
{
    T_Str s;
    zfsFromIntT<T_Str, T_Int>(s, n, radix, useUpperCase);
    return s;
}
/**
 * @brief see #zfsFromIntT
 */
template<typename T_Int>
ZF_ENV_EXPORT zfstring zfsFromInt(ZF_IN T_Int n,
                                  ZF_IN_OPT zfindex radix = 10,
                                  ZF_IN_OPT zfbool useUpperCase = zftrue)
{
    zfstring s;
    zfsFromIntT<zfstring, T_Int>(s, n, radix, useUpperCase);
    return s;
}

// ============================================================
/**
 * @brief convert string to int, return error position if failed,
 *   or null if success
 *
 * it's your responsibility to make sure the template int type is correct,
 * otherwise, the result may be unexpected
 * (for example, specify a short int type while numbers in src is too long)
 */
template<typename T_Int, typename T_Char>
ZF_ENV_EXPORT zfbool zfsToIntT(ZF_OUT T_Int &ret,
                               ZF_IN const T_Char *src,
                               ZF_IN_OPT zfindex srcLen = zfindexMax(),
                               ZF_IN_OPT zfindex radix = 10,
                               ZF_IN_OPT zfbool allowNegative = zftrue,
                               ZF_OUT_OPT const zfchar **outErrorPos = zfnull)
{
    if(src == zfnull || srcLen == 0 || radix < 2 || radix > 36)
    {
        if(outErrorPos != zfnull)
        {
            *outErrorPos = src;
        }
        return zffalse;
    }

    ret = 0;
    const T_Char *p = src;
    const T_Char *pEnd = ((srcLen == zfindexMax()) ? (p - 1) : (p + srcLen));
    zfbool negative = zffalse;
    if(*p == '-')
    {
        if(!allowNegative)
        {
            if(outErrorPos != zfnull)
            {
                *outErrorPos = p;
            }
            return zffalse;
        }
        negative = zftrue;
        ++p;
    }
    while(*p != '\0' && p != pEnd)
    {
        zfuint tmp = 0;
        if(*p >= '0' && *p <= '9') {tmp = *p - '0';}
        else if(*p >= 'a' && *p <= 'z') {tmp = 10 + *p - 'a';}
        else if(*p >= 'A' && *p <= 'Z') {tmp = 10 + *p - 'A';}
        else {break;}
        if(tmp >= radix) {break;}
        ret = (T_Int)((ret * (zfuint)radix) + tmp);
        ++p;
    }
    if(negative)
    {
        ret = (T_Int)0 - ret;
    }

    if(*p == '\0' || p == pEnd)
    {
        return zftrue;
    }
    else
    {
        if(outErrorPos != zfnull)
        {
            *outErrorPos = p;
        }
        return zffalse;
    }
}
/**
 * @brief see #zfsToIntT
 */
template<typename T_Int, typename T_Char>
ZF_ENV_EXPORT T_Int zfsToInt(ZF_IN const T_Char *src,
                             ZF_IN_OPT zfindex srcLen = zfindexMax(),
                             ZF_IN_OPT zfindex radix = 10,
                             ZF_IN_OPT zfbool allowNegative = zftrue,
                             ZF_OUT_OPT const T_Char **outErrorPos = zfnull)
{
    T_Int ret = 0;
    zfsToIntT(ret, src, srcLen, radix, allowNegative, outErrorPos);
    return ret;
}
/**
 * @brief see #zfsToIntT
 */
template<typename T_Char>
ZF_ENV_EXPORT zfint zfsToInt(ZF_IN const T_Char *src,
                             ZF_IN_OPT zfindex srcLen = zfindexMax(),
                             ZF_IN_OPT zfindex radix = 10,
                             ZF_IN_OPT zfbool allowNegative = zftrue,
                             ZF_OUT_OPT const T_Char **outErrorPos = zfnull)
{
    return zfsToInt<zfint, T_Char>(src, srcLen, radix, allowNegative, outErrorPos);
}

// ============================================================
/**
 * @brief convert float number (int, long, etc) to string
 *
 * float number can be any type such as float, double, long double,
 * whatever your compiler support\n
 * for typical usage, see #zfsFromIntT
 */
template<typename T_Str, typename T_Float>
ZF_ENV_EXPORT zfbool zfsFromFloatT(ZF_OUT T_Str &s,
                                   ZF_IN T_Float n,
                                   ZF_IN_OPT zfindex decimalLenOrMax = zfindexMax())
{
    if(n == 0)
    {
        s += '0';
        return zftrue;
    }
    if(n < 0)
    {
        s += '-';
        n = 0 - n;
    }

    zfsFromIntT(s, (unsigned long)n);
    s += '.';
    n -= (unsigned long)n;

    unsigned long t;
    if(decimalLenOrMax == zfindexMax())
    {
        if(sizeof(T_Float) <= 4) {t = (unsigned long)(n * 10000);}
        else if(sizeof(T_Float) <= 8) {t = (unsigned long)(n * 1000000);}
        else {t = (unsigned long)(n * 100000000);}
        if(t > 0)
        {
            while((t % 10) == 0) {t /= 10;}
        }
    }
    else
    {
        unsigned long e = 1;
        for(zfindex i = 0; i < decimalLenOrMax; ++i)
        {
            e *= 10;
        }
        t = (unsigned long)(n * e);
    }
    zfsFromIntT(s, t);
    return zftrue;
}
/**
 * @brief see #zfsFromFloatT
 */
template<typename T_Str, typename T_Float>
ZF_ENV_EXPORT T_Str zfsFromFloat(ZF_IN T_Float n,
                                 ZF_IN_OPT zfindex decimalLenOrMax = zfindexMax())
{
    T_Str s;
    zfsFromFloatT<T_Str, T_Float>(s, n, decimalLenOrMax);
    return s;
}
/**
 * @brief see #zfsFromFloatT
 */
template<typename T_Float>
ZF_ENV_EXPORT zfstring zfsFromFloat(ZF_IN T_Float n,
                                    ZF_IN_OPT zfindex decimalLenOrMax = zfindexMax())
{
    zfstring s;
    zfsFromFloatT<zfstring, T_Float>(s, n, decimalLenOrMax);
    return s;
}

// ============================================================
/**
 * @brief convert string to float
 *
 * it's your responsibility to make sure int type is correct,
 * otherwise, the result may be unexpected\n
 * for typical usage, see #zfsToIntT
 * @note if src is null, pErrPos would be null
 */
template<typename T_Float, typename T_Char>
ZF_ENV_EXPORT zfbool zfsToFloatT(ZF_OUT T_Float &ret,
                                 ZF_IN const T_Char *src,
                                 ZF_IN_OPT zfindex srcLen = zfindexMax(),
                                 ZF_OUT_OPT const T_Char **outErrorPos = zfnull)
{
    if(src == zfnull || srcLen == 0)
    {
        if(outErrorPos != zfnull)
        {
            *outErrorPos = src;
        }
        return zffalse;
    }

    ret = 0;
    const T_Char *p = src;
    const T_Char *pEnd = ((srcLen == zfindexMax()) ? (p - 1) : (p + srcLen));
    zfbool negative = zffalse;
    if(*p == '-')
    {
        negative = zftrue;
        ++p;
    }

    while(*p != '\0' && *p != '.' && p != pEnd)
    {
        if(*p < '0' || *p > '9') {break;}
        ret = ret * 10 + (*p - '0');
        ++p;
    }
    if(*p != '\0' && *p != '.' && p != pEnd)
    {
        if(outErrorPos != zfnull)
        {
            *outErrorPos = p;
        }
        return zffalse;
    }

    if(*p == '.')
    {
        ++p;

        unsigned long e = 10;
        while(*p != '\0' && p != pEnd
            && *p >= '0' && *p <= '9')
        {
            ret += (T_Float)(*p - '0') / e;
            e *= 10;
            ++p;
        }
        if(*p != '\0' && p != pEnd)
        {
            if(outErrorPos != zfnull)
            {
                *outErrorPos = p;
            }
            return zffalse;
        }
    }

    if(negative)
    {
        ret = 0 - ret;
    }

    if(*p == '\0' || p == pEnd)
    {
        return zftrue;
    }
    else
    {
        if(outErrorPos != zfnull)
        {
            *outErrorPos = p;
        }
        return zffalse;
    }
}
/**
 * @brief see #zfsToFloatT
 */
template<typename T_Float, typename T_Char>
ZF_ENV_EXPORT T_Float zfsToFloat(ZF_IN const T_Char *src,
                                 ZF_IN_OPT zfindex srcLen = zfindexMax(),
                                 ZF_OUT_OPT const T_Char **outErrorPos = zfnull)
{
    T_Float ret = 0;
    zfsToFloatT(ret, src, srcLen, outErrorPos);
    return ret;
}
/**
 * @brief see #zfsToFloatT
 */
template<typename T_Char>
ZF_ENV_EXPORT zffloat zfsToFloat(ZF_IN const T_Char *src,
                                 ZF_IN_OPT zfindex srcLen = zfindexMax(),
                                 ZF_OUT_OPT const T_Char **outErrorPos = zfnull)
{
    return zfsToFloat<zffloat, T_Char>(src, srcLen, outErrorPos);
}


// ============================================================
/**
 * @brief convert pointer value to string
 */
template<typename T_Str>
ZF_ENV_EXPORT zfbool zfsFromPointerT(ZF_OUT T_Str &s,
                                     ZF_IN const void *p)
{
    zfcharA buf[32] = {0};
    if(p == zfnull)
    {
        sprintf(buf, "<null>");
    }
    else
    {
        sprintf(buf, "%p", p);
    }
    const zfcharA *t = buf;
    while(*t)
    {
        s += *t++;
    }
    return zftrue;
}
/**
 * @brief see #zfsFromPointerT
 */
template<typename T_Str>
ZF_ENV_EXPORT T_Str zfsFromPointer(ZF_IN const void *p)
{
    T_Str s;
    zfsFromPointerT<T_Str>(s, p);
    return s;
}
/**
 * @brief see #zfsFromPointerT
 */
inline zfstring zfsFromPointer(ZF_IN const void *p)
{
    return zfsFromPointer<zfstring>(p);
}

// ============================================================
/**
 * @brief util to compare two c strings,
 *   while null is regarded as equal to empty string
 */
template<typename T_Char>
zfbool zfscmpTheSame(ZF_IN const T_Char *s1, ZF_IN const T_Char *s2)
{
    if(s1 == s2)
    {
        return zftrue;
    }
    else if(!s1)
    {
        return (*s2 == '\0');
    }
    else if(!s2)
    {
        return (*s1 == '\0');
    }
    else
    {
        return (zfscmpT(s1, s2) == 0);
    }
}
/**
 * @brief util to check whether string is empty (null or empty string)
 */
template<typename T_Char>
zfbool zfsIsEmpty(ZF_IN const T_Char *s1)
{
    return (s1 == zfnull || *s1 == '\0');
}

// ============================================================
/**
 * @brief util method to copy the contents of src,
 *   return null if src null, or empty string if src is empty string
 */
template<typename T_Char>
T_Char *zfsCopy(ZF_IN const T_Char *src)
{
    T_Char *ret = zfnull;
    if(src)
    {
        zfindex size = sizeof(T_Char) * (zfslenT(src) + 1);
        ret = (T_Char *)zfmalloc(size);
        zfmemcpy(ret, src, size);
    }
    return ret;
}
/**
 * @brief util method to copy the contents of src,
 *   return null if src null, or empty string if src is empty string
 */
template<typename T_Char>
T_Char *zfsCopy(ZF_IN const T_Char *src,
                ZF_IN zfindex size)
{
    T_Char *ret = zfnull;
    if(src)
    {
        if(size == zfindexMax())
        {
            size = zfslenT(src);
        }
        ret = (T_Char *)zfmalloc(sizeof(T_Char) * (size + 1));
        zfmemcpy(ret, src, sizeof(T_Char) * size);
        ret[size] = '\0';
    }
    return ret;
}
/**
 * @brief util method to free old string then copy and change to new string,
 *   free and set dst to null if src is null,
 *   otherwise, realloc and copy contents to dst
 */
template<typename T_Char>
T_Char *zfsChange(ZF_IN_OUT T_Char *&dst,
                  ZF_IN const T_Char *src)
{
    if(!src)
    {
        zffree(dst);
        dst = zfnull;
        return dst;
    }

    zfindex size = sizeof(T_Char) * (zfslenT(src) + 1);
    dst = (T_Char *)zfrealloc(dst, size);
    zfmemcpy(dst, src, size);
    return dst;
}
/**
 * @brief util method to free old string then copy and change to new string,
 *   free and set dst to null if src is null,
 *   otherwise, realloc and copy contents to dst
 */
template<typename T_Char>
T_Char *zfsChange(ZF_IN_OUT T_Char *&dst,
                  ZF_IN const T_Char *src,
                  ZF_IN zfindex size)
{
    if(!src)
    {
        zffree(dst);
        dst = zfnull;
        return dst;
    }

    if(size == zfindexMax())
    {
        size = zfslenT(src);
    }
    dst = (T_Char *)zfrealloc(dst, sizeof(T_Char) * (size + 1));
    zfmemcpy(dst, src, sizeof(T_Char) * size);
    dst[size] = '\0';
    return dst;
}
/**
 * @brief util method to append string to existing string buffer, realloc if need
 */
template<typename T_Char>
T_Char *zfsAppend(ZF_IN_OUT T_Char *&old,
                  ZF_IN const T_Char *append)
{
    if(!old)
    {
        old = zfsCopy(append);
        return old;
    }

    zfindex oldSize = zfslenT(old);
    zfindex size = sizeof(T_Char) * (oldSize + zfslenT(append) + 1);
    old = (T_Char *)zfrealloc(old, size);
    zfmemcpy(old + oldSize, append, size);
    return old;
}
/**
 * @brief util method to append string to existing string buffer, realloc if need
 */
template<typename T_Char>
T_Char *zfsAppend(ZF_IN_OUT T_Char *&old,
                  ZF_IN const T_Char *append,
                  ZF_IN zfindex size)
{
    if(!old)
    {
        old = zfsCopy(append, size);
        return old;
    }

    zfindex oldSize = zfslenT(old);
    if(size == zfindexMax())
    {
        size = zfslenT(append);
    }
    old = (T_Char *)zfrealloc(old, sizeof(T_Char) * (oldSize + size + 1));
    zfmemcpy(old + oldSize, append, sizeof(T_Char) * size);
    old[oldSize + size] = '\0';
    return old;
}

#define _ZFP_zfsConnectEndPtr ((void *)-1)
template<typename T_Char>
T_Char *_ZFP_zfsConnect(ZF_IN const T_Char *src,
                        ...)
{
    zfindex len = 0;
    va_list vaList;
    const T_Char *tmp = src;

    va_start(vaList, src);
    do
    {
        if(tmp != zfnull)
        {
            len += zfslenT(tmp);
        }
        tmp = va_arg(vaList, const T_Char *);
    } while(tmp != _ZFP_zfsConnectEndPtr);
    va_end(vaList);

    T_Char *ret = (T_Char *)zfmalloc(sizeof(T_Char) * (len + 1));
    tmp = src;
    len = 0;
    zfindex tmpLen = 0;
    va_start(vaList, src);
    do
    {
        if(tmp != zfnull)
        {
            tmpLen = zfslenT(tmp);
            zfmemcpy(ret + len, tmp, sizeof(T_Char) * tmpLen);
            len += tmpLen;
        }
        tmp = va_arg(vaList, const T_Char *);
    } while(tmp != _ZFP_zfsConnectEndPtr);
    va_end(vaList);
    ret[len] = '\0';

    return ret;
}
/**
 * @brief connect multiple strings and return a newly created string,
 *   result must be deleted by #zffree
 *
 * null string would be treated as empty string
 */
#define zfsConnect(src, ...) _ZFP_zfsConnect(src, ##__VA_ARGS__, _ZFP_zfsConnectEndPtr)

#if 1 // zfcharA version
    // ============================================================
    // zfstringFind
    /** @brief find string */
    extern ZF_ENV_EXPORT zfindex zfstringFind(ZF_IN const zfcharA *src, ZF_IN zfindex srcLen, ZF_IN const zfcharA *find, ZF_IN_OPT zfindex findLen = zfindexMax());
    /** @brief find string */
    inline zfindex zfstringFind(ZF_IN const ZFCoreStringA &src, ZF_IN const ZFCoreStringA &find)
    {
        return zfstringFind(src.cString(), src.length(), find.cString(), find.length());
    }
    /** @brief find string */
    inline zfindex zfstringFind(ZF_IN const ZFCoreStringA &src, ZF_IN const zfcharA *find, ZF_IN_OPT zfindex findLen = zfindexMax())
    {
        return zfstringFind(src.cString(), src.length(), find, findLen);
    }
    /** @brief find string */
    inline zfindex zfstringFind(ZF_IN const ZFCoreStringA &src, ZF_IN zfcharA find)
    {
        return zfstringFind(src.cString(), src.length(), &find, 1);
    }
    // ============================================================
    // zfstringFindReversely
    /** @brief find string */
    extern ZF_ENV_EXPORT zfindex zfstringFindReversely(ZF_IN const zfcharA *src, ZF_IN zfindex srcLen, ZF_IN const zfcharA *find, ZF_IN_OPT zfindex findLen = zfindexMax());
    /** @brief find string */
    inline zfindex zfstringFindReversely(ZF_IN const ZFCoreStringA &src, ZF_IN const ZFCoreStringA &find)
    {
        return zfstringFindReversely(src.cString(), src.length(), find.cString(), find.length());
    }
    /** @brief find string */
    inline zfindex zfstringFindReversely(ZF_IN const ZFCoreStringA &src, ZF_IN const zfcharA *find, ZF_IN_OPT zfindex findLen = zfindexMax())
    {
        return zfstringFindReversely(src.cString(), src.length(), find, findLen);
    }
    /** @brief find string */
    inline zfindex zfstringFindReversely(ZF_IN const ZFCoreStringA &src, ZF_IN zfcharA find)
    {
        return zfstringFindReversely(src.cString(), src.length(), &find, 1);
    }
    // ============================================================
    // zfstringFindCaseInsensitive
    /** @brief find string */
    extern ZF_ENV_EXPORT zfindex zfstringFindCaseInsensitive(ZF_IN const zfcharA *src, ZF_IN zfindex srcLen, ZF_IN const zfcharA *find, ZF_IN_OPT zfindex findLen = zfindexMax());
    /** @brief find string */
    inline zfindex zfstringFindCaseInsensitive(ZF_IN const ZFCoreStringA &src, ZF_IN const ZFCoreStringA &find)
    {
        return zfstringFindCaseInsensitive(src.cString(), src.length(), find.cString(), find.length());
    }
    /** @brief find string */
    inline zfindex zfstringFindCaseInsensitive(ZF_IN const ZFCoreStringA &src, ZF_IN const zfcharA *find, ZF_IN_OPT zfindex findLen = zfindexMax())
    {
        return zfstringFindCaseInsensitive(src.cString(), src.length(), find, findLen);
    }
    /** @brief find string */
    inline zfindex zfstringFindCaseInsensitive(ZF_IN const ZFCoreStringA &src, ZF_IN zfcharA find)
    {
        return zfstringFindCaseInsensitive(src.cString(), src.length(), &find, 1);
    }
    // ============================================================
    // zfstringFindCaseInsensitiveReversely
    /** @brief find string */
    extern ZF_ENV_EXPORT zfindex zfstringFindCaseInsensitiveReversely(ZF_IN const zfcharA *src, ZF_IN zfindex srcLen, ZF_IN const zfcharA *find, ZF_IN_OPT zfindex findLen = zfindexMax());
    /** @brief find string */
    inline zfindex zfstringFindCaseInsensitiveReversely(ZF_IN const ZFCoreStringA &src, ZF_IN const ZFCoreStringA &find)
    {
        return zfstringFindCaseInsensitiveReversely(src.cString(), src.length(), find.cString(), find.length());
    }
    /** @brief find string */
    inline zfindex zfstringFindCaseInsensitiveReversely(ZF_IN const ZFCoreStringA &src, ZF_IN const zfcharA *find, ZF_IN_OPT zfindex findLen = zfindexMax())
    {
        return zfstringFindCaseInsensitiveReversely(src.cString(), src.length(), find, findLen);
    }
    /** @brief find string */
    inline zfindex zfstringFindCaseInsensitiveReversely(ZF_IN const ZFCoreStringA &src, ZF_IN zfcharA find)
    {
        return zfstringFindCaseInsensitiveReversely(src.cString(), src.length(), &find, 1);
    }
    // ============================================================
    // zfstringFindFirstOf
    /** @brief find string */
    extern ZF_ENV_EXPORT zfindex zfstringFindFirstOf(ZF_IN const zfcharA *src, ZF_IN zfindex srcLen, ZF_IN const zfcharA *find, ZF_IN_OPT zfindex findLen = zfindexMax());
    /** @brief find string */
    inline zfindex zfstringFindFirstOf(ZF_IN const ZFCoreStringA &src, ZF_IN const ZFCoreStringA &find)
    {
        return zfstringFindFirstOf(src.cString(), src.length(), find.cString(), find.length());
    }
    /** @brief find string */
    inline zfindex zfstringFindFirstOf(ZF_IN const ZFCoreStringA &src, ZF_IN const zfcharA *find, ZF_IN_OPT zfindex findLen = zfindexMax())
    {
        return zfstringFindFirstOf(src.cString(), src.length(), find, findLen);
    }
    /** @brief find string */
    inline zfindex zfstringFindFirstOf(ZF_IN const ZFCoreStringA &src, ZF_IN zfcharA find)
    {
        return zfstringFindFirstOf(src.cString(), src.length(), &find, 1);
    }
    // ============================================================
    // zfstringFindFirstNotOf
    /** @brief find string */
    extern ZF_ENV_EXPORT zfindex zfstringFindFirstNotOf(ZF_IN const zfcharA *src, ZF_IN zfindex srcLen, ZF_IN const zfcharA *find, ZF_IN_OPT zfindex findLen = zfindexMax());
    /** @brief find string */
    inline zfindex zfstringFindFirstNotOf(ZF_IN const ZFCoreStringA &src, ZF_IN const ZFCoreStringA &find)
    {
        return zfstringFindFirstNotOf(src.cString(), src.length(), find.cString(), find.length());
    }
    /** @brief find string */
    inline zfindex zfstringFindFirstNotOf(ZF_IN const ZFCoreStringA &src, ZF_IN const zfcharA *find, ZF_IN_OPT zfindex findLen = zfindexMax())
    {
        return zfstringFindFirstNotOf(src.cString(), src.length(), find, findLen);
    }
    /** @brief find string */
    inline zfindex zfstringFindFirstNotOf(ZF_IN const ZFCoreStringA &src, ZF_IN zfcharA find)
    {
        return zfstringFindFirstNotOf(src.cString(), src.length(), &find, 1);
    }
    // ============================================================
    // zfstringFindLastOf
    /** @brief find string */
    extern ZF_ENV_EXPORT zfindex zfstringFindLastOf(ZF_IN const zfcharA *src, ZF_IN zfindex srcLen, ZF_IN const zfcharA *find, ZF_IN_OPT zfindex findLen = zfindexMax());
    /** @brief find string */
    inline zfindex zfstringFindLastOf(ZF_IN const ZFCoreStringA &src, ZF_IN const ZFCoreStringA &find)
    {
        return zfstringFindLastOf(src.cString(), src.length(), find.cString(), find.length());
    }
    /** @brief find string */
    inline zfindex zfstringFindLastOf(ZF_IN const ZFCoreStringA &src, ZF_IN const zfcharA *find, ZF_IN_OPT zfindex findLen = zfindexMax())
    {
        return zfstringFindLastOf(src.cString(), src.length(), find, findLen);
    }
    /** @brief find string */
    inline zfindex zfstringFindLastOf(ZF_IN const ZFCoreStringA &src, ZF_IN zfcharA find)
    {
        return zfstringFindLastOf(src.cString(), src.length(), &find, 1);
    }
    // ============================================================
    // zfstringFindLastNotOf
    /** @brief find string */
    extern ZF_ENV_EXPORT zfindex zfstringFindLastNotOf(ZF_IN const zfcharA *src, ZF_IN zfindex srcLen, ZF_IN const zfcharA *find, ZF_IN_OPT zfindex findLen = zfindexMax());
    /** @brief find string */
    inline zfindex zfstringFindLastNotOf(ZF_IN const ZFCoreStringA &src, ZF_IN const ZFCoreStringA &find)
    {
        return zfstringFindLastNotOf(src.cString(), src.length(), find.cString(), find.length());
    }
    /** @brief find string */
    inline zfindex zfstringFindLastNotOf(ZF_IN const ZFCoreStringA &src, ZF_IN const zfcharA *find, ZF_IN_OPT zfindex findLen = zfindexMax())
    {
        return zfstringFindLastNotOf(src.cString(), src.length(), find, findLen);
    }
    /** @brief find string */
    inline zfindex zfstringFindLastNotOf(ZF_IN const ZFCoreStringA &src, ZF_IN zfcharA find)
    {
        return zfstringFindLastNotOf(src.cString(), src.length(), &find, 1);
    }
#endif // zfcharA version
#if 1 // zfcharW version
    // ============================================================
    // zfstringFind
    /** @brief find string */
    extern ZF_ENV_EXPORT zfindex zfstringFind(ZF_IN const zfcharW *src, ZF_IN zfindex srcLen, ZF_IN const zfcharW *find, ZF_IN_OPT zfindex findLen = zfindexMax());
    /** @brief find string */
    inline zfindex zfstringFind(ZF_IN const ZFCoreStringW &src, ZF_IN const ZFCoreStringW &find)
    {
        return zfstringFind(src.cString(), src.length(), find.cString(), find.length());
    }
    /** @brief find string */
    inline zfindex zfstringFind(ZF_IN const ZFCoreStringW &src, ZF_IN const zfcharW *find, ZF_IN_OPT zfindex findLen = zfindexMax())
    {
        return zfstringFind(src.cString(), src.length(), find, findLen);
    }
    /** @brief find string */
    inline zfindex zfstringFind(ZF_IN const ZFCoreStringW &src, ZF_IN zfcharW find)
    {
        return zfstringFind(src.cString(), src.length(), &find, 1);
    }
    // ============================================================
    // zfstringFindReversely
    /** @brief find string */
    extern ZF_ENV_EXPORT zfindex zfstringFindReversely(ZF_IN const zfcharW *src, ZF_IN zfindex srcLen, ZF_IN const zfcharW *find, ZF_IN_OPT zfindex findLen = zfindexMax());
    /** @brief find string */
    inline zfindex zfstringFindReversely(ZF_IN const ZFCoreStringW &src, ZF_IN const ZFCoreStringW &find)
    {
        return zfstringFindReversely(src.cString(), src.length(), find.cString(), find.length());
    }
    /** @brief find string */
    inline zfindex zfstringFindReversely(ZF_IN const ZFCoreStringW &src, ZF_IN const zfcharW *find, ZF_IN_OPT zfindex findLen = zfindexMax())
    {
        return zfstringFindReversely(src.cString(), src.length(), find, findLen);
    }
    /** @brief find string */
    inline zfindex zfstringFindReversely(ZF_IN const ZFCoreStringW &src, ZF_IN zfcharW find)
    {
        return zfstringFindReversely(src.cString(), src.length(), &find, 1);
    }
    // ============================================================
    // zfstringFindCaseInsensitive
    /** @brief find string */
    extern ZF_ENV_EXPORT zfindex zfstringFindCaseInsensitive(ZF_IN const zfcharW *src, ZF_IN zfindex srcLen, ZF_IN const zfcharW *find, ZF_IN_OPT zfindex findLen = zfindexMax());
    /** @brief find string */
    inline zfindex zfstringFindCaseInsensitive(ZF_IN const ZFCoreStringW &src, ZF_IN const ZFCoreStringW &find)
    {
        return zfstringFindCaseInsensitive(src.cString(), src.length(), find.cString(), find.length());
    }
    /** @brief find string */
    inline zfindex zfstringFindCaseInsensitive(ZF_IN const ZFCoreStringW &src, ZF_IN const zfcharW *find, ZF_IN_OPT zfindex findLen = zfindexMax())
    {
        return zfstringFindCaseInsensitive(src.cString(), src.length(), find, findLen);
    }
    /** @brief find string */
    inline zfindex zfstringFindCaseInsensitive(ZF_IN const ZFCoreStringW &src, ZF_IN zfcharW find)
    {
        return zfstringFindCaseInsensitive(src.cString(), src.length(), &find, 1);
    }
    // ============================================================
    // zfstringFindCaseInsensitiveReversely
    /** @brief find string */
    extern ZF_ENV_EXPORT zfindex zfstringFindCaseInsensitiveReversely(ZF_IN const zfcharW *src, ZF_IN zfindex srcLen, ZF_IN const zfcharW *find, ZF_IN_OPT zfindex findLen = zfindexMax());
    /** @brief find string */
    inline zfindex zfstringFindCaseInsensitiveReversely(ZF_IN const ZFCoreStringW &src, ZF_IN const ZFCoreStringW &find)
    {
        return zfstringFindCaseInsensitiveReversely(src.cString(), src.length(), find.cString(), find.length());
    }
    /** @brief find string */
    inline zfindex zfstringFindCaseInsensitiveReversely(ZF_IN const ZFCoreStringW &src, ZF_IN const zfcharW *find, ZF_IN_OPT zfindex findLen = zfindexMax())
    {
        return zfstringFindCaseInsensitiveReversely(src.cString(), src.length(), find, findLen);
    }
    /** @brief find string */
    inline zfindex zfstringFindCaseInsensitiveReversely(ZF_IN const ZFCoreStringW &src, ZF_IN zfcharW find)
    {
        return zfstringFindCaseInsensitiveReversely(src.cString(), src.length(), &find, 1);
    }
    // ============================================================
    // zfstringFindFirstOf
    /** @brief find string */
    extern ZF_ENV_EXPORT zfindex zfstringFindFirstOf(ZF_IN const zfcharW *src, ZF_IN zfindex srcLen, ZF_IN const zfcharW *find, ZF_IN_OPT zfindex findLen = zfindexMax());
    /** @brief find string */
    inline zfindex zfstringFindFirstOf(ZF_IN const ZFCoreStringW &src, ZF_IN const ZFCoreStringW &find)
    {
        return zfstringFindFirstOf(src.cString(), src.length(), find.cString(), find.length());
    }
    /** @brief find string */
    inline zfindex zfstringFindFirstOf(ZF_IN const ZFCoreStringW &src, ZF_IN const zfcharW *find, ZF_IN_OPT zfindex findLen = zfindexMax())
    {
        return zfstringFindFirstOf(src.cString(), src.length(), find, findLen);
    }
    /** @brief find string */
    inline zfindex zfstringFindFirstOf(ZF_IN const ZFCoreStringW &src, ZF_IN zfcharW find)
    {
        return zfstringFindFirstOf(src.cString(), src.length(), &find, 1);
    }
    // ============================================================
    // zfstringFindFirstNotOf
    /** @brief find string */
    extern ZF_ENV_EXPORT zfindex zfstringFindFirstNotOf(ZF_IN const zfcharW *src, ZF_IN zfindex srcLen, ZF_IN const zfcharW *find, ZF_IN_OPT zfindex findLen = zfindexMax());
    /** @brief find string */
    inline zfindex zfstringFindFirstNotOf(ZF_IN const ZFCoreStringW &src, ZF_IN const ZFCoreStringW &find)
    {
        return zfstringFindFirstNotOf(src.cString(), src.length(), find.cString(), find.length());
    }
    /** @brief find string */
    inline zfindex zfstringFindFirstNotOf(ZF_IN const ZFCoreStringW &src, ZF_IN const zfcharW *find, ZF_IN_OPT zfindex findLen = zfindexMax())
    {
        return zfstringFindFirstNotOf(src.cString(), src.length(), find, findLen);
    }
    /** @brief find string */
    inline zfindex zfstringFindFirstNotOf(ZF_IN const ZFCoreStringW &src, ZF_IN zfcharW find)
    {
        return zfstringFindFirstNotOf(src.cString(), src.length(), &find, 1);
    }
    // ============================================================
    // zfstringFindLastOf
    /** @brief find string */
    extern ZF_ENV_EXPORT zfindex zfstringFindLastOf(ZF_IN const zfcharW *src, ZF_IN zfindex srcLen, ZF_IN const zfcharW *find, ZF_IN_OPT zfindex findLen = zfindexMax());
    /** @brief find string */
    inline zfindex zfstringFindLastOf(ZF_IN const ZFCoreStringW &src, ZF_IN const ZFCoreStringW &find)
    {
        return zfstringFindLastOf(src.cString(), src.length(), find.cString(), find.length());
    }
    /** @brief find string */
    inline zfindex zfstringFindLastOf(ZF_IN const ZFCoreStringW &src, ZF_IN const zfcharW *find, ZF_IN_OPT zfindex findLen = zfindexMax())
    {
        return zfstringFindLastOf(src.cString(), src.length(), find, findLen);
    }
    /** @brief find string */
    inline zfindex zfstringFindLastOf(ZF_IN const ZFCoreStringW &src, ZF_IN zfcharW find)
    {
        return zfstringFindLastOf(src.cString(), src.length(), &find, 1);
    }
    // ============================================================
    // zfstringFindLastNotOf
    /** @brief find string */
    extern ZF_ENV_EXPORT zfindex zfstringFindLastNotOf(ZF_IN const zfcharW *src, ZF_IN zfindex srcLen, ZF_IN const zfcharW *find, ZF_IN_OPT zfindex findLen = zfindexMax());
    /** @brief find string */
    inline zfindex zfstringFindLastNotOf(ZF_IN const ZFCoreStringW &src, ZF_IN const ZFCoreStringW &find)
    {
        return zfstringFindLastNotOf(src.cString(), src.length(), find.cString(), find.length());
    }
    /** @brief find string */
    inline zfindex zfstringFindLastNotOf(ZF_IN const ZFCoreStringW &src, ZF_IN const zfcharW *find, ZF_IN_OPT zfindex findLen = zfindexMax())
    {
        return zfstringFindLastNotOf(src.cString(), src.length(), find, findLen);
    }
    /** @brief find string */
    inline zfindex zfstringFindLastNotOf(ZF_IN const ZFCoreStringW &src, ZF_IN zfcharW find)
    {
        return zfstringFindLastNotOf(src.cString(), src.length(), &find, 1);
    }
#endif // zfcharW version

ZF_NAMESPACE_GLOBAL_END

#endif // #ifndef _ZFI_ZFCoreStringUtil_h_

