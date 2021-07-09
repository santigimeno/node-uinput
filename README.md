# node-uinput

Linux uinput nodejs wrapper

## Installation

```
npm install uinput
```

## Example

```
const UInput = require('uinput2');

const SETUP_OPTIONS = {
    UI_SET_EVBIT:  [
        UInput.EV_KEY,
        UInput.EV_SYN,
        UInput.EV_REL,
    ],
    UI_SET_RELBIT: [
        UInput.REL_X,
        UInput.REL_Y,
        UInput.REL_WHEEL,
        UInput.REL_HWHEEL,
    ],
    UI_SET_KEYBIT: [
        UInput.BTN_LEFT,
        UInput.BTN_RIGHT,
        UInput.BTN_MIDDLE,
        UInput.BTN_SIDE,
        UInput.BTN_EXTRA,
    ],
};

const CREATE_OPTIONS = {
    name: 'Wine Launcher Mouse Emulation',
    id:   {
        busType: UInput.BUS_USB,
        vendor:  0x0,
        product: 0x0,
        version: 1
    },
};

export default class UInputMouse {
    static map = {
        left:   UInput.BTN_LEFT,
        right:  UInput.BTN_RIGHT,
        middle: UInput.BTN_MIDDLE,
    };
    runtime = Promise.resolve();
    delay = 2;
    device;

    async createDevice() {
        if (undefined !== this.device) {
            return this.device;
        }

        this.device = await UInput.setup(SETUP_OPTIONS);
        this.device.create(CREATE_OPTIONS);

        return this.device;
    }

    async sleep(time) {
        return new Promise((resolve) => setTimeout(resolve, time));
    }

    /**
     * @param {number} x
     * @param {number} y
     */
    moveMouse(x, y) {
        this.createDevice().then(device => {
            this.runtime = this.runtime
                .then(() => device.sendEvent(UInput.EV_REL, UInput.REL_X, x, false))
                .then(() => device.sendEvent(UInput.EV_REL, UInput.REL_Y, y, true))
                .then(() => this.sleep(this.delay));
        });
    }


    /**
     * @param {string} key [left, right, middle]
     * @param {boolean} pressed
     */
    keyToggle(key, pressed) {
        if (undefined === UInputMouse.map[key]) {
            return;
        }

        this.createDevice().then(device => {
            this.runtime = this.runtime
                .then(() => device.keyEvent(UInputMouse.map[key], pressed))
                .then(() => this.sleep(this.delay));
        });
    }
}

const device = new UInputMouse();

device.moveMouse(0, 100);
device.keyToggle('right', true);
device.keyToggle('right', false);
```

## API

### async UInput.setup(options)

* *options* `Object`
    * *event_type* where event_type can be `EV_KEY`, `EV_ABS`, `EV_REL`, etc. and it's an `Array` with the different events we want the uinput device to handle
* Returns a UInputClass on success

It configures the uinput device we are about to create.

### async UInputClass.create(options)

* *options* `Object`. See `uinput_user_dev` definition in linux/uinput.h
    * *name* `String` with the name of the device
    * *id* `Object`
        * *busType* `Number`
        * *vendor* `Number`
        * *product* `Number`
        * *version* `Number`
    * *ffEffectsMax* `Number`
    * *absMax* `Array` of `Numbers` of size: `UInput.ABS_CNT`
    * *absMin* `Array` of `Numbers` of size: `UInput.ABS_CNT`
    * *absFuzz* `Array` of `Numbers` of size: `UInput.ABS_CNT`
    * *absFlat* `Array` of `Numbers` of size: `UInput.ABS_CNT`

It creates the uinput device.

### async UInputClass.sendEvent(type, code, value, syn)

* *type* `Number`
* *code* `Number`
* *value* `Number`
* *syn* `Boolean`

It sends an event to the uinput device.

### async UInputClass.keyEvent(code, press)

* *code* `Number`
* *press* `Boolean`

Wrapper over send_event to simulate key presses and mouse clicks.

### async UInputClass.emitCombo(code)

* *code* `Array with any combination of keys`

It sends an event to the uinput device with the combination
keys generated.
