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
 * @file ZFCoreLevel.h
 * @brief level for logic which depends on order
 */
#ifndef _ZFI_ZFCoreLevel_h_
#define _ZFI_ZFCoreLevel_h_

#include "ZFCoreUtilStringConvert.h"

ZF_NAMESPACE_GLOBAL_BEGIN

/**
 * @brief level for logic which depends on order
 *
 * higher priority ensured to have smaller value
 */
typedef enum
{
    ZFLevelZFFrameworkStatic        = 0, /**< @brief ZFFramework static, for non-ZFObject-related meta data or global instance */
    ZFLevelZFFrameworkEssential     = 1, /**< @brief ZFFramework essential, for ZFObject-related meta data, or essential global instance */
    ZFLevelZFFrameworkHigh          = 2, /**< @brief ZFFramework high, for global instance */
    ZFLevelZFFrameworkNormal        = 3, /**< @brief ZFFramework, for logic initialization */
    ZFLevelZFFrameworkLow           = 4, /**< @brief ZFFramework low */

    ZFLevelAppEssential             = 5, /**< @brief app essential */
    ZFLevelAppHigh                  = 6, /**< @brief app high */
    ZFLevelAppNormal                = 7, /**< @brief app */
    ZFLevelAppLow                   = 8, /**< @brief app low */

    ZFLevelZFFrameworkPostLow       = 9, /**< @brief ZFFramework post low */
    ZFLevelZFFrameworkPostNormal    = 10, /**< @brief ZFFramework post normal */
    ZFLevelZFFrameworkPostHigh      = 11, /**< @brief ZFFramework post high */
    ZFLevelZFFrameworkPostEssential = 12, /**< @brief ZFFramework post essential */
    ZFLevelZFFrameworkPostStatic    = 13, /**< @brief ZFFramework post static */
} ZFLevel;

/** @brief string tokens */
#define ZFTOKEN_ZFLevelZFFrameworkStatic zfText("LevelZFFrameworkStatic")
/** @brief string tokens */
#define ZFTOKEN_ZFLevelZFFrameworkEssential zfText("LevelZFFrameworkEssential")
/** @brief string tokens */
#define ZFTOKEN_ZFLevelZFFrameworkHigh zfText("LevelZFFrameworkHigh")
/** @brief string tokens */
#define ZFTOKEN_ZFLevelZFFrameworkNormal zfText("LevelZFFrameworkNormal")
/** @brief string tokens */
#define ZFTOKEN_ZFLevelZFFrameworkLow zfText("LevelZFFrameworkLow")

/** @brief string tokens */
#define ZFTOKEN_ZFLevelAppEssential zfText("LevelAppEssential")
/** @brief string tokens */
#define ZFTOKEN_ZFLevelAppHigh zfText("LevelAppHigh")
/** @brief string tokens */
#define ZFTOKEN_ZFLevelAppNormal zfText("LevelAppNormal")
/** @brief string tokens */
#define ZFTOKEN_ZFLevelAppLow zfText("LevelAppLow")

/** @brief string tokens */
#define ZFTOKEN_ZFLevelZFFrameworkPostLow zfText("LevelZFFrameworkPostLow")
/** @brief string tokens */
#define ZFTOKEN_ZFLevelZFFrameworkPostNormal zfText("LevelZFFrameworkPostNormal")
/** @brief string tokens */
#define ZFTOKEN_ZFLevelZFFrameworkPostHigh zfText("LevelZFFrameworkPostHigh")
/** @brief string tokens */
#define ZFTOKEN_ZFLevelZFFrameworkPostEssential zfText("LevelZFFrameworkPostEssential")
/** @brief string tokens */
#define ZFTOKEN_ZFLevelZFFrameworkPostStatic zfText("LevelZFFrameworkPostStatic")

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFCoreLevel_h_

