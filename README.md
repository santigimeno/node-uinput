# node-uinput

Linux uinput nodejs wrapper

## Installation

```
npm install uinput
```

## Example

Say hello

```
var uinput = require('uinput');

var setup_options = {
    EV_KEY : [ uinput.KEY_H, uinput.KEY_E, uinput.KEY_L, uinput.KEY_O ]
}

uinput.setup(setup_options, function(err, stream) {
    if (err) {
        throw(err);
    }

    var create_options = {
        name : 'myuinput',
        id : {
            bustype : uinput.BUS_VIRTUAL,
            vendor : 0x1,
            product : 0x1,
            version : 1
        }
    };

    uinput.create(stream, create_options, function(err) {
        if (err) {
            throw(err);
        }

        setTimeout(function() {
            uinput.key_event(stream, uinput.KEY_H, function(err) {
                if (err) {
                    throw(err);
                }

                uinput.key_event(stream, uinput.KEY_E, function(err) {
                    if (err) {
                        throw(err);
                    }

                    uinput.key_event(stream, uinput.KEY_L, function(err) {
                        if (err) {
                            throw(err);
                        }

                        uinput.key_event(stream, uinput.KEY_L, function(err) {
                            if (err) {
                                throw(err);
                            }

                            uinput.key_event(stream, uinput.KEY_O, function(err) {
                                if (err) {
                                    throw(err);
                                }
                            });
                        });
                    });
                });
            });
        }, 1000);
    });
});
```

## API

### uinput.setup(options, callback)

* *options* `Object`
    * *event_type* where event_type can be `EV_KEY`, `EV_ABS`, `EV_REL`, etc. and it's an `Array` with the different events we want the uinput device to handle
* *callback* `Function` called when the setup operation ends
    * *error* `Error`
    * *stream* `WritableStream` to the uinput device.

It configures the uinput device we are about to create.

### uinput.create(stream, options, callback)

* *stream* `WritableStream`
* *options* `Object`. See `uinput_user_dev` definition in linux/uinput.h
    * *name* `String` with the name of the device
    * *id* `Object`
        * *bustype* `Number`
        * *vendor* `Number`
        * *product* `Number`
        * *version* `Number`
    * *ff_effects_max* `Number`
    * *absmax* `Array` of `Numbers` of size: `uinput.ABS_CNT`
    * *absmin* `Array` of `Numbers` of size: `uinput.ABS_CNT`
    * *absfuzz* `Array` of `Numbers` of size: `uinput.ABS_CNT`
    * *absflat* `Array` of `Numbers` of size: `uinput.ABS_CNT`
* *callback* `Function` called when the creation operation ends
    * *error* `Error`

It creates the uinput device.

### send_event(stream, type, code, value, callback)

* *stream* `WritableStream`
* *type* `Number`
* *code* `Number`
* *value* `Number`
* *callback* `Function`

It sends an event to the uinput device.

### key_event(stream, code, callback)

* *stream* `WritableStream`
* *code* `Number`
* *callback* `Function`

Wrapper over send_event to simulate key presses and mouse clicks.