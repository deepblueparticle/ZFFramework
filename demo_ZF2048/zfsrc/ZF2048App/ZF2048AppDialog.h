/* ====================================================================== *
 * Copyright (c) 2010-2018 ZFFramework
 * Github repo: https://github.com/ZFFramework/ZFFramework
 * Home page: http://ZFFramework.com
 * Blog: http://zsaber.com
 * Contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/LICENSE
 * ====================================================================== */
#ifndef _ZFI_ZF2048AppDialog_h_
#define _ZFI_ZF2048AppDialog_h_

#include "ZFUIWidget.h"
ZF_NAMESPACE_GLOBAL_BEGIN

zfclassFwd _ZFP_ZF2048AppDialogPrivate;
zfclass ZF2048AppDialog : zfextends ZFUIDialog
{
    ZFOBJECT_DECLARE(ZF2048AppDialog, ZFUIDialog)

    ZFPROPERTY_OVERRIDE_ON_INIT_DECLARE(zfbool, dialogHideWhenTouchOutside)
    {
        propertyValue = zftrue;
    }
    ZFPROPERTY_OVERRIDE_ON_INIT_DECLARE(zfbool, dialogHideWhenClickBack)
    {
        propertyValue = zftrue;
    }

    ZFPROPERTY_ASSIGN(zfstring, dialogTitle)
    ZFPROPERTY_OVERRIDE_ON_UPDATE_DECLARE(zfstring, dialogTitle);

    ZFPROPERTY_RETAIN(ZFUIView *, dialogContent)
    ZFPROPERTY_OVERRIDE_ON_ATTACH_DECLARE(ZFUIView *, dialogContent);
    ZFPROPERTY_OVERRIDE_ON_DETACH_DECLARE(ZFUIView *, dialogContent);

protected:
    zfoverride
    virtual void objectOnInit(void);
    zfoverride
    virtual void objectOnDealloc(void);

private:
    _ZFP_ZF2048AppDialogPrivate *d;
    friend zfclassFwd _ZFP_ZF2048AppDialogPrivate;
};

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZF2048AppDialog_h_

