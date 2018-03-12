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
 * @file ZFMutex.h
 * @brief mutex utility
 */

#ifndef _ZFI_ZFMutex_h_
#define _ZFI_ZFMutex_h_

#include "ZFObject.h"
ZF_NAMESPACE_GLOBAL_BEGIN

/**
 * @brief mutex utility
 */
zfclass ZF_ENV_EXPORT ZFMutex : zfextends ZFObject
{
    ZFOBJECT_DECLARE_WITH_CUSTOM_CTOR(ZFMutex, ZFObject)
protected:
    /** @cond ZFPrivateDoc */
    ZFMutex(void) : noWarningIfImplNotAvailable(zffalse) {}
    /** @endcond */

protected:
    /**
     * @brief whether to warning if no implementation available
     */
    ZFOBJECT_ON_INIT_DECLARE_1(ZFMP_IN(zfbool, noWarningIfImplNotAvailable))
    zfoverride
    virtual void objectOnInit(void) {zfsuper::objectOnInit();}

public:
    /**
     * @brief wait until successfully acquired the lock
     *
     * wait until none of other threads hold the lock, then acquire the lock\n
     * you must call mutexUnlock to release lock,
     * and mutexLock and mutexUnlock must be paired
     * @see mutexTryLock, mutexUnlock
     */
    virtual void mutexLock(void);
    /**
     * @brief try to lock, or return false immediately if failed
     * @note if mutexTryLock success, you should unlock it somewhere,
     *   otherwise, there's no need to unlock
     * @see mutexLock, mutexUnlock
     */
    virtual zfbool mutexTryLock(void);
    /**
     * @brief release the lock, must be paired with mutexLock or mutexTryLock,
     *   and must be called in the same thread where mutexLock or mutexTryLock called
     */
    virtual void mutexUnlock(void);

private:
    zfbool noWarningIfImplNotAvailable;
};

zffinal zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFMutexLocker
{
    ZFCLASS_DISALLOW_COPY_CONSTRUCTOR(_ZFP_ZFMutexLocker)
public:
    _ZFP_ZFMutexLocker(ZFMutex *mutex)
    : m_mutex(mutex)
    {
        zfCoreAssertWithMessage(mutex != zfnull, zfTextA("null mutex"));
        mutex->mutexLock();
    }
    ~_ZFP_ZFMutexLocker(void)
    {
        m_mutex->mutexUnlock();
    }
private:
    ZFMutex *m_mutex;
};

/**
 * @brief convient mutex locker
 *
 * typical usage:
 * @code
 *   ZFMutex *mutex = ...;
 *   ...
 *   { // code block
 *     ZFMutexLocker(mutex);
 *     // code that protected by mutex
 *   } // mutex would be unlocked after brace
 * @endcode
 * @note never use "new" to create a ZFMutexLocker
 */
#define ZFMutexLocker(mutex) \
    _ZFP_ZFMutexLocker _ZFP_ZFMutexLocker_hold(mutex)

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFMutex_h_

