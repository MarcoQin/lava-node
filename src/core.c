#include <node_api.h>
#include "assert.h"
#include "stdio.h"
#include "player.h"

napi_value GlobalInit(napi_env env, napi_callback_info info) {
    global_init();
    return NULL;
}

napi_value LoadFile(napi_env env, napi_callback_info info) {
    napi_status status;

    size_t argc = 1;
    napi_value args[1];
    status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
    assert(status == napi_ok);

    if (argc < 1) {
        napi_throw_type_error(env, NULL, "Wrong number of arguments");
        return NULL;
    }

    napi_valuetype arg0;
    status = napi_typeof(env, args[0], &arg0);
    assert(status == napi_ok);

    if (arg0 != napi_string) {
        napi_throw_type_error(env, NULL, "Wrong arguments");
        return NULL;
    }

    size_t transactionIdLength;
    status = napi_get_value_string_utf8(env, args[0], NULL, 0, &transactionIdLength);
    assert(status == napi_ok);
    char* filename = (char*)malloc(transactionIdLength + 1);
    status = napi_get_value_string_utf8(env, args[0], filename, transactionIdLength + 1, &transactionIdLength);
    assert(status == napi_ok);
    const char* filename_new = filename;
    cp_load_file(filename_new);
    return NULL;
}

napi_value Pause(napi_env env, napi_callback_info info) {
    cp_pause_audio();
    return NULL;
}

napi_value Stop(napi_env env, napi_callback_info info) {
    cp_stop_audio();
    return NULL;
}

napi_value SetVolume(napi_env env, napi_callback_info info) {
    napi_status status;

    size_t argc = 1;
    napi_value args[1];
    status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
    assert(status == napi_ok);

    if (argc < 1) {
        napi_throw_type_error(env, NULL, "Wrong number of arguments");
        return NULL;
    }

    napi_valuetype arg0;
    status = napi_typeof(env, args[0], &arg0);
    assert(status == napi_ok);

    if (arg0 != napi_number) {
        napi_throw_type_error(env, NULL, "Wrong arguments");
        return NULL;
    }

    int32_t volume;
    status = napi_get_value_int32(env, args[0], &volume);
    assert(status == napi_ok);
    cp_set_volume(volume);
    return NULL;
}

#define DECLARE_NAPI_METHOD(name, func)                          \
  { name, 0, func, 0, 0, 0, napi_default, 0 }

napi_value Init(napi_env env, napi_value exports) {
  napi_status status;
  napi_property_descriptor addDescriptor = DECLARE_NAPI_METHOD("global_init", GlobalInit);
  status = napi_define_properties(env, exports, 1, &addDescriptor);
  assert(status == napi_ok);

  napi_property_descriptor descriptor1 = DECLARE_NAPI_METHOD("load_file", LoadFile);
  status = napi_define_properties(env, exports, 1, &descriptor1);
  assert(status == napi_ok);

  napi_property_descriptor descriptor2 = DECLARE_NAPI_METHOD("pause", Pause);
  status = napi_define_properties(env, exports, 1, &descriptor2);
  assert(status == napi_ok);

  napi_property_descriptor descriptor3 = DECLARE_NAPI_METHOD("stop", Stop);
  status = napi_define_properties(env, exports, 1, &descriptor3);
  assert(status == napi_ok);

  napi_property_descriptor descriptor4 = DECLARE_NAPI_METHOD("set_volume", SetVolume);
  status = napi_define_properties(env, exports, 1, &descriptor4);
  assert(status == napi_ok);

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
