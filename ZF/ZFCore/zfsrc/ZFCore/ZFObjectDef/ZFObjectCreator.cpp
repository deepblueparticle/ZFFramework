/* ====================================================================== *
 * Copyright (c) 2010-2018 ZFFramework
 * Github repo: https://github.com/ZFFramework/ZFFramework
 * Home page: http://ZFFramework.com
 * Blog: http://zsaber.com
 * Contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/LICENSE
 * ====================================================================== */
#include "ZFObjectCreator.h"
#include "ZFObjectImpl.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(ZFObjectCreatorDataHolder, ZFLevelZFFrameworkStatic)
{
}
public:
    ZFCoreMap creatorMap; // _ZFP_ZFObjectCreatorCallback *
ZF_GLOBAL_INITIALIZER_END(ZFObjectCreatorDataHolder)
#define _ZFP_ZFObjectCreatorMap (ZF_GLOBAL_INITIALIZER_INSTANCE(ZFObjectCreatorDataHolder)->creatorMap)

zfautoObject ZFObjectCreate(ZF_IN const zfchar *type,
                            ZF_IN const zfchar *data)
{
    _ZFP_ZFObjectCreatorCallback *creatorCallback = _ZFP_ZFObjectCreatorMap.get<_ZFP_ZFObjectCreatorCallback *>(type);
    if(creatorCallback == zfnull)
    {
        return zfnull;
    }
    return (*creatorCallback)(data);
}

void ZFObjectCreatorGetAllTypeT(ZF_OUT ZFCoreArray<const zfchar *> &ret)
{
    _ZFP_ZFObjectCreatorMap.allKeyT(ret);
}

void _ZFP_ZFObjectCreatorRegister(ZF_IN const zfchar *type,
                                  ZF_IN _ZFP_ZFObjectCreatorCallback creatorCallback)
{
    _ZFP_ZFObjectCreatorMap.set(type, ZFCorePointerForObject<_ZFP_ZFObjectCreatorCallback *>(zfnew(_ZFP_ZFObjectCreatorCallback, creatorCallback)));
}
void _ZFP_ZFObjectCreatorUnregister(ZF_IN const zfchar *type)
{
    _ZFP_ZFObjectCreatorMap.remove(type);
}

ZF_NAMESPACE_GLOBAL_END

#if _ZFP_ZFOBJECT_METHOD_REG
#include "../ZFObject.h"
ZF_NAMESPACE_GLOBAL_BEGIN

ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(zfautoObject, ZFObjectCreate, ZFMP_IN(const zfchar *, type), ZFMP_IN(const zfchar *, data))

ZF_NAMESPACE_GLOBAL_END
#endif

