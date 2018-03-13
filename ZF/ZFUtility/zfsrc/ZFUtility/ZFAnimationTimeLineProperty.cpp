/* ====================================================================== *
 * Copyright (c) 2010-2018 ZFFramework
 * Github repo: https://github.com/ZFFramework/ZFFramework
 * Home page: http://ZFFramework.com
 * Blog: http://zsaber.com
 * Contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/LICENSE
 * ====================================================================== */
#include "ZFAnimationTimeLineProperty.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
// _ZFP_ZFAnimationTimeLinePropertyPrivate
zfclassNotPOD _ZFP_ZFAnimationTimeLinePropertyPrivate
{
public:
    ZFCoreArrayPOD<ZFTimeLineProperty *> steps;
};

// ============================================================
ZFOBJECT_REGISTER(ZFAnimationTimeLineProperty)

// ============================================================
// serialize
zfbool ZFAnimationTimeLineProperty::serializableOnSerializeFromData(ZF_IN const ZFSerializableData &serializableData,
                                                                    ZF_OUT_OPT zfstring *outErrorHint /* = zfnull */,
                                                                    ZF_OUT_OPT ZFSerializableData *outErrorPos /* = zfnull */)
{
    if(!zfsuperI(ZFSerializable)::serializableOnSerializeFromData(serializableData, outErrorHint, outErrorPos)) {return zffalse;}

    this->stepRemoveAll();

    for(zfindex i = 0; i < serializableData.elementCount(); ++i)
    {
        const ZFSerializableData &categoryData = serializableData.elementAtIndex(i);
        if(categoryData.resolved()) {continue;}
        const zfchar *category = ZFSerializableUtil::checkCategory(categoryData);
        if(category == zfnull) {continue;}

        if(zfscmpTheSame(category, ZFSerializableKeyword_ZFAnimationTimeLineProperty_step))
        {
            zfautoObject step;
            if(!ZFObjectFromData(step, categoryData, outErrorHint, outErrorPos))
            {
                return zffalse;
            }
            if(step == zfautoObjectNull())
            {
                ZFSerializableUtil::errorOccurred(outErrorHint, outErrorPos, categoryData,
                    zfText("invalid step: %s"), ZFObjectInfoOfInstance(step.toObject()).cString());
                return zffalse;
            }
            this->stepAdd(step);

            categoryData.resolveMark();
        }
    }
    return zftrue;
}
zfbool ZFAnimationTimeLineProperty::serializableOnSerializeToData(ZF_IN_OUT ZFSerializableData &serializableData,
                                                                  ZF_IN ZFSerializable *referencedOwnerOrNull,
                                                                  ZF_OUT_OPT zfstring *outErrorHint /* = zfnull */)
{
    if(!zfsuperI(ZFSerializable)::serializableOnSerializeToData(serializableData, referencedOwnerOrNull, outErrorHint)) {return zffalse;}
    zfself *ref = ZFCastZFObject(zfself *, referencedOwnerOrNull);

    if(ref == zfnull)
    {
        for(zfindex i = 0; i < d->steps.count(); ++i)
        {
            ZFSerializableData stepData;
            if(!ZFObjectToData(stepData, d->steps[i], outErrorHint))
            {
                return zffalse;
            }
            stepData.categorySet(ZFSerializableKeyword_ZFAnimationTimeLineProperty_step);
            serializableData.elementAdd(stepData);
        }
    }
    else
    {
        zfbool mismatch = zffalse;
        if(d->steps.count() != ref->d->steps.count())
        {
            mismatch = zftrue;
        }
        if(!mismatch)
        {
            for(zfindex i = 0; i < d->steps.count(); ++i)
            {
                if(d->steps[i]->objectCompare(ref->d->steps[i]) != ZFCompareTheSame)
                {
                    mismatch = zftrue;
                    break;
                }
            }
        }
        if(mismatch)
        {
            ZFSerializableUtil::errorOccurred(outErrorHint,
                zfText("steps mismatch: %s, and: %s"),
                    d->steps.objectInfoOfContent(ZFCoreElementInfoGetter<ZFTimeLineProperty *>::elementInfoGetter).cString(),
                    ref->d->steps.objectInfoOfContent(ZFCoreElementInfoGetter<ZFTimeLineProperty *>::elementInfoGetter).cString());
            return zffalse;
        }
    }

    return zftrue;
}

// ============================================================
// object
void ZFAnimationTimeLineProperty::objectOnInit(void)
{
    zfsuper::objectOnInit();
    d = zfpoolNew(_ZFP_ZFAnimationTimeLinePropertyPrivate);
}
void ZFAnimationTimeLineProperty::objectOnDealloc(void)
{
    zfpoolDelete(d);
    d = zfnull;
    zfsuper::objectOnDealloc();
}
void ZFAnimationTimeLineProperty::objectOnDeallocPrepare(void)
{
    this->aniStop();
    this->stepRemoveAll();
    zfsuper::objectOnDeallocPrepare();
}

zfidentity ZFAnimationTimeLineProperty::objectHash(void)
{
    return zfidentityHash(zfsuper::objectHash()
        , d->steps.count()
        , (d->steps.isEmpty() ? zfidentityZero() : d->steps[0]->objectHash())
        );
}
ZFCompareResult ZFAnimationTimeLineProperty::objectCompare(ZF_IN ZFObject *anotherObj)
{
    if(zfsuper::objectCompare(anotherObj) != ZFCompareTheSame)
    {
        return ZFCompareUncomparable;
    }
    zfself *another = ZFCastZFObject(zfself *, anotherObj);
    if(another == zfnull) {return ZFCompareUncomparable;}

    if(d->steps.count() != another->d->steps.count())
    {
        return ZFCompareUncomparable;
    }
    for(zfindex i = 0; i < d->steps.count(); ++i)
    {
        if(d->steps[i]->objectCompare(another->d->steps[i]) != ZFCompareTheSame)
        {
            return ZFCompareUncomparable;
        }
    }
    return ZFCompareTheSame;
}

// ============================================================
// property change step
ZFMETHOD_DEFINE_1(ZFAnimationTimeLineProperty, void, stepAdd,
                  ZFMP_IN(ZFTimeLineProperty *, step))
{
    zfCoreAssert(!this->aniRunning());
    zfCoreAssert(step != zfnull);
    d->steps.add(zfRetain(step));
}
ZFMETHOD_DEFINE_1(ZFAnimationTimeLineProperty, void, stepRemove,
                  ZFMP_IN(ZFTimeLineProperty *, step))
{
    zfCoreAssert(!this->aniRunning());
    zfindex index = d->steps.find(step, ZFComparerCheckEqual);
    if(index != zfindexMax())
    {
        d->steps.remove(index);
        zfRelease(step);
    }
}
ZFMETHOD_DEFINE_1(ZFAnimationTimeLineProperty, void, stepRemoveAtIndex,
                  ZFMP_IN(zfindex, index))
{
    zfCoreAssert(!this->aniRunning());
    ZFTimeLineProperty *step = d->steps[index];
    d->steps.remove(index);
    zfRelease(step);
}
ZFMETHOD_DEFINE_0(ZFAnimationTimeLineProperty, void, stepRemoveAll)
{
    zfCoreAssert(!this->aniRunning());
    if(!d->steps.isEmpty())
    {
        ZFCoreArrayPOD<ZFTimeLineProperty *> tmp;
        tmp.copyFrom(d->steps);
        d->steps.removeAll();
        for(zfindex i = 0; i < tmp.count(); ++i)
        {
            zfRelease(tmp[i]);
        }
    }
}
ZFMETHOD_DEFINE_0(ZFAnimationTimeLineProperty, zfindex, stepCount)
{
    return d->steps.count();
}
ZFMETHOD_DEFINE_1(ZFAnimationTimeLineProperty, ZFTimeLineProperty *, stepAtIndex,
                  ZFMP_IN(zfindex, index))
{
    return d->steps.get(index);
}

// ============================================================
// start stop
zfbool ZFAnimationTimeLineProperty::aniImplCheckValid(void)
{
    if(!zfsuper::aniImplCheckValid() || this->aniTarget() == zfnull)
    {
        return zffalse;
    }
    if(!d->steps.isEmpty())
    {
        for(zfindex i = 0; i < d->steps.count(); ++i)
        {
            const ZFProperty *property = d->steps[i]->ownerProperty();
            if(property == zfnull || !this->aniTarget()->classData()->classIsTypeOf(property->propertyOwnerClass()))
            {
                return zffalse;
            }
        }
    }
    return zftrue;
}

void ZFAnimationTimeLineProperty::aniOnStart(void)
{
    zfidentity aniId = this->aniId();
    zfsuper::aniOnStart();
    for(zfindex i = 0; i < d->steps.count() && aniId == this->aniId(); ++i)
    {
        d->steps[i]->stateSave(this->aniTarget());
    }
}
void ZFAnimationTimeLineProperty::aniOnStop(void)
{
    zfidentity aniId = this->aniId();
    for(zfindex i = 0; i < d->steps.count() && aniId == this->aniId(); ++i)
    {
        d->steps[i]->stateRestore(this->aniTarget());
    }
    zfsuper::aniOnStop();
}
void ZFAnimationTimeLineProperty::aniTimeLineOnUpdate(ZF_IN zffloat progress)
{
    zfidentity aniId = this->aniId();
    zfsuper::aniTimeLineOnUpdate(progress);
    for(zfindex i = 0; i < d->steps.count() && aniId == this->aniId(); ++i)
    {
        d->steps[i]->progressUpdate(this->aniTarget(), progress);
    }
}

ZF_NAMESPACE_GLOBAL_END

