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
 * @file ZFClassUtil.h
 * @brief util for ZFClass
 */

#ifndef _ZFI_ZFClassUtil_h_
#define _ZFI_ZFClassUtil_h_

#include "ZFObjectCore.h"

ZF_NAMESPACE_GLOBAL_BEGIN

zfclassFwd ZFObject;
zfclassFwd ZFFilterForZFClass;
zfclassFwd ZFFilterForZFMethod;
zfclassFwd ZFFilterForZFProperty;

ZF_NAMESPACE_BEGIN(ZFClassUtil)

/**
 * @brief util to get all parent class
 */
extern ZF_ENV_EXPORT void allClassParentT(ZF_OUT ZFCoreArray<const ZFClass *> &ret,
                                          ZF_IN const ZFClass *cls,
                                          ZF_IN_OPT const ZFFilterForZFClass *filter = zfnull);
/** @brief see #allClassParentT */
inline ZFCoreArrayPOD<const ZFClass *> allClassParent(ZF_IN const ZFClass *cls,
                                                      ZF_IN_OPT const ZFFilterForZFClass *filter = zfnull)
{
    ZFCoreArrayPOD<const ZFClass *> ret;
    ZFClassUtil::allClassParentT(ret, cls, filter);
    return ret;
}

/**
 * @brief util to get all method in inherit tree
 */
extern ZF_ENV_EXPORT void allMethodT(ZF_OUT ZFCoreArray<const ZFMethod *> &ret,
                                     ZF_IN const ZFClass *cls,
                                     ZF_IN_OPT const ZFFilterForZFMethod *filter = zfnull);
/** @brief see #allMethod */
inline ZFCoreArrayPOD<const ZFMethod *> allMethod(ZF_IN const ZFClass *cls,
                                                  ZF_IN_OPT const ZFFilterForZFMethod *filter = zfnull)
{
    ZFCoreArrayPOD<const ZFMethod *> ret;
    ZFClassUtil::allMethodT(ret, cls, filter);
    return ret;
}

/**
 * @brief util to get all property in inherit tree
 */
extern ZF_ENV_EXPORT void allPropertyT(ZF_OUT ZFCoreArray<const ZFProperty *> &ret,
                                       ZF_IN const ZFClass *cls,
                                       ZF_IN_OPT const ZFFilterForZFProperty *filter = zfnull);
/** @brief see #allProperty */
inline ZFCoreArrayPOD<const ZFProperty *> allProperty(ZF_IN const ZFClass *cls,
                                                      ZF_IN_OPT const ZFFilterForZFProperty *filter = zfnull)
{
    ZFCoreArrayPOD<const ZFProperty *> ret;
    ZFClassUtil::allPropertyT(ret, cls, filter);
    return ret;
}

/**
 * @brief compare all properties of obj0 with obj1's property by reflect
 *
 * if both object is null, return true\n
 * two object have no need to be same class,
 * but must be ensured that all property are safe to be compared,
 * i.e. each property's type must match
 */
extern ZF_ENV_EXPORT zfbool allPropertyIsEqual(ZF_IN ZFObject *obj0,
                                               ZF_IN ZFObject *obj1,
                                               ZF_IN_OPT const ZFFilterForZFProperty *filter = zfnull);

/**
 * @brief use reflect to print all property if the property is not #ZFPropertyIsInitValue
 */
extern ZF_ENV_EXPORT void objectPropertyInfo(ZF_IN_OUT zfstring &ret,
                                             ZF_IN ZFObject *obj,
                                             ZF_IN_OPT zfindex maxCount = zfindexMax(),
                                             ZF_IN_OPT const ZFTokenForKeyValueContainer &token = ZFTokenForKeyValueContainerDefault());
/** @brief see #objectPropertyInfo */
inline zfstring objectPropertyInfo(ZF_IN ZFObject *obj,
                                   ZF_IN_OPT zfindex maxCount = zfindexMax(),
                                   ZF_IN_OPT const ZFTokenForKeyValueContainer &token = ZFTokenForKeyValueContainerDefault())
{
    zfstring ret;
    ZFClassUtil::objectPropertyInfo(ret, obj, maxCount, token);
    return ret;
}

/**
 * @brief get short info of object, see #objectPropertyInfo
 */
extern ZF_ENV_EXPORT void objectInfoT(ZF_IN_OUT zfstring &ret,
                                      ZF_IN ZFObject *obj);
/** @brief see #objectInfo */
inline zfstring objectInfo(ZF_IN ZFObject *obj)
{
    zfstring ret;
    ZFClassUtil::objectInfoT(ret, obj);
    return ret;
}

ZF_NAMESPACE_END(ZFClassUtil)
ZF_NAMESPACE_GLOBAL_END

#endif // #ifndef _ZFI_ZFClassUtil_h_

