#include "15_ATM.h"

void atm::getting_pin() {
    incoming
    .wait()
    .handle<digit_pressed>([&](const digit_pressed& msg) {
        unsigned const pin_length = 4;
        pin += msg.digit;
        if (pin.length()  == pin_length) {
            bank.send(verify_pin(account, pin, incoming));
            state = &atm::verifying_pin;
        }
    })
    .handle<clear_last_pressed>([&](const clear_last_pressed& msg) {
        if (!pin.empty()) {
            pin.resize(pin.length() - 1);
        }
    })
    .handle<cancel_pressed>([&](const cancel_pressed& msg) {
        state = &atm::done_processing;
    });
}
