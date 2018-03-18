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
 * @file ZFUIViewStateAni_move.h
 * @brief move animation for #ZFUIViewStateAniStart
 */

#ifndef _ZFI_ZFUIViewStateAni_move_h_
#define _ZFI_ZFUIViewStateAni_move_h_

#include "ZFUIViewStateAni.h"
#include "ZFAnimationNativeView.h"

ZF_NAMESPACE_GLOBAL_BEGIN

/**
 * @brief move animation for #ZFUIViewStateAniStart
 *
 * if a view's #ZFUIView::layoutedFrame changed (comparing to #ZFUIView::layoutedFramePrev),
 * and #ZFUIView::layoutedFramePrev's size is not zero,
 * a move animation of #ZFAnimationNativeView would be applied
 */
zfclass ZF_ENV_EXPORT ZFUIViewStateAniSettingForMove : zfextends ZFStyleableObject
{
    ZFOBJECT_DECLARE(ZFUIViewStateAniSettingForMove, ZFStyleableObject)
    ZFOBJECT_SINGLETON_DECLARE_DETAIL(private, public, ZFUIViewStateAniSettingForMove, instance)

    /**
     * @brief whether enable this ani
     */
    ZFPROPERTY_ASSIGN_WITH_INIT(zfbool, aniEnable, zftrue)
    /**
     * @brief filter to ignore views from being auto animated, empty by default
     */
    ZFFilterForZFObject aniFilter;
    /**
     * @brief minimum offset to apply the animation, #ZFUIGlobalStyle::itemSpace by default
     */
    ZFPROPERTY_ASSIGN_WITH_INIT(zfint, aniTolerance, ZFUIGlobalStyle::DefaultStyle()->itemSpace())
    /**
     * @brief ani duration, #ZFUIGlobalStyle::aniDurationLong by default
     */
    ZFPROPERTY_ASSIGN_WITH_INIT(zftimet, aniDuration, ZFUIGlobalStyle::DefaultStyle()->aniDurationLong())
    /**
     * @brief ani curve, #ZFAnimationNativeViewCurve::e_EaseOut by default
     */
    ZFPROPERTY_ASSIGN_WITH_INIT(ZFAnimationNativeViewCurveEnum, aniCurve, ZFAnimationNativeViewCurve::e_EaseOut)
};

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFUIViewStateAni_move_h_

