var fs = require('fs');
var bindings = require('bindings')('uinput');
var ioctl = require('ioctl');
var ref = require('ref');
var ArrayType = require('ref-array');
var StructType = require('ref-struct');
require('array.prototype.fill');

// struct input_id {
//     __u16 bustype;
//     __u16 vendor;
//     __u16 product;
//     __u16 version;
// };

var InputId = StructType({
    bustype : ref.types.uint16,
    vendor : ref.types.uint16,
    product : ref.types.uint16,
    version : ref.types.uint16,
});

// struct uinput_user_dev {
//     char name[UINPUT_MAX_NAME_SIZE];
//     struct input_id id;
//     int ff_effects_max;
//     int absmax[ABS_CNT];
//     int absmin[ABS_CNT];
//     int absfuzz[ABS_CNT];
//     int absflat[ABS_CNT];
// };

var DeviceName = ArrayType(ref.types.char, bindings.UINPUT_MAX_NAME_SIZE);
var AbsArray = ArrayType(ref.types.int, bindings.ABS_CNT);
var UInputUserDev = StructType({
    name : DeviceName,
    id : InputId,
    ff_effects_max : ref.types.int,
    absmax : AbsArray,
    absmin : AbsArray,
    absfuzz : AbsArray,
    absflat : AbsArray
});

var ioctls = [
    undefined,
    bindings.UI_SET_KEYBIT,
    bindings.UI_SET_RELBIT,
    bindings.UI_SET_ABSBIT,
    bindings.UI_SET_MSCBIT,
    bindings.UI_SET_LEDBIT,
    bindings.UI_SET_SNDBIT,
    bindings.UI_SET_FFBIT,
    bindings.UI_SET_PHYS,
    bindings.UI_SET_SWBIT,
    bindings.UI_SET_PROPBIT
];


function setup(options, cb) {
    var stream = fs.createWriteStream('/dev/uinput');
    stream.once('error', cb);
    stream.on('open', function(fd) {
        var events = Object.keys(options);
        for (var i = 0; i < events.length; ++ i) {
            var ev = events[i];
            if (ioctl(fd, bindings.UI_SET_EVBIT, bindings[ev])) {
                return cb(new Error("Could not listen for event: " + ev));
            }

            for (var j = 0; j < (options[ev]).length; ++ j) {
                var val = options[ev][j];
                if (ioctl(fd, ioctls[bindings[ev]], val)) {
                    return cb(new Error("Could not setup: " + val));
                }
            }
        }

        stream.removeAllListeners('error');
        cb(undefined, stream);
    });
}

function create(stream, options, cb) {

    if (!options.id) {
        return cb(new Error('Device id params is mandatory'));
    }

    var zero_array = new Array(bindings.ABS_CNT).fill(0);
    var user_dev = new UInputUserDev({
        id : options.id,
        ff_effects_max : options.ff_effects_max || 0,
        absmax : options.absmax ? new AbsArray(options.absmax) : new AbsArray(zero_array),
        absmin : options.absmin ? new AbsArray(options.absmin) : new AbsArray(zero_array),
        absfuzz : options.absfuzz ? new AbsArray(options.absfuzz) : new AbsArray(zero_array),
        absflat : options.absflat ? new AbsArray(options.absflat) : new AbsArray(zero_array)
    });

    var name = new Buffer(new Array(80));
    name.write(options.name);
    user_dev.name = new DeviceName(name);

    stream.once('error', cb);
    stream.write(user_dev.ref(), function(err) {
        if (err) {
            return cb(err);
        }

        stream.removeAllListeners('error');
        if (ioctl(stream.fd, bindings.UI_DEV_CREATE)) {
            cb(new Error('Could not create uinput device'));
        } else {
            cb();
        }
    });
}

var input_event = bindings.input_event;

function send_event(stream, type, code, value, cb) {
    var ev = input_event(type, code, value);
    stream.once('error', cb);
    stream.write(ev, function(err) {
        if (err) {
            return cb(err);
        }

        ev = input_event(bindings.EV_SYN, bindings.SYN_REPORT, 0);
        stream.write(ev, cb);
    });
}

function key_event(stream, code, cb) {
    /* press / click */
    send_event(stream, bindings.EV_KEY, code, 1, function(err) {
        if (err) {
            return cb(err);
        }

        /* release / unclick */
        send_event(stream, bindings.EV_KEY, code, 0, cb);
    });
}

module.exports = bindings;
delete module.exports.input_event;
module.exports.setup = setup;
module.exports.create = create;
module.exports.send_event = send_event;
module.exports.key_event = key_event;

