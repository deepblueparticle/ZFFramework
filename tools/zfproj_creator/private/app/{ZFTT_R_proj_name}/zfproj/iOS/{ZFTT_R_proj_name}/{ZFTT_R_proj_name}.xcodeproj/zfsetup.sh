WORK_DIR=$(cd "$(dirname "$0")"; pwd)
iOS_SRCROOT=$1
iOS_CONFIGURATION_BUILD_DIR=$2
iOS_CONTENTS_FOLDER_PATH=$3
if test "x-$iOS_SRCROOT" = "x-" || test "x-$iOS_CONFIGURATION_BUILD_DIR" = "x-" || test "x-$iOS_CONFIGURATION_BUILD_DIR" = "x-" ; then
    echo "usage:"
    echo "  zfsetup.sh SRCROOT CONFIGURATION_BUILD_DIR CONTENTS_FOLDER_PATH"
    exit 1
fi

ZF_ROOT_PATH=${iOS_SRCROOT}/../../../../../ZFFramework
ZF_TOOLS_PATH=$ZF_ROOT_PATH/tools

COMPILE_DST_PATH=${iOS_SRCROOT}/ProjectFiles
sh $ZF_TOOLS_PATH/common/unity_build.sh "${COMPILE_DST_PATH}/zfgensrc_{ZFTT_R_proj_name}.mm" "${iOS_SRCROOT}/../../../zfsrc"

RES_DST_PATH=${iOS_CONFIGURATION_BUILD_DIR}/${iOS_CONTENTS_FOLDER_PATH}/zfres
{ZFTT_C_lib_require_0}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_0}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_1}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_1}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_2}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_2}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_3}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_3}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_4}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_4}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_5}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_5}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_6}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_6}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_7}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_7}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_8}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_8}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_9}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_9}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_10}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_10}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_11}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_11}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_12}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_12}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_13}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_13}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_14}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_14}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_15}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_15}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_16}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_16}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_17}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_17}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_18}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_18}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_19}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_19}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_20}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_20}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_21}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_21}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_22}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_22}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_23}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_23}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_24}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_24}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_25}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_25}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_26}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_26}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_27}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_27}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_28}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_28}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_29}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_29}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_30}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_30}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_lib_require_31}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_lib_name_31}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_0}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_0}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_1}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_1}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_2}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_2}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_3}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_3}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_4}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_4}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_5}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_5}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_6}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_6}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_7}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_7}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_8}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_8}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_9}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_9}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_10}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_10}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_11}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_11}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_12}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_12}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_13}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_13}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_14}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_14}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_15}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_15}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_16}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_16}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_17}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_17}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_18}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_18}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_19}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_19}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_20}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_20}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_21}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_21}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_22}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_22}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_23}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_23}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_24}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_24}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_25}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_25}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_26}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_26}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_27}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_27}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_28}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_28}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_29}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_29}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_30}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_30}/zfres" "$RES_DST_PATH"
{ZFTT_CE}{ZFTT_C_impl_require_31}sh "$ZF_TOOLS_PATH/util/copy_res.sh" "$ZF_ROOT_PATH/_release/iOS/module/{ZFTT_R_impl_name_31}/zfres" "$RES_DST_PATH"
{ZFTT_CE}
sh "$ZF_TOOLS_PATH/util/copy_res.sh" "${iOS_SRCROOT}/../../../zfres" "$RES_DST_PATH"

