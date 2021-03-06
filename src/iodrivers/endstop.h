/* The MIT License (MIT)
 *
 * Copyright (c) 2014 Colin Wallace
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef IODRIVERS_ENDSTOP_H
#define IODRIVERS_ENDSTOP_H

#include <utility> //for std::move
#include "iodriver.h"
#include "iopin.h"
#include "common/logging.h"

namespace iodrv {

/* 
 * Endstops are queriable switches placed at the axis limits.
 * They typically represent a "known" point to which the device can be homed upon initiailization,
 *   or a point beyond which the device should not be pushed.
 */
class Endstop : public IODriver {
    IoPin pin;
    public:
        inline Endstop() : pin(IoPin::null()) {}
        inline Endstop(IoPin &&pin) : IODriver(), pin(std::move(pin)) {
            this->pin.setDefaultState(IO_DEFAULT_HIGH_IMPEDANCE);
            this->pin.makeDigitalInput();
        }
        inline bool isEndstop() const { 
            return true;
        }
        inline bool isNull() const {
            return pin.isNull();
        }
        inline bool isEndstopTriggered() const {
            //if the endstop is NULL, then always return triggered.
            bool t = isNull() ? true : pin.digitalRead();
            LOGV("LeverEndstop is %i\n", t);
            return t;
        }
};

}
#endif
