/* ====================================================================== *
 * Copyright (c) 2010-2018 ZFFramework
 * Github repo: https://github.com/ZFFramework/ZFFramework
 * Home page: http://ZFFramework.com
 * Blog: http://zsaber.com
 * Contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/LICENSE
 * ====================================================================== */
#include "ZFCallerInfo.h"

ZF_NAMESPACE_GLOBAL_BEGIN

const ZFCallerInfo &_ZFP_ZFCallerInfoEmpty(void)
{
    static ZFCallerInfo d;
    return d;
}

ZF_NAMESPACE_GLOBAL_END

