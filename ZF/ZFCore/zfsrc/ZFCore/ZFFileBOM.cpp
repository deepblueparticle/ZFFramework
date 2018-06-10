/* ====================================================================== *
 * Copyright (c) 2010-2018 ZFFramework
 * Github repo: https://github.com/ZFFramework/ZFFramework
 * Home page: http://ZFFramework.com
 * Blog: http://zsaber.com
 * Contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/LICENSE
 * ====================================================================== */
#include "ZFFileBOM.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
ZFTYPEID_DEFINE_BY_STRING_CONVERTER(ZFFileBOM, ZFFileBOM, {
        zfmemset(v.BOM, 0, sizeof(v.BOM));
        if(src == zfnull || srcLen == 0)
        {
            return zftrue;
        }
        if(srcLen == zfindexMax())
        {
            srcLen = zfslen(src);
        }
        if((srcLen % 2) != 0 || srcLen >= ZFFileBOMMaxSize)
        {
            return zffalse;
        }

        for(zfindex i = 0; ; ++i, src += 2)
        {
            if(!zfsToIntT(v.BOM[i], src, 2, 16))
            {
                return zffalse;
            }
        }

        return zftrue;
    }, {
        for(zfindex i = 0; v.BOM[i] != 0x00; ++i)
        {
            zfstringAppend(s, zfText("%02X"), v.BOM[i]);
        }
        return zftrue;
    })

ZFCORETYPE_STRING_CONVERTER_DEFINE(ZFFileBOMList, ZFFileBOMList, {
        ZFCoreArrayPOD<ZFIndexRange> pos;
        if(!zfCoreDataPairSplitString(pos, zfindexMax(), src, srcLen))
        {
            return zffalse;
        }

        for(zfindex i = 0; i < pos.count(); ++i)
        {
            ZFFileBOM bom;
            if(!ZFFileBOMFromString(bom, src + pos[i].start, pos[i].count))
            {
                return zffalse;
            }
            v.add(bom);
        }
        return zftrue;
    }, {
        s += zfText("(");
        for(zfindex i = 0; i < v.count(); ++i)
        {
            if(i != 0)
            {
                s += zfText(", ");
            }
            ZFFileBOMToString(s, v[i]);
        }
        s += zfText(")");
        return zftrue;
    })

// ============================================================
static const ZFFileBOM &_ZFP_ZFFileBOMUTF8Init(void)
{
    static ZFFileBOM BOM = {{0xEF, 0xBB, 0xBF}};
    return BOM;
}
ZFEXPORT_VAR_READONLY_DEFINE(ZFFileBOM, ZFFileBOMUTF8, _ZFP_ZFFileBOMUTF8Init())

// ============================================================
ZFEXPORT_VAR_READONLY_DEFINE(ZFFileBOMList, ZFFileBOMListEmpty, ZFFileBOMList())

static const ZFFileBOMList &_ZFP_ZFFileBOMListDefaultInit(void)
{
    static ZFFileBOMList ret;
    ret.add(ZFFileBOMUTF8());
    return ret;
}
ZFEXPORT_VAR_READONLY_DEFINE(ZFFileBOMList, ZFFileBOMListDefault, _ZFP_ZFFileBOMListDefaultInit())

ZF_NAMESPACE_GLOBAL_END

