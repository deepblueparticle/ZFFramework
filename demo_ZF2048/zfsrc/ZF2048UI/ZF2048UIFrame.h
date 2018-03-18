/* ====================================================================== *
 * Copyright (c) 2010-2018 ZFFramework
 * Github repo: https://github.com/ZFFramework/ZFFramework
 * Home page: http://ZFFramework.com
 * Blog: http://zsaber.com
 * Contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/LICENSE
 * ====================================================================== */
#ifndef _ZFI_ZF2048UIFrame_h_
#define _ZFI_ZF2048UIFrame_h_

#include "ZF2048UIBlock.h"
#include "ZF2048UISkin.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
// ZF2048UIFrame
zfclassFwd _ZFP_ZF2048UIFramePrivate;
/**
 * @brief linear container view that layout children in linear by specified orientation
 */
zfclass ZF2048UIFrame : zfextends ZFUIView
{
    ZFOBJECT_DECLARE(ZF2048UIFrame, ZFUIView)
    ZFSTYLE_DEFAULT_DECLARE(ZF2048UIFrame)

public:
    /**
     * called when swipe to move or press direction key to move,
     * param0 is the #ZFUIOrientation which indicates move direction
     */
    ZFOBSERVER_EVENT(FrameOnMove)

public:
    ZFPROPERTY_OVERRIDE_ON_INIT_DECLARE(zfbool, viewFocusable)
    {
        propertyValue = zftrue;
    }

    ZFPROPERTY_RETAIN(ZFUIImage *, frameBackgroundImage)
    ZFPROPERTY_OVERRIDE_ON_UPDATE_DECLARE(ZFUIImage *, frameBackgroundImage);

    ZFPROPERTY_ASSIGN_WITH_INIT(ZFUIMargin, frameMargin, ZFUIMarginMake(ZFUIGlobalStyle::DefaultStyle()->itemSpace()))
    ZFPROPERTY_OVERRIDE_ON_UPDATE_DECLARE(ZFUIMargin, frameMargin);

public:
    virtual void update(ZF_IN const ZF2048Value *data,
                        ZF_IN zfindex dataWidth,
                        ZF_IN zfindex dataHeight);
    virtual ZF2048UIBlock *blockAtIndex(ZF_IN zfindex posX, ZF_IN zfindex posY);
    virtual ZFUIRect blockRectAtIndex(ZF_IN zfindex posX, ZF_IN zfindex posY);

protected:
    virtual inline void frameOnMove(ZF_IN ZFUIOrientationEnum direction)
    {
        this->observerNotify(zfself::EventFrameOnMove(), zflineAlloc(ZFUIOrientation, direction));
    }

protected:
    zfoverride
    virtual void objectOnInit(void);
    zfoverride
    virtual void objectOnDealloc(void);

    zfoverride
    virtual void layoutOnLayoutPrepare(ZF_IN const ZFUIRect &bounds);
    zfoverride
    virtual void layoutOnLayout(ZF_IN const ZFUIRect &bounds);
    zfoverride
    virtual void internalBgViewOnLayout(ZF_IN const ZFUIRect &bounds);
    zfoverride
    virtual void viewEventOnMouseEvent(ZF_IN ZFUIMouseEvent *mouseEvent);
    zfoverride
    virtual void viewEventOnKeyEvent(ZF_IN ZFUIKeyEvent *keyEvent);

private:
    _ZFP_ZF2048UIFramePrivate *d;
    friend zfclassFwd _ZFP_ZF2048UIFramePrivate;
};

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZF2048UIFrame_h_

