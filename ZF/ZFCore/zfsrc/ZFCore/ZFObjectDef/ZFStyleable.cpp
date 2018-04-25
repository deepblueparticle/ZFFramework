/* ====================================================================== *
 * Copyright (c) 2010-2018 ZFFramework
 * Github repo: https://github.com/ZFFramework/ZFFramework
 * Home page: http://ZFFramework.com
 * Blog: http://zsaber.com
 * Contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/LICENSE
 * ====================================================================== */
#include "ZFStyleable.h"
#include "ZFObjectImpl.h"
#include "ZFObjectUtil.h"
#include "ZFClassUtil.h"
#include "ZFPropertyUtil.h"
#include "ZFListenerDeclare.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFStyleable *ZFStyleable::defaultStyle(void)
{
    const ZFMethod *method = this->classData()->methodForName(zfText("DefaultStyleReflect"));
    if(method != zfnull)
    {
        return method->executeStatic<zfautoObject>().to<ZFStyleable *>();
    }
    else
    {
        return zfnull;
    }
}

// ============================================================
zfclass _ZFP_I_ZFStyleable_PropertyTypeHolder : zfextends ZFObject
{
    ZFOBJECT_DECLARE(_ZFP_I_ZFStyleable_PropertyTypeHolder, ZFObject)

public:
    ZFCoreArrayPOD<const ZFProperty *> normalProperty;
    ZFCoreArrayPOD<const ZFProperty *> styleableProperty;
    ZFCoreArrayPOD<const ZFProperty *> copyableProperty;
};

// ============================================================
void ZFStyleable::styleableCopyFrom(ZF_IN ZFStyleable *anotherStyleable)
{
    if(anotherStyleable == zfnull)
    {
        return ;
    }
    _ZFP_I_ZFStyleable_PropertyTypeHolder *holderTmp = this->_ZFP_ZFStyleable_getPropertyTypeHolder();
    const ZFClass *thisCls = this->classData();
    const ZFClass *anotherCls = anotherStyleable->classData();
    ZFObject *anotherStyleableObject = anotherStyleable->toObject();;
    const ZFProperty *property = zfnull;

    for(zfindex i = holderTmp->normalProperty.count() - 1; i != zfindexMax(); --i)
    {
        property = holderTmp->normalProperty[i];
        if(!anotherCls->classIsTypeOf(property->propertyOwnerClass()))
        {
            continue;
        }
        if(!thisCls->_ZFP_ZFClass_propertyInitStepIsTheSame(property, anotherCls)
            || property->callbackIsValueAccessed(property, anotherStyleableObject))
        {
            this->styleableOnCopyPropertyFrom(anotherStyleable, property, ZFStyleable::PropertyTypeNormal);
        }
    }
    for(zfindex i = holderTmp->styleableProperty.count() - 1; i != zfindexMax(); --i)
    {
        property = holderTmp->styleableProperty[i];
        if(!anotherCls->classIsTypeOf(property->propertyOwnerClass()))
        {
            continue;
        }
        if(!thisCls->_ZFP_ZFClass_propertyInitStepIsTheSame(property, anotherCls)
            || property->callbackIsValueAccessed(property, anotherStyleableObject))
        {
            this->styleableOnCopyPropertyFrom(anotherStyleable, property, ZFStyleable::PropertyTypeStyleable);
        }
    }
    for(zfindex i = holderTmp->copyableProperty.count() - 1; i != zfindexMax(); --i)
    {
        property = holderTmp->copyableProperty[i];
        if(!anotherCls->classIsTypeOf(property->propertyOwnerClass()))
        {
            continue;
        }
        if(!thisCls->_ZFP_ZFClass_propertyInitStepIsTheSame(property, anotherCls)
            || property->callbackIsValueAccessed(property, anotherStyleableObject))
        {
            this->styleableOnCopyPropertyFrom(anotherStyleable, property, ZFStyleable::PropertyTypeCopyable);
        }
    }

    this->styleableOnCopyFrom(anotherStyleable);
}
ZFStyleable::PropertyType ZFStyleable::styleableOnCheckPropertyType(ZF_IN const ZFProperty *property)
{
    if(property->propertyIsRetainProperty()
        && property->setterMethod()->methodPrivilegeType() == ZFMethodPrivilegeTypePrivate
        && property->getterMethod()->methodPrivilegeType() != ZFMethodPrivilegeTypePrivate)
    {
        if(property->propertyClassOfRetainProperty()->classIsTypeOf(ZFStyleable::ClassData()))
        {
            return ZFStyleable::PropertyTypeStyleable;
        }
        else if(property->propertyClassOfRetainProperty()->classIsTypeOf(ZFCopyable::ClassData()))
        {
            return ZFStyleable::PropertyTypeCopyable;
        }
    }
    if(property->setterMethod()->methodPrivilegeType() == ZFMethodPrivilegeTypePrivate
        || property->getterMethod()->methodPrivilegeType() == ZFMethodPrivilegeTypePrivate)
    {
        return ZFStyleable::PropertyTypeNotStyleable;
    }
    return ZFStyleable::PropertyTypeNormal;
}

void ZFStyleable::styleableOnCopyPropertyFrom(ZF_IN ZFStyleable *anotherStyleable,
                                              ZF_IN const ZFProperty *property,
                                              ZF_IN ZFStyleable::PropertyType propertyType)
{
    switch(propertyType)
    {
        case ZFStyleable::PropertyTypeNormal:
        {
            ZFPropertyCopy(property, this->toObject(), anotherStyleable->toObject());
        }
            break;
        case ZFStyleable::PropertyTypeStyleable:
        {
            ZFStyleable *selfPropertyValue = ((const zfautoObject *)property->callbackValueGet(property, this->toObject()))->to<ZFStyleable *>();
            ZFStyleable *anotherPropertyValue = ((const zfautoObject *)property->callbackValueGet(property, anotherStyleable->toObject()))->to<ZFStyleable *>();
            if(selfPropertyValue != zfnull && anotherPropertyValue != zfnull)
            {
                selfPropertyValue->styleableCopyFrom(anotherPropertyValue);
            }
        }
            break;
        case ZFStyleable::PropertyTypeCopyable:
        {
            ZFCopyable *selfPropertyValue = ((const zfautoObject *)property->callbackValueGet(property, this->toObject()))->to<ZFCopyable *>();
            ZFObject *anotherPropertyValue = ((const zfautoObject *)property->callbackValueGet(property, anotherStyleable->toObject()))->toObject();
            if(selfPropertyValue != zfnull && anotherPropertyValue != zfnull)
            {
                selfPropertyValue->copyFrom(anotherPropertyValue);
            }
        }
            break;
        case ZFStyleable::PropertyTypeNotStyleable:
        default:
            zfCoreCriticalShouldNotGoHere();
            return ;
    }
}

_ZFP_I_ZFStyleable_PropertyTypeHolder *ZFStyleable::_ZFP_ZFStyleable_getPropertyTypeHolder(void)
{
    zfCoreMutexLocker();
    _ZFP_I_ZFStyleable_PropertyTypeHolder *holder = this->classData()->classTagGet<_ZFP_I_ZFStyleable_PropertyTypeHolder *>(
        _ZFP_I_ZFStyleable_PropertyTypeHolder::ClassData()->className());
    if(holder == zfnull)
    {
        zflockfree_zfblockedAlloc(_ZFP_I_ZFStyleable_PropertyTypeHolder, holderTmp);

        const ZFCoreArrayPOD<const ZFProperty *> allProperty = ZFClassUtil::allProperty(this->classData());
        const ZFProperty *propertyTmp = zfnull;
        for(zfindex i = 0; i < allProperty.count(); ++i)
        {
            propertyTmp = allProperty[i];
            switch(this->styleableOnCheckPropertyType(propertyTmp))
            {
                case ZFStyleable::PropertyTypeNotStyleable:
                    break;
                case ZFStyleable::PropertyTypeNormal:
                    holderTmp->normalProperty.add(propertyTmp);
                    break;
                case ZFStyleable::PropertyTypeStyleable:
                    holderTmp->styleableProperty.add(propertyTmp);
                    break;
                case ZFStyleable::PropertyTypeCopyable:
                    holderTmp->copyableProperty.add(propertyTmp);
                    break;
            }
        }

        holder = holderTmp;
        this->classData()->classTagSet(
            _ZFP_I_ZFStyleable_PropertyTypeHolder::ClassData()->className(),
            holderTmp);
        this->ClassData()->classDataChangeAutoRemoveTagAdd(_ZFP_I_ZFStyleable_PropertyTypeHolder::ClassData()->className());
    }
    return holder;
}

// ============================================================
ZFOBJECT_REGISTER(ZFStyleableObject)

// ============================================================
ZF_STATIC_INITIALIZER_INIT(ZFStyleableDefaultStyleDataHolder)
{
}
ZFCoreMap instanceDataMap; // _ZFP_ZFStyleableDefaultPointerHolder *
ZF_STATIC_INITIALIZER_END(ZFStyleableDefaultStyleDataHolder)

_ZFP_ZFStyleableDefaultPointerHolder *_ZFP_ZFStyleableDefaultRefAccess(ZF_IN const zfchar *name)
{
    zfCoreMutexLocker();
    ZFCoreMap &m = ZF_STATIC_INITIALIZER_INSTANCE(ZFStyleableDefaultStyleDataHolder)->instanceDataMap;
    ZFCorePointerBase *v = m.get(name);
    if(v == zfnull)
    {
        m.set(name, ZFCorePointerForObject<_ZFP_ZFStyleableDefaultPointerHolder *>(zfnew(_ZFP_ZFStyleableDefaultPointerHolder)));
        v = m.get(name);
    }
    return v->pointerValueT<_ZFP_ZFStyleableDefaultPointerHolder *>();
}

// ============================================================
zfclass _ZFP_ZFStyleDefaultApplyAutoCopyTaskData : zfextends ZFObject
{
    ZFOBJECT_DECLARE(_ZFP_ZFStyleDefaultApplyAutoCopyTaskData, ZFObject)

public:
    ZFCoreArrayPOD<ZFObjectHolder *> styles;
};
ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(ZFStyleDefaultApplyAutoCopyDataHolder, ZFLevelZFFrameworkEssential)
{
    this->styleOnDeallocListener = ZFCallbackForRawFunction(zfself::styleOnDealloc);
    this->defaultStyleOnChangeListener = ZFCallbackForRawFunction(zfself::defaultStyleOnChange);
}
public:
    ZFListener styleOnDeallocListener;
    ZFListener defaultStyleOnChangeListener;
public:
    static ZFLISTENER_PROTOTYPE_EXPAND(styleOnDealloc)
    {
        zfCoreMutexLocker();

        ZFStyleable *defaultStyle = listenerData.sender->to<ZFStyleable *>()->defaultStyle();
        zfCoreAssert(defaultStyle != zfnull);
        _ZFP_ZFStyleDefaultApplyAutoCopyTaskData *taskData = defaultStyle->toObject()
            ->tagGet<_ZFP_ZFStyleDefaultApplyAutoCopyTaskData *>(_ZFP_ZFStyleDefaultApplyAutoCopyTaskData::ClassData()->className());
        zfCoreAssert(taskData != zfnull);

        taskData->styles.removeElement(listenerData.sender->objectHolder());

        if(taskData->styles.isEmpty())
        {
            defaultStyle->toObject()->tagRemove(_ZFP_ZFStyleDefaultApplyAutoCopyTaskData::ClassData()->className());
            defaultStyle->toObject()->observerRemove(ZFObject::EventObjectPropertyValueOnUpdate(),
                ZF_GLOBAL_INITIALIZER_INSTANCE(ZFStyleDefaultApplyAutoCopyDataHolder)->defaultStyleOnChangeListener);
        }
    }
    static ZFLISTENER_PROTOTYPE_EXPAND(defaultStyleOnChange)
    {
        zfCoreMutexLocker();

        const ZFProperty *property = listenerData.param0->to<ZFPointerHolder *>()->holdedDataPointer<const ZFProperty *>();
        ZFStyleable *defaultStyle = listenerData.sender->to<ZFStyleable *>();
        _ZFP_ZFStyleDefaultApplyAutoCopyTaskData *taskData = defaultStyle->toObject()
            ->tagGet<_ZFP_ZFStyleDefaultApplyAutoCopyTaskData *>(_ZFP_ZFStyleDefaultApplyAutoCopyTaskData::ClassData()->className());

        ZFCoreArrayPOD<ZFObjectHolder *> styles;
        styles.copyFrom(taskData->styles);
        for(zfindex i = 0; i < styles.count(); ++i)
        {
            ZFPropertyCopy(property, styles[i]->objectHolded(), listenerData.sender);
        }
    }
ZF_GLOBAL_INITIALIZER_END(ZFStyleDefaultApplyAutoCopyDataHolder)

void ZFStyleDefaultApplyAutoCopy(ZF_IN ZFStyleable *style)
{
    zfCoreMutexLocker();
    if(style != zfnull && !style->styleableIsDefaultStyle())
    {
        ZFStyleable *defaultStyle = style->defaultStyle();
        if(defaultStyle != zfnull)
        {
            _ZFP_ZFStyleDefaultApplyAutoCopyTaskData *taskData = defaultStyle->toObject()
                ->tagGet<_ZFP_ZFStyleDefaultApplyAutoCopyTaskData *>(_ZFP_ZFStyleDefaultApplyAutoCopyTaskData::ClassData()->className());
            if(taskData == zfnull)
            {
                taskData = zfAlloc(_ZFP_ZFStyleDefaultApplyAutoCopyTaskData);
                defaultStyle->toObject()->tagSet(_ZFP_ZFStyleDefaultApplyAutoCopyTaskData::ClassData()->className(), taskData);
                zfRelease(taskData);

                defaultStyle->toObject()->observerAdd(ZFObject::EventObjectPropertyValueOnUpdate(),
                    ZF_GLOBAL_INITIALIZER_INSTANCE(ZFStyleDefaultApplyAutoCopyDataHolder)->defaultStyleOnChangeListener);
            }
            taskData->styles.add(style->toObject()->objectHolder());
            style->toObject()->observerAdd(ZFObject::EventObjectBeforeDealloc(),
                ZF_GLOBAL_INITIALIZER_INSTANCE(ZFStyleDefaultApplyAutoCopyDataHolder)->styleOnDeallocListener);
        }
    }
}

ZF_NAMESPACE_GLOBAL_END

#if _ZFP_ZFOBJECT_METHOD_REG
#include "../ZFObject.h"
ZF_NAMESPACE_GLOBAL_BEGIN

ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_0(ZFStyleable, ZFStyleable *, defaultStyle)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_1(ZFStyleable, void, styleableCopyFrom, ZFMP_IN(ZFStyleable *, anotherStyleable))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_0(ZFStyleable, zfbool, styleableIsDefaultStyle)

ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_1(void, ZFStyleDefaultApplyAutoCopy, ZFMP_IN(ZFStyleable *, style))

ZF_NAMESPACE_GLOBAL_END
#endif

