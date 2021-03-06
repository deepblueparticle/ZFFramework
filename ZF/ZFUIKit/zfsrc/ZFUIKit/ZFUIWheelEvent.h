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
 * @file ZFUIWheelEvent.h
 * @brief wheel event for ui elements
 */

#ifndef _ZFI_ZFUIWheelEvent_h_
#define _ZFI_ZFUIWheelEvent_h_

#include "ZFUIEvent.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
/**
 * @brief wheel event for ui elements
 */
zffinal zfclass ZF_ENV_EXPORT ZFUIWheelEvent : zfextends ZFUIEvent
{
    ZFOBJECT_DECLARE(ZFUIWheelEvent, ZFUIEvent)

protected:
    zfoverride
    virtual void objectInfoOnAppend(ZF_IN_OUT zfstring &ret);

public:
    /**
     * @brief wheel rotate count in x direction
     *
     * positive value means wheel from left to right
     */
    zfint wheelX;
    /**
     * @brief see #wheelX
     */
    zfint wheelY;

public:
    ZFCACHEABLE_DECLARE(ZFUIWheelEvent)

protected:
    zfoverride
    virtual void cacheableOnReset(void);
};

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFUIWheelEvent_h_

