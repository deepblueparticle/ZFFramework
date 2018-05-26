/* ====================================================================== *
 * Copyright (c) 2010-2018 ZFFramework
 * Github repo: https://github.com/ZFFramework/ZFFramework
 * Home page: http://ZFFramework.com
 * Blog: http://zsaber.com
 * Contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/LICENSE
 * ====================================================================== */
#include "ZFDynamicRegisterUtil.h"

#include "ZFSTLWrapper/zfstl_map.h"

ZF_NAMESPACE_GLOBAL_BEGIN
/* ZFMETHOD_MAX_PARAM */

// ============================================================
ZFOBJECT_REGISTER(ZFDynamicMethodData)

ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_VAR(ZFDynamicMethodData, const ZFMethod *, invokerMethod)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_VAR(ZFDynamicMethodData, ZFObject *, invokerObject)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_VAR(ZFDynamicMethodData, zfstring, errorHint)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_VAR(ZFDynamicMethodData, zfautoObject, ret)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_VAR(ZFDynamicMethodData, ZFObject *, param0)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_VAR(ZFDynamicMethodData, ZFObject *, param1)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_VAR(ZFDynamicMethodData, ZFObject *, param2)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_VAR(ZFDynamicMethodData, ZFObject *, param3)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_VAR(ZFDynamicMethodData, ZFObject *, param4)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_VAR(ZFDynamicMethodData, ZFObject *, param5)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_VAR(ZFDynamicMethodData, ZFObject *, param6)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_VAR(ZFDynamicMethodData, ZFObject *, param7)

// ============================================================
ZFOBJECT_REGISTER(ZFDynamicPropertyData)

ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_VAR(ZFDynamicPropertyData, zfautoObject, ret)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_VAR(ZFDynamicPropertyData, const ZFProperty *, property)

// ============================================================
ZFOBSERVER_EVENT_GLOBAL_REGISTER(ZFGlobalEvent, ZFDynamicRemoveAll)

// ============================================================
zfclassNotPOD _ZFP_ZFDynamicPrivate
{
public:
    zfuint refCount;
    zfbool errorOccurred;
    const ZFClass *cls;
    zfstring methodNamespace;
    ZFCoreArrayPOD<const ZFClass *> allClass;
    ZFCoreArrayPOD<const ZFMethod *> allMethod;
    ZFCoreArrayPOD<const ZFProperty *> allProperty;
    ZFCoreArrayPOD<zfidentity> allEvent;
    ZFCoreArray<ZFOutput> errorCallbackList;
public:
    _ZFP_ZFDynamicPrivate(void)
    : refCount(1)
    , errorOccurred(zffalse)
    , cls(zfnull)
    , methodNamespace()
    , allClass()
    , allMethod()
    , allProperty()
    , allEvent()
    {
    }
public:
    void error(ZF_IN const zfchar *errorHint, ...)
    {
        this->errorOccurred = zftrue;
        if(!this->errorCallbackList.isEmpty())
        {
            zfstring s;
            va_list vaList;
            va_start(vaList, errorHint);
            zfstringAppendV(s, errorHint, vaList);
            va_end(vaList);
            s += zfText("\n");

            for(zfindex i = 0; i < this->errorCallbackList.count(); ++i)
            {
                this->errorCallbackList[i].execute(s.cString());
            }
        }
    }
public:
    zfbool scopeBeginCheck(void)
    {
        if(this->cls != zfnull)
        {
            this->error(zfText("[ZFDynamic] have you forgot classEnd?"));
            return zffalse;
        }
        else if(!this->methodNamespace.isEmpty())
        {
            this->error(zfText("[ZFDynamic] have you forgot NSEnd?"));
            return zffalse;
        }
        else
        {
            return zftrue;
        }
    }
};

// ============================================================
/** @cond ZFPrivateDoc */
ZFDynamic::ZFDynamic(void)
: d(zfnew(_ZFP_ZFDynamicPrivate))
{
}
ZFDynamic::ZFDynamic(ZF_IN const ZFDynamic &ref)
: d(ref.d)
{
    ++(d->refCount);
}
ZFDynamic &ZFDynamic::operator = (ZF_IN const ZFDynamic &ref)
{
    ++(ref.d->refCount);
    --(d->refCount);
    if(d->refCount == 0)
    {
        zfdelete(d);
    }
    d = ref.d;
    return *this;
}
zfbool ZFDynamic::operator == (ZF_IN const ZFDynamic &ref) const
{
    return (d == ref.d);
}
/** @endcond */

void ZFDynamic::removeAll(void)
{
    ZFCoreArrayPOD<const ZFClass *> allClass = d->allClass;
    d->allClass = ZFCoreArrayPOD<const ZFClass *>();
    ZFCoreArrayPOD<const ZFMethod *> allMethod = d->allMethod;
    d->allMethod = ZFCoreArrayPOD<const ZFMethod *>();
    ZFCoreArrayPOD<const ZFProperty *> allProperty = d->allProperty;
    d->allProperty = ZFCoreArrayPOD<const ZFProperty *>();
    ZFCoreArrayPOD<zfidentity> allEvent = d->allEvent;
    d->allEvent = ZFCoreArrayPOD<zfidentity>();

    for(zfindex i = 0; i < allEvent.count(); ++i)
    {
        ZFIdMapUnregister(allEvent[i]);
    }
    for(zfindex i = 0; i < allMethod.count(); ++i)
    {
        ZFMethodDynamicUnregister(allMethod[i]);
    }
    for(zfindex i = 0; i < allProperty.count(); ++i)
    {
        ZFPropertyDynamicUnregister(allProperty[i]);
    }
    for(zfindex i = 0; i < allClass.count(); ++i)
    {
        ZFClassDynamicUnregister(allClass[i]);
    }
}

ZFDynamic &ZFDynamic::removeAllOnEvent(ZF_IN zfidentity eventId /* = ZFGlobalEvent::EventZFDynamicRemoveAll() */)
{
    ZFLISTENER_LOCAL(action, {
        userData->to<v_ZFDynamic *>()->zfv.removeAll();
    })
    ZFGlobalEventCenter::instance()->observerAdd(
        eventId, action, zflineAlloc(v_ZFDynamic, *this));
    return *this;
}

const ZFCoreArrayPOD<const ZFClass *> &ZFDynamic::allClass(void) const
{
    return d->allClass;
}
const ZFCoreArrayPOD<const ZFMethod *> &ZFDynamic::allMethod(void) const
{
    return d->allMethod;
}
const ZFCoreArrayPOD<const ZFProperty *> &ZFDynamic::allProperty(void) const
{
    return d->allProperty;
}
const ZFCoreArrayPOD<zfidentity> &ZFDynamic::allEvent(void) const
{
    return d->allEvent;
}

ZFDynamic &ZFDynamic::classBegin(ZF_IN const zfchar *className,
                                 ZF_IN_OPT const ZFClass *parentClass /* = ZFObject::ClassData() */,
                                 ZF_IN_OPT ZFObject *classDynamicRegisterUserData /* = zfnull */)
{
    if(d->errorOccurred) {return *this;}
    if(!d->scopeBeginCheck()) {return *this;}
    d->cls = ZFClass::classForName(className);
    if(d->cls == zfnull)
    {
        if(parentClass == zfnull)
        {
            d->error(zfText("[ZFDynamic] no such class: %s"), className);
        }
        else
        {
            zfstring errorHint;
            const ZFClass *dynClass = ZFClassDynamicRegister(
                className, parentClass, classDynamicRegisterUserData, &errorHint);
            if(dynClass == zfnull)
            {
                d->error(zfText("[ZFDynamic] unable to register class: %s, reason: %s"),
                    className,
                    errorHint.cString());
            }
            else
            {
                d->allClass.add(dynClass);
                d->cls = dynClass;
            }
        }
    }
    return *this;
}
ZFDynamic &ZFDynamic::classBegin(ZF_IN const zfchar *className,
                                 ZF_IN const zfchar *parentClassName,
                                 ZF_IN_OPT ZFObject *classDynamicRegisterUserData /* = zfnull */)
{
    if(d->errorOccurred) {return *this;}
    if(!d->scopeBeginCheck()) {return *this;}
    if(zfsIsEmpty(parentClassName))
    {
        return this->classBegin(className, ZFObject::ClassData(), classDynamicRegisterUserData);
    }
    else
    {
        const ZFClass *parentClass = ZFClass::classForName(parentClassName);
        if(parentClass == zfnull)
        {
            d->error(zfText("[ZFDynamic] no such parentClass: %s"), parentClassName);
            return *this;
        }
        else
        {
            return this->classBegin(className, parentClass, classDynamicRegisterUserData);
        }
    }
}
ZFDynamic &ZFDynamic::classBegin(ZF_IN const ZFClass *cls)
{
    if(d->errorOccurred) {return *this;}
    if(!d->scopeBeginCheck()) {return *this;}
    d->cls = cls;
    if(d->cls == zfnull)
    {
        d->error(zfText("[ZFDynamic] null class"));
    }
    return *this;
}
ZFDynamic &ZFDynamic::classEnd(void)
{
    if(d->errorOccurred) {return *this;}
    if(d->cls == zfnull)
    {
        d->error(zfText("[ZFDynamic] no paired classBegin"));
    }
    d->cls = zfnull;
    return *this;
}

zfclass _ZFP_I_ZFDynamicOnInitData : zfextends ZFObject
{
    ZFOBJECT_DECLARE(_ZFP_I_ZFDynamicOnInitData, ZFObject)
public:
    ZFListener callback;
    zfautoObject userData;
};
ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(ZFDynamicOnInit, ZFLevelZFFrameworkEssential)
{
    this->onInitListener = ZFCallbackForFunc(zfself::onInit);
    this->onDeallocAttachListener = ZFCallbackForFunc(zfself::onDeallocAttach);
    this->onDeallocListener = ZFCallbackForFunc(zfself::onDealloc);
}
ZF_GLOBAL_INITIALIZER_DESTROY(ZFDynamicOnInit)
{
    if(this->classOnChangeListener.callbackIsValid())
    {
        ZFClassDataChangeObserver.observerRemove(
            ZFGlobalEvent::EventClassDataChange(),
            this->classOnChangeListener);
    }
}
zfstlmap<const ZFClass *, zfbool> onInitMap;
zfstlmap<const ZFClass *, zfbool> onDeallocMap;
ZFListener classOnChangeListener;
ZFListener onInitListener;
ZFListener onDeallocAttachListener;
ZFListener onDeallocListener;
void checkAttach(void)
{
    if(!this->classOnChangeListener.callbackIsValid())
    {
        this->classOnChangeListener = ZFCallbackForFunc(zfself::classOnChange);
        ZFClassDataChangeObserver.observerAdd(
            ZFGlobalEvent::EventClassDataChange(),
            this->classOnChangeListener);
    }
}
static ZFLISTENER_PROTOTYPE_EXPAND(classOnChange)
{
    const ZFClassDataChangeData *data = listenerData.param0->to<ZFPointerHolder *>()->holdedDataPointer<const ZFClassDataChangeData *>();
    if(data->changeType == ZFClassDataChangeTypeDetach && data->changedClass != zfnull)
    {
        ZF_GLOBAL_INITIALIZER_CLASS(ZFDynamicOnInit) *d = ZF_GLOBAL_INITIALIZER_INSTANCE(ZFDynamicOnInit);
        d->onInitMap.erase(data->changedClass);
        d->onDeallocMap.erase(data->changedClass);
    }
}
static ZFLISTENER_PROTOTYPE_EXPAND(onInit)
{
    _ZFP_I_ZFDynamicOnInitData *data = userData->to<_ZFP_I_ZFDynamicOnInitData *>();
    if(data->callback.callbackIsValid())
    {
        data->callback.execute(listenerData, data->userData);
    }
}
static ZFLISTENER_PROTOTYPE_EXPAND(onDeallocAttach)
{
    listenerData.sender->observerAdd(ZFObserverAddParam()
        .eventIdSet(ZFObject::EventObjectBeforeDealloc())
        .observerSet(ZF_GLOBAL_INITIALIZER_INSTANCE(ZFDynamicOnInit)->onDeallocListener)
        .userDataSet(userData)
        .observerLevelSet(ZFLevelZFFrameworkPostHigh)
        );
}
static ZFLISTENER_PROTOTYPE_EXPAND(onDealloc)
{
    _ZFP_I_ZFDynamicOnInitData *data = userData->to<_ZFP_I_ZFDynamicOnInitData *>();
    if(data->callback.callbackIsValid())
    {
        data->callback.execute(listenerData, data->userData);
    }
}
ZF_GLOBAL_INITIALIZER_END(ZFDynamicOnInit)

ZFDynamic &ZFDynamic::onInit(ZF_IN const ZFListener &onInitCallback,
                             ZF_IN_OPT ZFObject *userData /* = zfnull */)
{
    if(d->errorOccurred) {return *this;}
    if(d->cls == zfnull)
    {
        d->error(zfText("[ZFDynamic] have you forgot classBegin?"));
        return *this;
    }
    if(!d->cls->classIsDynamicRegister())
    {
        d->error(zfText("[ZFDynamic] only dynamic registered class can attach custom onInit"));
        return *this;
    }
    if(!onInitCallback.callbackIsValid())
    {
        d->error(zfText("[ZFDynamic] invalid callback"));
        return *this;
    }
    zfCoreMutexLocker();
    ZF_GLOBAL_INITIALIZER_CLASS(ZFDynamicOnInit) *g = ZF_GLOBAL_INITIALIZER_INSTANCE(ZFDynamicOnInit);
    if(g->onInitMap.find(d->cls) != g->onInitMap.end())
    {
        d->error(zfText("[ZFDynamic] class %s already register a custom onInit"),
            d->cls->className());
        return *this;
    }
    g->onInitMap[d->cls] = zftrue;
    zfblockedAlloc(_ZFP_I_ZFDynamicOnInitData, data);
    data->callback = onInitCallback;
    data->userData = userData;
    d->cls->instanceObserverAdd(g->onInitListener, data, zfnull, ZFLevelZFFrameworkHigh);
    g->checkAttach();
    return *this;
}
ZFDynamic &ZFDynamic::onDealloc(ZF_IN const ZFListener &onDeallocCallback,
                                ZF_IN_OPT ZFObject *userData /* = zfnull */)
{
    if(d->errorOccurred) {return *this;}
    if(d->cls == zfnull)
    {
        d->error(zfText("[ZFDynamic] have you forgot classBegin?"));
        return *this;
    }
    if(!d->cls->classIsDynamicRegister())
    {
        d->error(zfText("[ZFDynamic] only dynamic registered class can attach custom onDealloc"));
        return *this;
    }
    if(!onDeallocCallback.callbackIsValid())
    {
        d->error(zfText("[ZFDynamic] invalid callback"));
        return *this;
    }
    zfCoreMutexLocker();
    ZF_GLOBAL_INITIALIZER_CLASS(ZFDynamicOnInit) *g = ZF_GLOBAL_INITIALIZER_INSTANCE(ZFDynamicOnInit);
    if(g->onDeallocMap.find(d->cls) != g->onDeallocMap.end())
    {
        d->error(zfText("[ZFDynamic] class %s already register a custom onDealloc"),
            d->cls->className());
        return *this;
    }
    g->onDeallocMap[d->cls] = zftrue;
    zfblockedAlloc(_ZFP_I_ZFDynamicOnInitData, data);
    data->callback = onDeallocCallback;
    data->userData = userData;
    d->cls->instanceObserverAdd(g->onDeallocAttachListener, data, zfnull, ZFLevelZFFrameworkHigh);
    g->checkAttach();
    return *this;
}

ZFDynamic &ZFDynamic::NSBegin(ZF_IN_OPT const zfchar *methodNamespace /* = ZFMethodFuncNamespaceGlobal */)
{
    if(d->errorOccurred) {return *this;}
    if(!d->scopeBeginCheck()) {return *this;}
    if(zfsIsEmpty(methodNamespace))
    {
        d->methodNamespace = ZFMethodFuncNamespaceGlobal;
    }
    else
    {
        d->methodNamespace = methodNamespace;
    }
    return *this;
}
ZFDynamic &ZFDynamic::NSEnd(void)
{
    if(d->errorOccurred) {return *this;}
    if(d->methodNamespace.isEmpty())
    {
        d->error(zfText("[ZFDynamic] no paired NSBegin"));
    }
    d->methodNamespace.removeAll();
    return *this;
}

static zfbool _ZFP_ZFDynamicEventGI(ZFMETHOD_GENERIC_INVOKER_PARAMS)
{
    ret = invokerMethod->methodDynamicRegisterUserData();
    return zftrue;
}
ZFDynamic &ZFDynamic::event(ZF_IN const zfchar *eventName)
{
    if(d->errorOccurred) {return *this;}
    if(zfsIsEmpty(eventName))
    {
        d->error(zfText("empty event name"));
        return *this;
    }
    zfstring idName;
    if(d->cls != zfnull)
    {
        idName += d->cls->className();
    }
    else
    {
        if(d->methodNamespace.isEmpty())
        {
            idName += ZFMethodFuncNamespaceGlobal;
        }
        else
        {
            idName += d->methodNamespace;
        }
    }
    idName += zfText("::Event");
    idName += eventName;
    zfidentity idValue = ZFIdMapGetId(idName);
    if(idValue != zfidentityInvalid())
    {
        d->error(zfText("%s already exists"), idName.cString());
        return *this;
    }
    idValue = ZFIdMapRegister(idName);
    d->allEvent.add(idValue);

    zfblockedAlloc(v_zfidentity, t);
    t->zfv = idValue;
    const ZFMethod *method = ZFMethodDynamicRegister(ZFMethodDynamicRegisterParam()
            .methodGenericInvokerSet(_ZFP_ZFDynamicEventGI)
            .methodDynamicRegisterUserDataSet(t)
            .methodOwnerClassSet(d->cls)
            .methodNamespaceSet(d->methodNamespace)
            .methodNameSet(zfstringWithFormat(zfText("Event%s"), eventName))
            .methodReturnTypeIdSet(ZFTypeId_zfidentity())
        );
    zfCoreAssert(method != zfnull);
    d->allMethod.add(method);

    return *this;
}

zfclass _ZFP_I_ZFDynamicMethodTask : zfextends ZFObject
{
    ZFOBJECT_DECLARE(_ZFP_I_ZFDynamicMethodTask, ZFObject)
public:
    ZFListener methodCallback;
    zfautoObject methodCallbackUserData;
};
static zfbool _ZFP_ZFDynamicMethodGI(ZFMETHOD_GENERIC_INVOKER_PARAMS)
{
    zfblockedAlloc(ZFDynamicMethodData, d);
    d->invokerMethod = invokerMethod;
    d->invokerObject = invokerObject;
    d->param0 = param0;
    d->param1 = param1;
    d->param2 = param2;
    d->param3 = param3;
    d->param4 = param4;
    d->param5 = param5;
    d->param6 = param6;
    d->param7 = param7;

    _ZFP_I_ZFDynamicMethodTask *task = ZFCastZFObjectUnchecked(_ZFP_I_ZFDynamicMethodTask *, invokerMethod->methodDynamicRegisterUserData());
    task->methodCallback.execute(ZFListenerData().param0Set(d), task->methodCallbackUserData);
    ret = d->ret;
    if(errorHint != zfnull)
    {
        *errorHint += d->errorHint;
    }
    return d->invokeSuccess;
}
ZFDynamic &ZFDynamic::method(ZF_IN const ZFListener &methodCallback
                             , ZF_IN ZFObject *methodCallbackUserData
                             , ZF_IN const zfchar *methodReturnTypeId
                             , ZF_IN const zfchar *methodName
                             , ZF_IN_OPT const zfchar *methodParamTypeId0 /* = zfnull */
                             , ZF_IN_OPT const zfchar *methodParamTypeId1 /* = zfnull */
                             , ZF_IN_OPT const zfchar *methodParamTypeId2 /* = zfnull */
                             , ZF_IN_OPT const zfchar *methodParamTypeId3 /* = zfnull */
                             , ZF_IN_OPT const zfchar *methodParamTypeId4 /* = zfnull */
                             , ZF_IN_OPT const zfchar *methodParamTypeId5 /* = zfnull */
                             , ZF_IN_OPT const zfchar *methodParamTypeId6 /* = zfnull */
                             , ZF_IN_OPT const zfchar *methodParamTypeId7 /* = zfnull */
                             )
{
    if(d->errorOccurred) {return *this;}
    if(!methodCallback.callbackIsValid())
    {
        d->error(zfText("invalid methodCallback"));
        return *this;
    }

    zfblockedAlloc(_ZFP_I_ZFDynamicMethodTask, task);
    task->methodCallback = methodCallback;
    task->methodCallbackUserData = methodCallbackUserData;
    return this->method(_ZFP_ZFDynamicMethodGI, task, methodReturnTypeId, methodName
            , methodParamTypeId0
            , methodParamTypeId1
            , methodParamTypeId2
            , methodParamTypeId3
            , methodParamTypeId4
            , methodParamTypeId5
            , methodParamTypeId6
            , methodParamTypeId7
        );
}
ZFDynamic &ZFDynamic::method(ZF_IN ZFMethodGenericInvoker methodGenericInvoker
                             , ZF_IN ZFObject *methodDynamicRegisterUserData
                             , ZF_IN const zfchar *methodReturnTypeId
                             , ZF_IN const zfchar *methodName
                             , ZF_IN_OPT const zfchar *methodParamTypeId0 /* = zfnull */
                             , ZF_IN_OPT const zfchar *methodParamTypeId1 /* = zfnull */
                             , ZF_IN_OPT const zfchar *methodParamTypeId2 /* = zfnull */
                             , ZF_IN_OPT const zfchar *methodParamTypeId3 /* = zfnull */
                             , ZF_IN_OPT const zfchar *methodParamTypeId4 /* = zfnull */
                             , ZF_IN_OPT const zfchar *methodParamTypeId5 /* = zfnull */
                             , ZF_IN_OPT const zfchar *methodParamTypeId6 /* = zfnull */
                             , ZF_IN_OPT const zfchar *methodParamTypeId7 /* = zfnull */
                             )
{
    if(d->errorOccurred) {return *this;}
    return this->method(ZFMethodDynamicRegisterParam()
            .methodDynamicRegisterUserDataSet(methodDynamicRegisterUserData)
            .methodOwnerClassSet(d->cls)
            .methodNamespaceSet(d->methodNamespace)
            .methodGenericInvokerSet(methodGenericInvoker)
            .methodNameSet(methodName)
            .methodReturnTypeIdSet(methodReturnTypeId)
            .methodParamAdd(methodParamTypeId0)
            .methodParamAdd(methodParamTypeId1)
            .methodParamAdd(methodParamTypeId2)
            .methodParamAdd(methodParamTypeId3)
            .methodParamAdd(methodParamTypeId4)
            .methodParamAdd(methodParamTypeId5)
            .methodParamAdd(methodParamTypeId6)
            .methodParamAdd(methodParamTypeId7)
        );
}
ZFDynamic &ZFDynamic::method(ZF_IN const ZFMethodDynamicRegisterParam &param)
{
    if(d->errorOccurred) {return *this;}
    zfstring errorHint;
    const ZFMethod *dynMethod = ZFMethodDynamicRegister(param, &errorHint);
    if(dynMethod == zfnull)
    {
        d->error(zfText("[ZFDynamic] unable to register method, reason: %s"), errorHint.cString());
    }
    else
    {
        d->allMethod.add(dynMethod);
    }
    return *this;
}

zfclass _ZFP_I_ZFDynamicPropertyTask : zfextends ZFObject
{
    ZFOBJECT_DECLARE(_ZFP_I_ZFDynamicPropertyTask, ZFObject)
public:
    ZFListener initValueCallback;
    ZFObject *initValueCallbackUserData;
};
static zfautoObject _ZFP_ZFDynamicPropertyInit(ZF_IN const ZFProperty *property)
{
    _ZFP_I_ZFDynamicPropertyTask *task = ZFCastZFObjectUnchecked(_ZFP_I_ZFDynamicPropertyTask *, property->propertyDynamicRegisterUserData());
    zfblockedAlloc(ZFDynamicPropertyData, d);
    d->property = property;
    task->initValueCallback.execute(ZFListenerData().param0Set(d), task->initValueCallbackUserData);
    return d->ret;
}
static void _ZFP_ZFDynamicPropertyInitSetup(ZF_IN_OUT ZFPropertyDynamicRegisterParam &param,
                                            ZF_IN const ZFListener &initValueCallback,
                                            ZF_IN ZFObject *initValueCallbackUserData)
{
    if(initValueCallback.callbackIsValid())
    {
        zfblockedAlloc(_ZFP_I_ZFDynamicPropertyTask, task);
        task->initValueCallback = initValueCallback;
        task->initValueCallbackUserData = initValueCallbackUserData;
        param.propertyInitValueCallbackSet(_ZFP_ZFDynamicPropertyInit);
        param.propertyDynamicRegisterUserDataSet(task);
    }
}
ZFDynamic &ZFDynamic::property(ZF_IN const zfchar *propertyTypeId,
                               ZF_IN const zfchar *propertyName,
                               ZF_IN_OPT const ZFListener &initValueCallback /* = ZFCallbackNull() */,
                               ZF_IN_OPT ZFObject *initValueCallbackUserData /* = zfnull */)
{
    if(d->errorOccurred) {return *this;}
    ZFPropertyDynamicRegisterParam param;
    param.propertyOwnerClassSet(d->cls);
    param.propertyTypeIdSet(propertyTypeId);
    param.propertyNameSet(propertyName);
    _ZFP_ZFDynamicPropertyInitSetup(param, initValueCallback, initValueCallbackUserData);
    return this->property(param);
}
ZFDynamic &ZFDynamic::property(ZF_IN const ZFClass *propertyClassOfRetainProperty,
                               ZF_IN const zfchar *propertyName,
                               ZF_IN_OPT const ZFListener &initValueCallback /* = ZFCallbackNull() */,
                               ZF_IN_OPT ZFObject *initValueCallbackUserData /* = zfnull */)
{
    if(d->errorOccurred) {return *this;}
    if(propertyClassOfRetainProperty == zfnull)
    {
        d->error(zfText("[ZFDynamic] propertyClassOfRetainProperty not set"));
        return *this;
    }
    ZFPropertyDynamicRegisterParam param;
    param.propertyOwnerClassSet(d->cls);
    param.propertyTypeIdSet(ZFTypeId_ZFObject());
    param.propertyNameSet(propertyName);
    param.propertyClassOfRetainPropertySet(propertyClassOfRetainProperty);
    _ZFP_ZFDynamicPropertyInitSetup(param, initValueCallback, initValueCallbackUserData);
    return this->property(param);
}
ZFDynamic &ZFDynamic::property(ZF_IN const ZFPropertyDynamicRegisterParam &param)
{
    if(d->errorOccurred) {return *this;}
    if(d->cls == zfnull)
    {
        d->error(zfText("[ZFDynamic] have you forgot classBegin?"));
        return *this;
    }
    zfstring errorHint;
    const ZFProperty *dynProperty = ZFPropertyDynamicRegister(param, &errorHint);
    if(dynProperty == zfnull)
    {
        d->error(zfText("[ZFDynamic] unable to register property, reason: %s"), errorHint.cString());
    }
    else
    {
        d->allProperty.add(dynProperty);
    }
    return *this;
}

ZFDynamic &ZFDynamic::errorCallbackAdd(ZF_IN const ZFOutput &errorCallback /* = ZFOutputDefault() */)
{
    if(errorCallback.callbackIsValid())
    {
        d->errorCallbackList.add(errorCallback);
    }
    return *this;
}
ZFDynamic &ZFDynamic::errorCallbackRemove(ZF_IN const ZFOutput &errorCallback)
{
    d->errorCallbackList.removeElement(errorCallback);
    return *this;
}
zfindex ZFDynamic::errorCallbackCount(void) const
{
    return d->errorCallbackList.count();
}
const ZFOutput &ZFDynamic::errorCallbackAtIndex(ZF_IN zfindex index) const
{
    return d->errorCallbackList[index];
}
void ZFDynamic::errorCallbackNotify(ZF_IN const zfchar *errorHint) const
{
    d->error(zfText("%s"), errorHint);
}

// ============================================================
ZFTYPEID_ACCESS_ONLY_DEFINE(ZFDynamic, ZFDynamic)

// ============================================================
ZFMETHOD_FUNC_DEFINE_0(void, ZFDynamicRemoveAll)
{
    ZFGlobalEventCenter::instance()->observerNotify(ZFGlobalEvent::EventZFDynamicRemoveAll());
}

// ============================================================
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFDynamic, void, removeAll)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFDynamic, ZFDynamic &, removeAllOnEvent, ZFMP_IN_OPT(zfidentity, eventId, ZFGlobalEvent::EventZFDynamicRemoveAll()))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFDynamic, const ZFCoreArrayPOD<const ZFClass *> &, allClass)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFDynamic, const ZFCoreArrayPOD<const ZFMethod *> &, allMethod)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFDynamic, const ZFCoreArrayPOD<const ZFProperty *> &, allProperty)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFDynamic, const ZFCoreArrayPOD<zfidentity> &, allEvent)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_3(v_ZFDynamic, ZFDynamic &, classBegin, ZFMP_IN(const zfchar *, className), ZFMP_IN_OPT(const ZFClass *, parentClass, ZFObject::ClassData()), ZFMP_IN_OPT(ZFObject *, classDynamicRegisterUserData, zfnull))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_3(v_ZFDynamic, ZFDynamic &, classBegin, ZFMP_IN(const zfchar *, className), ZFMP_IN(const zfchar *, parentClassName), ZFMP_IN_OPT(ZFObject *, classDynamicRegisterUserData, zfnull))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFDynamic, ZFDynamic &, classBegin, ZFMP_IN(const ZFClass *, cls))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFDynamic, ZFDynamic &, classEnd)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_2(v_ZFDynamic, ZFDynamic &, onInit, ZFMP_IN(const ZFListener &, onInitCallback), ZFMP_IN_OPT(ZFObject *, userData, zfnull))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_2(v_ZFDynamic, ZFDynamic &, onDealloc, ZFMP_IN(const ZFListener &, onDeallocCallback), ZFMP_IN_OPT(ZFObject *, userData, zfnull))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFDynamic, ZFDynamic &, NSBegin, ZFMP_IN_OPT(const zfchar *, methodNamespace, ZFMethodFuncNamespaceGlobal))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFDynamic, ZFDynamic &, NSEnd)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFDynamic, ZFDynamic &, event, ZFMP_IN(const zfchar *, eventName))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_8(v_ZFDynamic, ZFDynamic &, method
    , ZFMP_IN(ZFMethodGenericInvoker, methodGenericInvoker)
    , ZFMP_IN(ZFObject *, methodDynamicRegisterUserData)
    , ZFMP_IN(const zfchar *, methodReturnTypeId)
    , ZFMP_IN(const zfchar *, methodName)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId0, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId1, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId2, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId3, zfnull)
    /* ZFMETHOD_MAX_PARAM , ZFMP_IN_OPT(const zfchar *, methodParamTypeId4, zfnull) */
    /* ZFMETHOD_MAX_PARAM , ZFMP_IN_OPT(const zfchar *, methodParamTypeId5, zfnull) */
    /* ZFMETHOD_MAX_PARAM , ZFMP_IN_OPT(const zfchar *, methodParamTypeId6, zfnull) */
    /* ZFMETHOD_MAX_PARAM , ZFMP_IN_OPT(const zfchar *, methodParamTypeId7, zfnull) */
    )
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_8(v_ZFDynamic, ZFDynamic &, method
    , ZFMP_IN(const ZFListener &, methodCallback)
    , ZFMP_IN(ZFObject *, methodCallbackUserData)
    , ZFMP_IN(const zfchar *, methodReturnTypeId)
    , ZFMP_IN(const zfchar *, methodName)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId0, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId1, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId2, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId3, zfnull)
    /* ZFMETHOD_MAX_PARAM , ZFMP_IN_OPT(const zfchar *, methodParamTypeId4, zfnull) */
    /* ZFMETHOD_MAX_PARAM , ZFMP_IN_OPT(const zfchar *, methodParamTypeId5, zfnull) */
    /* ZFMETHOD_MAX_PARAM , ZFMP_IN_OPT(const zfchar *, methodParamTypeId6, zfnull) */
    /* ZFMETHOD_MAX_PARAM , ZFMP_IN_OPT(const zfchar *, methodParamTypeId7, zfnull) */
    )
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFDynamic, ZFDynamic &, method, ZFMP_IN(const ZFMethodDynamicRegisterParam &, param))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_4(v_ZFDynamic, ZFDynamic &, property, ZFMP_IN(const zfchar *, propertyTypeId), ZFMP_IN(const zfchar *, propertyName), ZFMP_IN_OPT(const ZFListener &, initValueCallback, ZFCallbackNull()), ZFMP_IN_OPT(ZFObject *, initValueCallbackUserData, zfnull))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_4(v_ZFDynamic, ZFDynamic &, property, ZFMP_IN(const ZFClass *, propertyClassOfRetainProperty), ZFMP_IN(const zfchar *, propertyName), ZFMP_IN_OPT(const ZFListener &, initValueCallback, ZFCallbackNull()), ZFMP_IN_OPT(ZFObject *, initValueCallbackUserData, zfnull))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFDynamic, ZFDynamic &, property, ZFMP_IN(const ZFPropertyDynamicRegisterParam &, param))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFDynamic, ZFDynamic &, errorCallbackAdd, ZFMP_IN_OPT(const ZFOutput &, errorCallback, ZFOutputDefault()))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFDynamic, ZFDynamic &, errorCallbackRemove, ZFMP_IN(const ZFOutput &, errorCallback))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFDynamic, zfindex, errorCallbackCount)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFDynamic, const ZFOutput &, errorCallbackAtIndex, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFDynamic, void, errorCallbackNotify, ZFMP_IN(const zfchar *, errorHint))

ZF_NAMESPACE_GLOBAL_END

