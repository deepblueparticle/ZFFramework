/* ====================================================================== *
 * Copyright (c) 2010-2018 ZFFramework
 * Github repo: https://github.com/ZFFramework/ZFFramework
 * Home page: http://ZFFramework.com
 * Blog: http://zsaber.com
 * Contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/LICENSE
 * ====================================================================== */
#include "ZFCore_test.h"

ZF_NAMESPACE_GLOBAL_BEGIN

zfclass _ZFP_ZFCore_ZFProperty_test_TestBase : zfextends ZFObject
{
    ZFOBJECT_DECLARE(_ZFP_ZFCore_ZFProperty_test_TestBase, ZFObject)

public:
    // retain
    ZFPROPERTY_RETAIN(ZFObject *, propertyRetain)
    ZFPROPERTY_RETAIN_READONLY(ZFObject *, propertyRetainReadonly, ZFPropertyNoInitValue)

    // assign
    ZFPROPERTY_ASSIGN(zfstring, propertyAssign)
    ZFPROPERTY_ASSIGN_READONLY(zfstring, propertyAssignReadonly, ZFPropertyNoInitValue)

    // weak
    ZFPROPERTY_WEAK(ZFObject *, propertyWeak)

    // custom callback
    ZFPROPERTY_OVERRIDE_ON_INIT_DECLARE(ZFObject *, propertyRetain)
    {
        zfLogT();
    }
    ZFPROPERTY_OVERRIDE_ON_DEALLOC_DECLARE(ZFObject *, propertyRetain)
    {
        zfLogT();
    }
    ZFPROPERTY_OVERRIDE_ON_VERIFY_DECLARE(ZFObject *, propertyRetain)
    {
        zfLogT();
    }
    ZFPROPERTY_OVERRIDE_ON_ATTACH_DECLARE(ZFObject *, propertyRetain)
    {
        zfLogT();
    }
    ZFPROPERTY_OVERRIDE_ON_DETACH_DECLARE(ZFObject *, propertyRetain)
    {
        zfLogT();
    }
    ZFPROPERTY_OVERRIDE_ON_UPDATE_DECLARE(ZFObject *, propertyRetain)
    {
        zfLogT();
    }

    ZFPROPERTY_OVERRIDE_ON_INIT_DECLARE(zfstring, propertyAssign);
    ZFPROPERTY_OVERRIDE_ON_DEALLOC_DECLARE(zfstring, propertyAssign);
    ZFPROPERTY_OVERRIDE_ON_VERIFY_DECLARE(zfstring, propertyAssign);
    ZFPROPERTY_OVERRIDE_ON_ATTACH_DECLARE(zfstring, propertyAssign);
    ZFPROPERTY_OVERRIDE_ON_DETACH_DECLARE(zfstring, propertyAssign);
    ZFPROPERTY_OVERRIDE_ON_UPDATE_DECLARE(zfstring, propertyAssign);
};
ZFPROPERTY_OVERRIDE_ON_INIT_DEFINE(_ZFP_ZFCore_ZFProperty_test_TestBase, zfstring, propertyAssign)
{
    zfLogT();
}
ZFPROPERTY_OVERRIDE_ON_DEALLOC_DEFINE(_ZFP_ZFCore_ZFProperty_test_TestBase, zfstring, propertyAssign)
{
    zfLogT();
}
ZFPROPERTY_OVERRIDE_ON_VERIFY_DEFINE(_ZFP_ZFCore_ZFProperty_test_TestBase, zfstring, propertyAssign)
{
    zfLogT();
}
ZFPROPERTY_OVERRIDE_ON_ATTACH_DEFINE(_ZFP_ZFCore_ZFProperty_test_TestBase, zfstring, propertyAssign)
{
    zfLogT();
}
ZFPROPERTY_OVERRIDE_ON_DETACH_DEFINE(_ZFP_ZFCore_ZFProperty_test_TestBase, zfstring, propertyAssign)
{
    zfLogT();
}
ZFPROPERTY_OVERRIDE_ON_UPDATE_DEFINE(_ZFP_ZFCore_ZFProperty_test_TestBase, zfstring, propertyAssign)
{
    zfLogT();
}

zfclass _ZFP_ZFCore_ZFProperty_test_TestChild: zfextends _ZFP_ZFCore_ZFProperty_test_TestBase
{
    ZFOBJECT_DECLARE(_ZFP_ZFCore_ZFProperty_test_TestChild, _ZFP_ZFCore_ZFProperty_test_TestBase)

public:
    ZFPROPERTY_ASSIGN(zfstring, propertyInChild)
};

// ============================================================
zfclass ZFCore_ZFProperty_test : zfextends ZFFramework_test_TestCase
{
    ZFOBJECT_DECLARE(ZFCore_ZFProperty_test, ZFFramework_test_TestCase)

protected:
    zfoverride
    virtual void testCaseOnStart(void)
    {
        zfsuper::testCaseOnStart();

        this->testCaseOutputSeparator();
        this->testCaseOutput(zfText("ZFProperty"));
        {
            zfblockedAlloc(_ZFP_ZFCore_ZFProperty_test_TestChild, p);

            // property list
            const ZFClass *clsTmp = p->classData();
            zfLogT() << ZFLogAutoEndlOff << zfText("list: ");
            for(zfindex i = 0; i < clsTmp->propertyCount(); ++i)
            {
                if(i > 0)
                {
                    zfLogTrimT() << ZFLogAutoEndlOff << zfText(", ");
                }
                zfLogTrimT() << ZFLogAutoSpaceOff << ZFLogAutoEndlOff
                << clsTmp->propertyAtIndex(i)->propertyName();
            }
            zfLogTrimT();

            // reflect
            p->propertyAssignSet(zfText("oldValue"));
            zfLogT() << zfText("before:") << p->propertyAssign();
            p->classData()->methodForName(zfText("propertyAssignSet"))->execute<void, zfstring const &>(p, zfText("newValue"));
            zfLogT() << zfText("after:") << p->propertyAssign();
            zfLogT() << zfText("access by reflect:") << p->classData()->methodForName(zfText("propertyAssign"))->execute<zfstring const &>(p);

            // retain
            zfLogTrimT();
            zfLogTrimT() << zfText("retain");

            p->propertyRetainSet(zflineAlloc(ZFObject));
            zfLogT() << p->propertyRetain();

#if 0 // this should not compile
            p->propertyRetainReadonlySet(zflineAlloc(ZFObject));
#endif
            zfLogT() << p->propertyRetainReadonly();

            // assign
            zfLogTrimT();
            zfLogTrimT() << zfText("assign");

            p->propertyAssignSet(zfstring());
            zfLogT() << p->propertyAssign();

#if 0 // this should not compile
            p->propertyAssignReadonlySet(zfstring());
#endif
            zfLogT() << p->propertyAssignReadonly();

            // weak
            {
                zfblockedAlloc(ZFObject, value);
                p->propertyWeakSet(value);
                zfLogT() << p->propertyWeak();
            }
            zfLogT() << p->propertyWeak();

            // copy
            this->testCaseOutputSeparator();
            this->testCaseOutput(zfText("copy propertis"));
            zfblockedAlloc(_ZFP_ZFCore_ZFProperty_test_TestBase, pBase);
            zfblockedAlloc(_ZFP_ZFCore_ZFProperty_test_TestChild, pChild);
            pBase->propertyAssignSet(zfText("string set in another"));
            ZFPropertyCopyAll(pChild, pBase);
            this->testCaseOutputSeparator();
            zfLogTrimT() << zfText("after copy:") << pChild->propertyAssign();

            this->testCaseOutputSeparator();
            this->testCaseOutput(zfText("copy by ZFPropertyCopyAll"));
            pChild->propertyAssignSet(zfText(""));
            ZFPropertyCopyAll(pChild, pBase);
            zfLogTrimT() << zfText("after copy:") << pChild->propertyAssign();
        }

        this->testCaseStop();
    }
};
ZFOBJECT_REGISTER(ZFCore_ZFProperty_test)

ZF_NAMESPACE_GLOBAL_END

