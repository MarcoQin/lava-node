#include <node_api.h>
#include "assert.h"
#include "stdio.h"
#include "player.h"

napi_value GlobalInit(napi_env env, napi_callback_info info)
{
    global_init();
    return NULL;
}

napi_value LoadFile(napi_env env, napi_callback_info info)
{
    napi_status status;

    size_t argc = 1;
    napi_value args[1];
    status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
    assert(status == napi_ok);

    if (argc < 1)
    {
        napi_throw_type_error(env, NULL, "Wrong number of arguments");
        return NULL;
    }

    napi_valuetype arg0;
    status = napi_typeof(env, args[0], &arg0);
    assert(status == napi_ok);

    if (arg0 != napi_string)
    {
        napi_throw_type_error(env, NULL, "Wrong arguments");
        return NULL;
    }

    size_t transactionIdLength;
    status = napi_get_value_string_utf8(env, args[0], NULL, 0, &transactionIdLength);
    assert(status == napi_ok);
    char *filename = (char *)malloc(transactionIdLength + 1);
    status = napi_get_value_string_utf8(env, args[0], filename, transactionIdLength + 1, &transactionIdLength);
    assert(status == napi_ok);
    const char *filename_new = filename;
    cp_load_file(filename_new);
    return NULL;
}

napi_value Pause(napi_env env, napi_callback_info info)
{
    cp_pause_audio();
    return NULL;
}

napi_value Stop(napi_env env, napi_callback_info info)
{
    cp_stop_audio();
    return NULL;
}

napi_value SetVolume(napi_env env, napi_callback_info info)
{
    napi_status status;

    size_t argc = 1;
    napi_value args[1];
    status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
    assert(status == napi_ok);

    if (argc < 1)
    {
        napi_throw_type_error(env, NULL, "Wrong number of arguments");
        return NULL;
    }

    napi_valuetype arg0;
    status = napi_typeof(env, args[0], &arg0);
    assert(status == napi_ok);

    if (arg0 != napi_number)
    {
        napi_throw_type_error(env, NULL, "Wrong arguments");
        return NULL;
    }

    int32_t volume;
    status = napi_get_value_int32(env, args[0], &volume);
    assert(status == napi_ok);
    cp_set_volume(volume);
    return NULL;
}

napi_value SeekByPercent(napi_env env, napi_callback_info info)
{
    napi_status status;

    size_t argc = 1;
    napi_value args[1];
    status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
    assert(status == napi_ok);

    if (argc < 1)
    {
        napi_throw_type_error(env, NULL, "Wrong number of arguments");
        return NULL;
    }

    napi_valuetype arg0;
    status = napi_typeof(env, args[0], &arg0);
    assert(status == napi_ok);

    if (arg0 != napi_number)
    {
        napi_throw_type_error(env, NULL, "Wrong arguments");
        return NULL;
    }

    double percent;
    status = napi_get_value_double(env, args[0], &percent);
    assert(status == napi_ok);
    cp_seek_audio(percent);
    return NULL;
}

napi_value SeekBySec(napi_env env, napi_callback_info info)
{
    napi_status status;

    size_t argc = 1;
    napi_value args[1];
    status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
    assert(status == napi_ok);

    if (argc < 1)
    {
        napi_throw_type_error(env, NULL, "Wrong number of arguments");
        return NULL;
    }

    napi_valuetype arg0;
    status = napi_typeof(env, args[0], &arg0);
    assert(status == napi_ok);

    if (arg0 != napi_number)
    {
        napi_throw_type_error(env, NULL, "Wrong arguments");
        return NULL;
    }

    int32_t sec;
    status = napi_get_value_int32(env, args[0], &sec);
    assert(status == napi_ok);
    cp_seek_audio_by_sec(sec);
    return NULL;
}

napi_value GetTimeLength(napi_env env, napi_callback_info info)
{
    napi_status status;

    int total_length = cp_get_time_length();
    napi_value result;
    status = napi_create_int32(env, total_length, &result);
    assert(status == napi_ok);

    return result;
}

napi_value GetCurrentTimePos(napi_env env, napi_callback_info info)
{
    napi_status status;

    double current_time_pos = cp_get_current_time_pos();
    napi_value result;
    status = napi_create_double(env, current_time_pos, &result);
    assert(status == napi_ok);

    return result;
}

napi_value IsStopping(napi_env env, napi_callback_info info)
{
    napi_status status;

    int is_stopping = cp_is_stopping();
    napi_value result;
    status = napi_create_int32(env, is_stopping, &result);
    assert(status == napi_ok);

    return result;
}

void export_function(napi_env env, napi_value *exports, napi_callback func, const char *fn_name)
{
    napi_value exported_function;
    assert(napi_create_function(env,
                                fn_name,
                                NAPI_AUTO_LENGTH,
                                func,
                                NULL,
                                &exported_function) == napi_ok);
    assert(napi_set_named_property(env,
                                   *exports,
                                   fn_name,
                                   exported_function) == napi_ok);
}

napi_value Init(napi_env env, napi_value exports)
{
    export_function(env, &exports, &GlobalInit, "global_init");
    export_function(env, &exports, &LoadFile, "load_file");
    export_function(env, &exports, &Pause, "pause");
    export_function(env, &exports, &Stop, "stop");
    export_function(env, &exports, &SetVolume, "set_volume");
    export_function(env, &exports, &IsStopping, "is_stopping");
    export_function(env, &exports, &SeekByPercent, "seek_by_percent");
    export_function(env, &exports, &SeekBySec, "seek_by_sec");
    export_function(env, &exports, &GetTimeLength, "get_time_length");
    export_function(env, &exports, &GetCurrentTimePos, "get_current_time_pos");
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
