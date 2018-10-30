const fs = require('fs');
const bindings = require('bindings')('uinput');
const ioctl = require('ioctl');

const InputEvent = bindings.input_event;
const Events = bindings.events;

// Throughout this file there's an assumption that the host machine is little endian.

// struct input_id {
//     __u16 bustype;
//     __u16 vendor;
//     __u16 product;
//     __u16 version;
// };

function InputId(options) {
    const buffer = Buffer.alloc(4 * 2);
    buffer.writeUInt16LE(options.busType, 0);
    buffer.writeUInt16LE(options.vendor, 2);
    buffer.writeUInt16LE(options.product, 4);
    buffer.writeUInt16LE(options.version, 6);
    return buffer;
};

function DeviceName(name) {
    const buf = Buffer.alloc(Events.UINPUT_MAX_NAME_SIZE).fill(0);
    if (name) {
        buf.write(name, 0);
    }
    return buf;
}

function AbsArray(abs) {
    const buf = Buffer.alloc(Events.ABS_CNT * 4).fill(0);
    if (abs) {
        for (let i = 0; i < abs.length; i++) {
            buf.writeUInt32LE(abs[i].value, abs[i].offset * 4);
        }
    }
    return buf;
}

const Abs = (offset, value) => {
    return {
        offset: offset,
        value: value
    };
};

function UInputUserDev(options) {
    const name = DeviceName(options.name);
    const id = InputId(options.id);

    const ffEffectsMax = Buffer.alloc(4);
    ffEffectsMax.writeUInt32LE(options.ffEffectsMax || 0, 0);

    const absMax = AbsArray(options.absMax);
    const absMin = AbsArray(options.absMin);
    const absFuzz = AbsArray(options.absFuzz);
    const absFlat = AbsArray(options.absFlat);

    return Buffer.concat([
        name,
        id,
        ffEffectsMax,
        absMax,
        absMin,
        absFuzz,
        absFlat
    ]);
}

const ioctls = [
    Events.UI_SET_KEYBIT,
    Events.UI_SET_RELBIT,
    Events.UI_SET_ABSBIT,
    Events.UI_SET_MSCBIT,
    Events.UI_SET_LEDBIT,
    Events.UI_SET_SNDBIT,
    Events.UI_SET_FFBIT,
    Events.UI_SET_PHYS,
    Events.UI_SET_SWBIT,
    Events.UI_SET_PROPBIT
];

class UInput {
    constructor(stream) {
        this.stream = stream;
    }

    async write(data) {
        return new Promise((resolve, reject) => {
            this.stream.once('error', reject);
            this.stream.write(data, (err) => {
                this.stream.removeAllListeners('error');
                if (err) {
                    return reject(err);
                }
                resolve();
            });
        });
    }

    async create(options) {
        if (!options.id) {
            throw new Error('Device id params is mandatory');
        }

        const userDev = UInputUserDev(options);

        return new Promise((resolve, reject) => {
            this.stream.once('error', reject);
            this.stream.write(userDev, (err) => {
                if (ioctl(this.stream.fd, Events.UI_DEV_CREATE)) {
                    throw new Error('Could not create uinput device');
                }

                this.stream.removeAllListeners('error');
                resolve();
            });
        });
    }

    async sendEvent(type, code, value) {
        await this.write(InputEvent(type, code, value));
        await this.write(InputEvent(Events.EV_SYN, Events.SYN_REPORT, 0));
    }

    async keyEvent(code) {
        /* press / click */
        await this.sendEvent(Events.EV_KEY, code, 1);
        await this.sendEvent(Events.EV_KEY, code, 0);
    }

    async emitCombo(code) {
        // Press each of the keys in series
        for (let i = 0; i < code.length; i++) {
            await this.sendEvent(Events.EV_KEY, code[i], 1);
        }
        // Release them in reverse
        for (let i = code.length; i-- > 0;) {
            await this.sendEvent(Events.EV_KEY, code[i], 0);
        }
    }
};

async function setup(options) {
    return new Promise((resolve, reject) => {
        const stream = fs.createWriteStream('/dev/uinput');
        const uinput = new UInput(stream);
        stream.once('error', reject);
        stream.on('open', (fd) => {
            const events = Object.keys(options);
            for (let i = 0; i < events.length; i++) {
                const ev = events[i];
                if (ioctl(fd, Events.UI_SET_EVBIT, Events[ev])) {
                    throw new Error("Could not listen for event: " + ev);
                }
                for (let j = 0; j < (options[ev]).length; j++) {
                    const val = options[ev][j];
                    if (ioctl(fd, ioctls[Events[ev] - 1], val)) {
                        throw new Error("Could not setup: " + val);
                    }
                }
            }
            stream.removeAllListeners('error');
            resolve(uinput);
        });
    });
}

module.exports = Events;
module.exports.Abs = Abs;
module.exports.setup = setup;
