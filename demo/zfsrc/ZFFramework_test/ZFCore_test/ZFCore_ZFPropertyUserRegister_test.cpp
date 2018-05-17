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

#include "ZFAlgorithm/ZFXmlSerializableConverter.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
zfclass _ZFP_ZFCore_ZFPropertyUserRegister_test_Object : zfextends ZFObject, zfimplements ZFSerializable
{
    ZFOBJECT_DECLARE(_ZFP_ZFCore_ZFPropertyUserRegister_test_Object, ZFObject)
    ZFIMPLEMENTS_DECLARE(ZFSerializable)
public:
    ZFPROPERTY_ASSIGN(zfindex, valueNormal)
};
zfclass ZFCore_ZFPropertyUserRegister_test : zfextends ZFFramework_test_TestCase
{
    ZFOBJECT_DECLARE(ZFCore_ZFPropertyUserRegister_test, ZFFramework_test_TestCase)

protected:
    zfoverride
    virtual void testCaseOnStart(void)
    {
        zfsuper::testCaseOnStart();

        {
            zfblockedAlloc(_ZFP_ZFCore_ZFPropertyUserRegister_test_Object, obj);
            obj->valueNormalSet(1);

            this->testCaseOutputSeparator();
            this->testCaseOutput(zfText("try modify and serialize a dynamically registered property, result"));

            ZFPropertyUserRegisterAssign(propertyInfo, _ZFP_ZFCore_ZFPropertyUserRegister_test_Object::ClassData(),
                zfstring, zfText("valueDynamic"), ZFPropertyNoInitValue,
                public, public);
            obj->classData()->propertyForName(zfText("valueDynamic"))->setterMethod()
                ->execute<void, zfstring const &>(obj, zfText("value"));
            ZFObjectToXml(ZFOutputDefault(), obj);
            ZFPropertyUserUnregister(obj->classData()->propertyForName(zfText("valueDynamic")));

            this->testCaseOutput(zfText("after unregister:"));
            ZFObjectToXml(ZFOutputDefault(), obj);
        }

        {
            zfblockedAlloc(_ZFP_ZFCore_ZFPropertyUserRegister_test_Object, obj);
            obj->valueNormalSet(1);

            this->testCaseOutputSeparator();
            this->testCaseOutput(zfText("try modify and serialize a statically registered property, result"));

            obj->classData()->propertyForName(zfText("valueStatic"))->setterMethod()
                ->execute<void, ZFString * const &>(obj, zflineAlloc(ZFString, zfText("value")));
            ZFObjectToXml(ZFOutputDefault(), obj);
        }

        this->testCaseStop();
    }
};
ZFOBJECT_REGISTER(ZFCore_ZFPropertyUserRegister_test)

ZFPROPERTY_USER_REGISTER_RETAIN(_ZFP_ZFCore_ZFPropertyUserRegister_test_Object,
    ZFString *, valueStatic, ZFPropertyNoInitValue,
    public, public)

ZF_NAMESPACE_GLOBAL_END

