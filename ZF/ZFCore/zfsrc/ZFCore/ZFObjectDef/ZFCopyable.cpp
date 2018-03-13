/* ====================================================================== *
 * Copyright (c) 2010-2018 ZFFramework
 * Github repo: https://github.com/ZFFramework/ZFFramework
 * Home page: http://ZFFramework.com
 * Blog: http://zsaber.com
 * Contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/LICENSE
 * ====================================================================== */
#include "ZFCopyable.h"
#include "ZFObjectImpl.h"
#include "ZFSerializable.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFOBJECT_REGISTER(ZFCopyable)

zfautoObject ZFCopyable::copy(void)
{
    zfautoObject ret = this->classData()->newInstance();
    if(ret != zfnull)
    {
        ZFCastZFObjectUnchecked(zfself *, ret.toObject())->copyableOnCopyFrom(this->toObject());
        if(ret.toObject()->classData()->classIsTypeOf(ZFSerializable::ClassData()))
        {
            ZFCastZFObjectUnchecked(ZFSerializable *, ret.toObject())->serializableCopyInfoFrom(ZFCastZFObjectUnchecked(ZFSerializable *, this));
        }
    }
    return ret;
}

void ZFCopyable::copyFrom(ZF_IN ZFObject *anotherObj)
{
    if(anotherObj != zfnull && anotherObj != this->toObject() && anotherObj->classData() == this->classData())
    {
        this->copyableOnCopyFrom(anotherObj);
        if(this->classData()->classIsTypeOf(ZFSerializable::ClassData()))
        {
            ZFCastZFObjectUnchecked(ZFSerializable *, this)->serializableCopyInfoFrom(ZFCastZFObjectUnchecked(ZFSerializable *, anotherObj));
        }
    }
}

ZF_NAMESPACE_GLOBAL_END

#if _ZFP_ZFOBJECT_METHOD_REG
#include "../ZFObject.h"
ZF_NAMESPACE_GLOBAL_BEGIN

ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_0(ZFCopyable, zfautoObject, copy)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_1(ZFCopyable, void, copyFrom, ZFMP_IN(ZFObject *, anotherObj))

ZF_NAMESPACE_GLOBAL_END
#endif

