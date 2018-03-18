/* ====================================================================== *
 * Copyright (c) 2010-2018 ZFFramework
 * Github repo: https://github.com/ZFFramework/ZFFramework
 * Home page: http://ZFFramework.com
 * Blog: http://zsaber.com
 * Contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/LICENSE
 * ====================================================================== */
#include "ZF2048UIBlock.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFSTYLE_DEFAULT_DEFINE(ZF2048UIBlock)

ZFOBJECT_REGISTER(ZF2048UIBlock)
ZFCACHEABLE_DEFINE_WITH_MAX(ZF2048UIBlock, ZF2048UIBlock, 16)

ZFPROPERTY_OVERRIDE_ON_UPDATE_DEFINE(ZF2048UIBlock, ZF2048Value, blockValue)
{
    if(this->blockValue() == 0)
    {
        zfSkinApplyCancelZFStyleable(this);
        this->blockTitle()->viewVisibleSet(zffalse);
        return ;
    }

    zfstring skinKey = zfstringWithFormat(zfText("ZF2048_block_%d"), (zfint)this->blockValue());
    zfautoObject skin = zfSkin(skinKey);
    if(skin == zfnull)
    {
        zfSkinApplyZFStyleable(this, zfText("ZF2048_block_na"));
        this->blockTitle()->textSet(zfstringWithFormat(zfText("%d"), (zfint)this->blockValue()));
        this->blockTitle()->viewVisibleSet(zftrue);
    }
    else
    {
        zfSkinApplyZFStyleable(this, skinKey);
        this->blockTitle()->viewVisibleSet(zffalse);
    }
}

void ZF2048UIBlock::objectOnInit(void)
{
    zfsuper::objectOnInit();
    this->internalFgViewAdd(this->blockTitle());
    this->blockTitle()->layoutParam()->layoutAlignSet(ZFUIAlign::e_Center);
    this->blockTitle()->viewVisibleSet(zffalse);
    this->blockTitle()->textAlignSet(ZFUIAlign::e_Center);
    this->blockTitle()->textColorSet(ZFUIColorWhite());
    this->blockTitle()->textShadowColorSet(ZFUIColorGrayDark());
    this->blockTitle()->textAppearanceSet(ZFUITextAppearance::e_Bold);
    this->blockTitle()->textSizeSet(24);
}

ZF_NAMESPACE_GLOBAL_END

