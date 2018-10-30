# node-uinput

Linux uinput nodejs wrapper

## Installation

```
npm install uinput
```

## Example

Say hello BYE

```
const UInput = require('../index');

const SETUP_OPTIONS = {
    EV_KEY : [ UInput.BTN_LEFT, UInput.KEY_H, UInput.KEY_E, UInput.KEY_L, UInput.KEY_O,
               UInput.KEY_CAPSLOCK, UInput.KEY_B, UInput.KEY_Y, UInput.KEY_SPACE ],
    EV_REL : [ UInput.REL_WHEEL, UInput.REL_HWHEEL ],
    EV_ABS : [ UInput.ABS_X, UInput.ABS_Y ]
};

const CREATE_OPTIONS = {
    name: 'myuinput',
    id: {
        busType: UInput.BUS_VIRTUAL,
        vendor: 0x1,
        product: 0x1,
        version: 1
    },
    absMax: [
        UInput.Abs(UInput.ABS_X, 1024),
        UInput.Abs(UInput.ABS_Y, 1024)
    ]
};

async function sleep(time) {
    return new Promise((resolve) => setTimeout(resolve, time));
}

async function main() {
    console.log('Setting up input');
    const uinput = await UInput.setup(SETUP_OPTIONS);

    await uinput.create(CREATE_OPTIONS);

    console.log('Sleeping');
    await sleep(2000);
    console.log('Sending HELLO');
    await uinput.keyEvent(UInput.KEY_H);
    await uinput.keyEvent(UInput.KEY_E);
    await uinput.keyEvent(UInput.KEY_L);
    await uinput.keyEvent(UInput.KEY_L);
    await uinput.keyEvent(UInput.KEY_O);

    console.log('Sleeping');
    await sleep(3000);
    const keys = [ UInput.KEY_SPACE, UInput.KEY_CAPSLOCK, UInput.KEY_B, UInput.KEY_Y, UInput.KEY_E ];
    console.log('Sending key combo');
    await uinput.emitCombo(keys);
    console.log('Done');
}

(async() => {
    try {
        await main();
    } catch (err) {
        console.log(err);
    }
})();
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

### async UInputClass.sendEvent(type, code, value)

* *type* `Number`
* *code* `Number`
* *value* `Number`

It sends an event to the uinput device.

### async UInputClass.keyEvent(code)

* *code* `Number`

Wrapper over send_event to simulate key presses and mouse clicks.

### async UInputClass.emitCombo(code)

* *code* `Array with any combination of keys`

It sends an event to the uinput device with the combination
keys generated.
