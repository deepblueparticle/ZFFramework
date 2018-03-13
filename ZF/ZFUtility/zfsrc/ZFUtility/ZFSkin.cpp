/* ====================================================================== *
 * Copyright (c) 2010-2018 ZFFramework
 * Github repo: https://github.com/ZFFramework/ZFFramework
 * Home page: http://ZFFramework.com
 * Blog: http://zsaber.com
 * Contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/LICENSE
 * ====================================================================== */
#include "ZFSkin.h"
#include "ZFCore/ZFSTLWrapper/zfstl_string.h"
#include "ZFCore/ZFSTLWrapper/zfstl_hashmap.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFOBSERVER_EVENT_GLOBAL_REGISTER(ZFGlobalEvent, SkinOnChange)

// ============================================================
typedef zfstlhashmap<zfstlstringZ, zfautoObject> _ZFP_ZFSkinMapType;
ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(ZFSkinDataHolder, ZFLevelZFFrameworkHigh)
{
}
public:
    _ZFP_ZFSkinMapType skinMap;
ZF_GLOBAL_INITIALIZER_END(ZFSkinDataHolder)
#define _ZFP_ZFSkinMapGlobal ZF_GLOBAL_INITIALIZER_INSTANCE(ZFSkinDataHolder)->skinMap

// ============================================================
ZFMETHOD_FUNC_DEFINE_2(zfautoObject, zfSkin,
                       ZFMP_IN(const zfchar *, key),
                       ZFMP_IN_OPT(ZFStyleable *, valueDefault, zfnull))
{
    zfCoreMutexLocker();
    _ZFP_ZFSkinMapType &m = _ZFP_ZFSkinMapGlobal;
    _ZFP_ZFSkinMapType::iterator it = m.find(key);
    if(it != m.end())
    {
        return it->second;
    }
    else
    {
        if(valueDefault != zfnull)
        {
            return valueDefault->toObject();
        }
        else
        {
            return zfnull;
        }
    }
}
ZFMETHOD_FUNC_DEFINE_0(void, zfSkinNotifyChanged)
{
    ZFGlobalEventCenter::instance()->observerNotify(ZFGlobalEvent::EventSkinOnChange());
}
ZFMETHOD_FUNC_DEFINE_2(void, zfSkinSet,
                       ZFMP_IN(const zfchar *, key),
                       ZFMP_IN(ZFStyleable *, value))
{
    if(key != zfnull)
    {
        zfCoreMutexLocker();
        if(value == zfnull)
        {
            _ZFP_ZFSkinMapGlobal.erase(key);
        }
        else
        {
            if(value->classData()->classIsTypeOf(ZFSerializable::ClassData()))
            {
                _ZFP_ZFSkinMapGlobal[key] = value->toObject();
            }
            else
            {
                zfCoreCriticalClassNotTypeOf(value->classData(), ZFSerializable::ClassData());
            }
        }
    }
}
ZFMETHOD_FUNC_DEFINE_2(void, zfSkinSetDefault,
                       ZFMP_IN(const zfchar *, key),
                       ZFMP_IN(ZFStyleable *, value))
{
    if(key && value)
    {
        if(!value->classData()->classIsTypeOf(ZFSerializable::ClassData()))
        {
            zfCoreCriticalClassNotTypeOf(value->classData(), ZFSerializable::ClassData());
            return ;
        }

        zfCoreMutexLocker();
        _ZFP_ZFSkinMapType &m = _ZFP_ZFSkinMapGlobal;
        _ZFP_ZFSkinMapType::iterator it = m.find(key);
        if(it == m.end())
        {
            m[key] = value->toObject();
        }
    }
}

ZFMETHOD_FUNC_DEFINE_0(void, zfSkinUnload)
{
    zfCoreMutexLocker();
    _ZFP_ZFSkinMapGlobal.clear();

    zfSkinNotifyChanged();
}

ZFMETHOD_FUNC_DEFINE_1(void, zfSkinDebug,
                       ZFMP_IN_OPT(const ZFOutputCallback &, output, ZFOutputCallbackDefault()))
{
    _ZFP_ZFSkinMapType &m = _ZFP_ZFSkinMapGlobal;
    for(_ZFP_ZFSkinMapType::iterator it = m.begin(); it != m.end(); ++it)
    {
        output << it->first.c_str() << zfText(" = ") << it->second.toObject()->objectInfoOfInstance() << zfText("\n");
    }
}

ZF_NAMESPACE_GLOBAL_END

