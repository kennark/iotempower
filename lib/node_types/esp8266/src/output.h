// output.h
// Header File for output device (simple gpio on/off, led, relay)

#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include <device.h>

class Output : public Device {
    private:
        const char* _high;
        const char* _low;
        int _pin;
    public:
        Output(const char* name, const int pin, 
                const char* high_command="on",
                const char* low_command="off" );
        void start();
        Output& high() { 
            if(started()) digitalWrite(_pin, 1);
            measured_value().from(_high);
            return *this;
        }
        Output& on() { return high(); }
        Output& low() { 
            if(started()) digitalWrite(_pin, 0); 
            measured_value().from(_low);
            return *this;
        }
        Output& off() { return low(); }

        bool is_high() {
            return value().equals(_high);
        }
        bool is_low() {
            return value().equals(_low);
        }
        Output& set(const char* value) {
            Ustring v(value);
            if(v.equals(_high)) high();
            else {
                if(v.equals(_low)) low();
            }
            return *this;
        }
        void toggle() {
            if(measured_value().equals(_high)) set(_low);
            else set(_high);
        }

        // TODO: set output "floating"?
};


#endif // _OUTPUT_H_