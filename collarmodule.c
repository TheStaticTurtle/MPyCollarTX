#include <collartx.h>

// Define a Python reference to the function we'll make available.
// See example.cpp for the definition.
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(shock_obj, 4, 4, shock);
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(vibrate_obj, 4, 4, vibrate);
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(beep_obj, 3, 3, beep);

// Define all properties of the module.
// Table entries are key/value pairs of the attribute name (a string)
// and the MicroPython object reference.
// All identifiers and strings are written as MP_QSTR_xxx and will be
// optimized to word-sized integers by the build system (interned strings).
STATIC const mp_rom_map_elem_t collartx_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_collartx) },
    { MP_ROM_QSTR(MP_QSTR_shock), MP_ROM_PTR(&shock_obj) },
    { MP_ROM_QSTR(MP_QSTR_vibrate), MP_ROM_PTR(&vibrate_obj) },
    { MP_ROM_QSTR(MP_QSTR_beep), MP_ROM_PTR(&beep_obj) },

    { MP_ROM_QSTR(MP_QSTR_CHANNEL_1), MP_ROM_INT(0) },
    { MP_ROM_QSTR(MP_QSTR_CHANNEL_2), MP_ROM_INT(1) },
    { MP_ROM_QSTR(MP_QSTR_CHANNEL_3), MP_ROM_INT(2) },
};
STATIC MP_DEFINE_CONST_DICT(collartx_module_globals, collartx_module_globals_table);

// Define module object.
const mp_obj_module_t collartx_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&collartx_module_globals,
};

// Register the module to make it available in Python.
// Note: the "1" in the third argument means this module is always enabled.
// This "1" can be optionally replaced with a macro like MODULE_collartx_ENABLED
// which can then be used to conditionally enable this module.
MP_REGISTER_MODULE(MP_QSTR_collartx, collartx_user_cmodule, 1);
