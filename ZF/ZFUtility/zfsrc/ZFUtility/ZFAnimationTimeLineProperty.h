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
 * @file ZFAnimationTimeLineProperty.h
 * @brief animated update object's property base on time line
 */

#ifndef _ZFI_ZFAnimationTimeLineProperty_h_
#define _ZFI_ZFAnimationTimeLineProperty_h_

#include "ZFAnimationTimeLine.h"
#include "ZFTimeLineProperty.h"
ZF_NAMESPACE_GLOBAL_BEGIN

/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFAnimationTimeLineProperty_step zfText("step")

// ============================================================
zfclassFwd _ZFP_ZFAnimationTimeLinePropertyPrivate;
/**
 * @brief animated update object's property base on time line
 *
 * serializable data:
 * @code
 *   <ZFAnimationTimeLineProperty>
 *       // all property change steps
 *       <ZFTimeLineProperty_XXX category="step" ... />
 *   </ZFAnimationTimeLineProperty>
 * @endcode
 */
zfclass ZF_ENV_EXPORT ZFAnimationTimeLineProperty : zfextends ZFAnimationTimeLine
{
    ZFOBJECT_DECLARE(ZFAnimationTimeLineProperty, ZFAnimationTimeLine)

protected:
    zfoverride
    virtual zfbool serializableOnSerializeFromData(ZF_IN const ZFSerializableData &serializableData,
                                                   ZF_OUT_OPT zfstring *outErrorHint = zfnull,
                                                   ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull);
    zfoverride
    virtual zfbool serializableOnSerializeToData(ZF_IN_OUT ZFSerializableData &serializableData,
                                                 ZF_IN ZFSerializable *referencedOwnerOrNull,
                                                 ZF_OUT_OPT zfstring *outErrorHint = zfnull);

    // ============================================================
    // object
protected:
    zfoverride
    virtual void objectOnInit(void);
    zfoverride
    virtual void objectOnDealloc(void);
    zfoverride
    virtual void objectOnDeallocPrepare(void);

public:
    zfoverride
    virtual zfidentity objectHash(void);
    zfoverride
    virtual ZFCompareResult objectCompare(ZF_IN ZFObject *anotherObj);

    // ============================================================
    // property change step
public:
    /**
     * @brief add a property change step,
     *   #ZFAnimation::aniTarget's property would be change accorrding this step
     */
    ZFMETHOD_DECLARE_1(void, stepAdd,
                       ZFMP_IN(ZFTimeLineProperty *, step))
    /** @brief see #stepAdd */
    ZFMETHOD_DECLARE_1(void, stepRemove,
                       ZFMP_IN(ZFTimeLineProperty *, step))
    /** @brief see #stepAdd */
    ZFMETHOD_DECLARE_1(void, stepRemoveAtIndex,
                       ZFMP_IN(zfindex, index))
    /** @brief see #stepAdd */
    ZFMETHOD_DECLARE_0(void, stepRemoveAll)
    /** @brief see #stepAdd */
    ZFMETHOD_DECLARE_0(zfindex, stepCount)
    /** @brief see #stepAdd */
    ZFMETHOD_DECLARE_1(ZFTimeLineProperty *, stepAtIndex,
                       ZFMP_IN(zfindex, index))

    // ============================================================
    // start stop
protected:
    zfoverride
    virtual zfbool aniImplCheckValid(void);

protected:
    zfoverride
    virtual void aniOnStart(void);
    zfoverride
    virtual void aniOnStop(void);
    zfoverride
    virtual void aniTimeLineOnUpdate(ZF_IN zffloat progress);

private:
    _ZFP_ZFAnimationTimeLinePropertyPrivate *d;
};

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFAnimationTimeLineProperty_h_

