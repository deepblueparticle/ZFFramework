/* ====================================================================== *
 * Copyright (c) 2010-2018 ZFFramework
 * Github repo: https://github.com/ZFFramework/ZFFramework
 * Home page: http://ZFFramework.com
 * Blog: http://zsaber.com
 * Contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/LICENSE
 * ====================================================================== */
#include "ZFObjectIO_zfsd.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFOBJECTIO_DEFINE(zfsd, zfText("zfsd"), {
        return zftrue;
    }, {
        return ZFObjectFromInput(ret, input, outErrorHint);
    }, {
        return ZFObjectToOutput(output, obj, outErrorHint);
    })

ZF_NAMESPACE_GLOBAL_END

