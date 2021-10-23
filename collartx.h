// Include MicroPython API.
#include "py/runtime.h"
#include "py/mphal.h"

#define COLLAR_MODE_SHOCK 1
#define COLLAR_MODE_VIBE 2
#define COLLAR_MODE_BEEP 3

extern void collar_tx_bit(mp_hal_pin_obj_t pin, bool is_one);
extern void collar_tx_byte(mp_hal_pin_obj_t pin, uint8_t byte);
extern void collar_tx_buffer(mp_hal_pin_obj_t pin, uint8_t *buf, uint8_t buf_len);

extern mp_obj_t collar_check_values(mp_hal_pin_obj_t pin, int remote_id, int mode, int channel, int power) ;
extern mp_obj_t shock(size_t n_args, const mp_obj_t *args);
extern mp_obj_t vibrate(size_t n_args, const mp_obj_t *args);
extern mp_obj_t beep(size_t n_args, const mp_obj_t *args);