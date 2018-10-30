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
