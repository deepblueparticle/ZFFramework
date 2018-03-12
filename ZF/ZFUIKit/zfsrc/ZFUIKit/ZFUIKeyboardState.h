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
 * @file ZFUIKeyboardState.h
 * @brief hardware keyboard state helper
 */

#ifndef _ZFI_ZFUIKeyboardState_h_
#define _ZFI_ZFUIKeyboardState_h_

#include "ZFUIKeyCode.h"

ZF_NAMESPACE_GLOBAL_BEGIN

/**
 * @brief hardware keyboard state helper
 */
zffinal zfclass ZF_ENV_EXPORT ZFUIKeyboardState : zfextends ZFObject
{
    ZFOBJECT_DECLARE(ZFUIKeyboardState, ZFObject)

    ZFOBJECT_SINGLETON_DECLARE(ZFUIKeyboardState, instance)

public:
    /**
     * @brief see #ZFObject::observerNotify
     *
     * called when pressed key changed
     */
    ZFOBSERVER_EVENT(KeyPressedOnChange)

public:
    /**
     * @brief true is key is pressed
     */
    ZFMETHOD_DECLARE_1(zfbool, keyPressed,
                       ZFMP_IN(ZFUIKeyCodeEnum, keyCode))
    /**
     * @brief true is key is pressed
     */
    ZFMETHOD_DECLARE_1(zfbool, keyPressedRaw,
                       ZFMP_IN(zfflags, keyCodeRaw))

protected:
    zfoverride
    virtual void objectInfoOnAppend(ZF_IN_OUT zfstring &ret);
};

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFUIKeyboardState_h_

