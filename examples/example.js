var uinput = require('../index');
require('array.prototype.fill');

var setup_options = {
    EV_KEY : [ uinput.BTN_LEFT, uinput.KEY_H, uinput.KEY_E, uinput.KEY_L, uinput.KEY_O,
               uinput.KEY_CAPSLOCK, uinput.KEY_B, uinput.KEY_Y, uinput.KEY_SPACE ],
    EV_REL : [ uinput.REL_WHEEL, uinput.REL_HWHEEL ],
    EV_ABS : [ uinput.ABS_X, uinput.ABS_Y ]
};

uinput.setup(setup_options, function(err, stream) {
    if (err) {
        throw(err);
    }

    var absmax = new Array(uinput.ABS_CNT).fill(0);
    absmax[uinput.ABS_X] = 1024;
    absmax[uinput.ABS_Y] = 1024;

    var create_options = {
        name : 'myuinput',
        id : {
            bustype : uinput.BUS_VIRTUAL,
            vendor : 0x1,
            product : 0x1,
            version : 1
        },
        absmax : absmax
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
        }, 2000);

        setTimeout(function() {
            var keys = [ uinput.KEY_SPACE, uinput.KEY_CAPSLOCK, uinput.KEY_B, uinput.KEY_Y, uinput.KEY_E ];
            uinput.emit_combo(stream, keys, function(err) {
                if (err) throw(err);
            });
        }, 3000);
    });
});
