extern "C" {
#include <collartx.h>
#include <cstring>


void collar_tx_bit(mp_hal_pin_obj_t pin, bool is_one){
    mp_hal_pin_od_high(pin);
    mp_hal_delay_us(is_one ? 830 : 360);
    mp_hal_pin_od_low(pin);
    mp_hal_delay_us(is_one ? 200 : 670);
}

void collar_tx_byte(mp_hal_pin_obj_t pin, uint8_t byte){
    for (int i = 7; i >= 0 ; i--) collar_tx_bit(pin, byte & (1 << i));
}

void collar_tx_buffer(mp_hal_pin_obj_t pin, uint8_t *buf, uint8_t buf_len){
    //Send start bit
    mp_hal_pin_od_high(pin);
    mp_hal_delay_us(1550);
    mp_hal_pin_od_low(pin);
    mp_hal_delay_us(660);

    //Send buffer
    uint8_t checksum = 0;
    for (size_t n = 0; n < buf_len; n++) {
        checksum += buf[n];
        collar_tx_byte(pin, buf[n]);
    }
    collar_tx_byte(pin, checksum);

    //Stop bit
    collar_tx_bit(pin, 0);
}

void collar_tx(mp_hal_pin_obj_t pin, uint16_t remote_id, uint8_t mode, uint8_t channel, uint8_t power) {
    uint8_t txbuf[4];

    //Put the remote id in the buffer
    memcpy(txbuf, &remote_id, 2);

    //Put the channel and mode in the buffer
    txbuf[2] = ((channel << 4) | mode);

    //Put power in the buffer
    if(power > 99){
        txbuf[3] = 99;
    } else {
        txbuf[3] = power;
    }

    collar_tx_buffer(pin, txbuf, sizeof(txbuf));
    collar_tx_buffer(pin, txbuf, sizeof(txbuf));
    collar_tx_buffer(pin, txbuf, sizeof(txbuf));
}

mp_obj_t collar_check_values(mp_hal_pin_obj_t pin, int remote_id, int mode, int channel, int power) {
    if(channel < 0 || channel > 2) {
        mp_raise_ValueError("Channel must be either 0,1 or 2");
        return mp_const_none;
    }
    if(mode < 1 || mode> 3) {
        mp_raise_ValueError("Mode must be either 1(SHOCK), 2(VIBE), 3(BEEP)");
        return mp_const_none;
    }
    if(power < 0 || power > 99) {
        mp_raise_ValueError("Power must be contained between 0 and 99");
        return mp_const_none;
    }
    if(remote_id > 0xFFFF) {
        mp_raise_ValueError("Remote id is too big, must be contained between 0x0000 and 0xFFFF");
        return mp_const_none;
    }

    collar_tx(pin, (uint16_t)remote_id, (uint8_t)mode, (uint8_t)channel, (uint8_t)power);
    return mp_const_none;
}

//mp_obj_t vibrate(mp_obj_t pin_out, mp_obj_t remote_id, mp_obj_t channel, mp_obj_t level)
mp_obj_t shock(size_t n_args, const mp_obj_t *args) {
    return collar_check_values(
        mp_hal_get_pin_obj(args[0]),
        mp_obj_get_int(args[1]), //Remote id
        COLLAR_MODE_SHOCK,
        mp_obj_get_int(args[2]), //Channel
        mp_obj_get_int(args[3])  // Level
    );
}
mp_obj_t vibrate(size_t n_args, const mp_obj_t *args) {
    return collar_check_values(
        mp_hal_get_pin_obj(args[0]),
        mp_obj_get_int(args[1]), //Remote id
        COLLAR_MODE_VIBE,
        mp_obj_get_int(args[2]), //Channel
        mp_obj_get_int(args[3])  // Level
    );
}
mp_obj_t beep(size_t n_args, const mp_obj_t *args) {
    return collar_check_values(
        mp_hal_get_pin_obj(args[0]),
        mp_obj_get_int(args[1]), //Remote id
        COLLAR_MODE_BEEP,
        mp_obj_get_int(args[2]), //Channel
        1
    );
}
}
