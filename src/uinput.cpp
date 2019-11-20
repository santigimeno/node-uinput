#include <nan.h>
#include <linux/input.h>
#include <linux/uinput.h>

using namespace v8;
using namespace node;

#define QUOTE(name) name

namespace {

void InputEvent (const Nan::FunctionCallbackInfo<v8::Value>& info) {
    Nan::HandleScope scope;

    int type;
    int code;
    int value;

    assert(info.Length() == 3);
    type = info[0]->Int32Value(Nan::GetCurrentContext()).FromJust();
    code = info[1]->Int32Value(Nan::GetCurrentContext()).FromJust();
    value = info[2]->Int32Value(Nan::GetCurrentContext()).FromJust();

    struct input_event ev;
    memset(&ev, 0, sizeof(ev));
    gettimeofday(&ev.time, NULL);
    ev.type = type;
    ev.code = code;
    ev.value = value;

    const char* ev_buf = reinterpret_cast<const char*>(
                             const_cast<const input_event*>(&ev));
    info.GetReturnValue().Set(
        Nan::CopyBuffer(ev_buf, sizeof(ev)).ToLocalChecked());
}

void Initialize(Local<v8::Object> input) {
    v8::Local<v8::Object> target = Nan::New<v8::Object>();

    Nan::Set(input, Nan::New("events").ToLocalChecked(), target);
    Nan::Set(input, Nan::New("input_event").ToLocalChecked(),
                Nan::GetFunction(Nan::New<FunctionTemplate>(InputEvent)).ToLocalChecked());

    /* input.h */
    Nan::Set(target, Nan::New("EV_SYN").ToLocalChecked(),
                Nan::New(EV_SYN));
    Nan::Set(target, Nan::New("EV_KEY").ToLocalChecked(),
                Nan::New(EV_KEY));
    Nan::Set(target, Nan::New("EV_REL").ToLocalChecked(),
                Nan::New(EV_REL));
    Nan::Set(target, Nan::New("EV_ABS").ToLocalChecked(),
                Nan::New(EV_ABS));
    Nan::Set(target, Nan::New("EV_MSC").ToLocalChecked(),
                Nan::New(EV_MSC));
    Nan::Set(target, Nan::New("EV_SW").ToLocalChecked(),
                Nan::New(EV_SW));
    Nan::Set(target, Nan::New("EV_LED").ToLocalChecked(),
                Nan::New(EV_LED));
    Nan::Set(target, Nan::New("EV_SND").ToLocalChecked(),
                Nan::New(EV_SND));
    Nan::Set(target, Nan::New("EV_REP").ToLocalChecked(),
                Nan::New(EV_REP));
    Nan::Set(target, Nan::New("EV_FF").ToLocalChecked(),
                Nan::New(EV_FF));
    Nan::Set(target, Nan::New("EV_PWR").ToLocalChecked(),
                Nan::New(EV_PWR));
    Nan::Set(target, Nan::New("EV_FF_STATUS").ToLocalChecked(),
                Nan::New(EV_FF_STATUS));
    Nan::Set(target, Nan::New("EV_MAX").ToLocalChecked(),
                Nan::New(EV_MAX));
    Nan::Set(target, Nan::New("EV_CNT").ToLocalChecked(),
                Nan::New(EV_CNT));
    Nan::Set(target, Nan::New("SYN_REPORT").ToLocalChecked(),
                Nan::New(SYN_REPORT));
    Nan::Set(target, Nan::New("SYN_CONFIG").ToLocalChecked(),
                Nan::New(SYN_CONFIG));
    Nan::Set(target, Nan::New("SYN_MT_REPORT").ToLocalChecked(),
                Nan::New(SYN_MT_REPORT));
    Nan::Set(target, Nan::New("SYN_DROPPED").ToLocalChecked(),
                Nan::New(SYN_DROPPED));
    Nan::Set(target, Nan::New("KEY_RESERVED").ToLocalChecked(),
                Nan::New(KEY_RESERVED));
    Nan::Set(target, Nan::New("KEY_ESC").ToLocalChecked(),
                Nan::New(KEY_ESC));
    Nan::Set(target, Nan::New("KEY_1").ToLocalChecked(),
                Nan::New(KEY_1));
    Nan::Set(target, Nan::New("KEY_2").ToLocalChecked(),
                Nan::New(KEY_2));
    Nan::Set(target, Nan::New("KEY_3").ToLocalChecked(),
                Nan::New(KEY_3));
    Nan::Set(target, Nan::New("KEY_4").ToLocalChecked(),
                Nan::New(KEY_4));
    Nan::Set(target, Nan::New("KEY_5").ToLocalChecked(),
                Nan::New(KEY_5));
    Nan::Set(target, Nan::New("KEY_6").ToLocalChecked(),
                Nan::New(KEY_6));
    Nan::Set(target, Nan::New("KEY_7").ToLocalChecked(),
                Nan::New(KEY_7));
    Nan::Set(target, Nan::New("KEY_8").ToLocalChecked(),
                Nan::New(KEY_8));
    Nan::Set(target, Nan::New("KEY_9").ToLocalChecked(),
                Nan::New(KEY_9));
    Nan::Set(target, Nan::New("KEY_0").ToLocalChecked(),
                Nan::New(KEY_0));
    Nan::Set(target, Nan::New("KEY_MINUS").ToLocalChecked(),
                Nan::New(KEY_MINUS));
    Nan::Set(target, Nan::New("KEY_EQUAL").ToLocalChecked(),
                Nan::New(KEY_EQUAL));
    Nan::Set(target, Nan::New("KEY_BACKSPACE").ToLocalChecked(),
                Nan::New(KEY_BACKSPACE));
    Nan::Set(target, Nan::New("KEY_TAB").ToLocalChecked(),
                Nan::New(KEY_TAB));
    Nan::Set(target, Nan::New("KEY_Q").ToLocalChecked(),
                Nan::New(KEY_Q));
    Nan::Set(target, Nan::New("KEY_W").ToLocalChecked(),
                Nan::New(KEY_W));
    Nan::Set(target, Nan::New("KEY_E").ToLocalChecked(),
                Nan::New(KEY_E));
    Nan::Set(target, Nan::New("KEY_R").ToLocalChecked(),
                Nan::New(KEY_R));
    Nan::Set(target, Nan::New("KEY_T").ToLocalChecked(),
                Nan::New(KEY_T));
    Nan::Set(target, Nan::New("KEY_Y").ToLocalChecked(),
                Nan::New(KEY_Y));
    Nan::Set(target, Nan::New("KEY_U").ToLocalChecked(),
                Nan::New(KEY_U));
    Nan::Set(target, Nan::New("KEY_I").ToLocalChecked(),
                Nan::New(KEY_I));
    Nan::Set(target, Nan::New("KEY_O").ToLocalChecked(),
                Nan::New(KEY_O));
    Nan::Set(target, Nan::New("KEY_P").ToLocalChecked(),
                Nan::New(KEY_P));
    Nan::Set(target, Nan::New("KEY_LEFTBRACE").ToLocalChecked(),
                Nan::New(KEY_LEFTBRACE));
    Nan::Set(target, Nan::New("KEY_RIGHTBRACE").ToLocalChecked(),
                Nan::New(KEY_RIGHTBRACE));
    Nan::Set(target, Nan::New("KEY_ENTER").ToLocalChecked(),
                Nan::New(KEY_ENTER));
    Nan::Set(target, Nan::New("KEY_LEFTCTRL").ToLocalChecked(),
                Nan::New(KEY_LEFTCTRL));
    Nan::Set(target, Nan::New("KEY_A").ToLocalChecked(),
                Nan::New(KEY_A));
    Nan::Set(target, Nan::New("KEY_S").ToLocalChecked(),
                Nan::New(KEY_S));
    Nan::Set(target, Nan::New("KEY_D").ToLocalChecked(),
                Nan::New(KEY_D));
    Nan::Set(target, Nan::New("KEY_F").ToLocalChecked(),
                Nan::New(KEY_F));
    Nan::Set(target, Nan::New("KEY_G").ToLocalChecked(),
                Nan::New(KEY_G));
    Nan::Set(target, Nan::New("KEY_H").ToLocalChecked(),
                Nan::New(KEY_H));
    Nan::Set(target, Nan::New("KEY_J").ToLocalChecked(),
                Nan::New(KEY_J));
    Nan::Set(target, Nan::New("KEY_K").ToLocalChecked(),
                Nan::New(KEY_K));
    Nan::Set(target, Nan::New("KEY_L").ToLocalChecked(),
                Nan::New(KEY_L));
    Nan::Set(target, Nan::New("KEY_SEMICOLON").ToLocalChecked(),
                Nan::New(KEY_SEMICOLON));
    Nan::Set(target, Nan::New("KEY_APOSTROPHE").ToLocalChecked(),
                Nan::New(KEY_APOSTROPHE));
    Nan::Set(target, Nan::New("KEY_GRAVE").ToLocalChecked(),
                Nan::New(KEY_GRAVE));
    Nan::Set(target, Nan::New("KEY_LEFTSHIFT").ToLocalChecked(),
                Nan::New(KEY_LEFTSHIFT));
    Nan::Set(target, Nan::New("KEY_BACKSLASH").ToLocalChecked(),
                Nan::New(KEY_BACKSLASH));
    Nan::Set(target, Nan::New("KEY_Z").ToLocalChecked(),
                Nan::New(KEY_Z));
    Nan::Set(target, Nan::New("KEY_X").ToLocalChecked(),
                Nan::New(KEY_X));
    Nan::Set(target, Nan::New("KEY_C").ToLocalChecked(),
                Nan::New(KEY_C));
    Nan::Set(target, Nan::New("KEY_V").ToLocalChecked(),
                Nan::New(KEY_V));
    Nan::Set(target, Nan::New("KEY_B").ToLocalChecked(),
                Nan::New(KEY_B));
    Nan::Set(target, Nan::New("KEY_N").ToLocalChecked(),
                Nan::New(KEY_N));
    Nan::Set(target, Nan::New("KEY_M").ToLocalChecked(),
                Nan::New(KEY_M));
    Nan::Set(target, Nan::New("KEY_COMMA").ToLocalChecked(),
                Nan::New(KEY_COMMA));
    Nan::Set(target, Nan::New("KEY_DOT").ToLocalChecked(),
                Nan::New(KEY_DOT));
    Nan::Set(target, Nan::New("KEY_SLASH").ToLocalChecked(),
                Nan::New(KEY_SLASH));
    Nan::Set(target, Nan::New("KEY_RIGHTSHIFT").ToLocalChecked(),
                Nan::New(KEY_RIGHTSHIFT));
    Nan::Set(target, Nan::New("KEY_KPASTERISK").ToLocalChecked(),
                Nan::New(KEY_KPASTERISK));
    Nan::Set(target, Nan::New("KEY_LEFTALT").ToLocalChecked(),
                Nan::New(KEY_LEFTALT));
    Nan::Set(target, Nan::New("KEY_SPACE").ToLocalChecked(),
                Nan::New(KEY_SPACE));
    Nan::Set(target, Nan::New("KEY_CAPSLOCK").ToLocalChecked(),
                Nan::New(KEY_CAPSLOCK));
    Nan::Set(target, Nan::New("KEY_F1").ToLocalChecked(),
                Nan::New(KEY_F1));
    Nan::Set(target, Nan::New("KEY_F2").ToLocalChecked(),
                Nan::New(KEY_F2));
    Nan::Set(target, Nan::New("KEY_F3").ToLocalChecked(),
                Nan::New(KEY_F3));
    Nan::Set(target, Nan::New("KEY_F4").ToLocalChecked(),
                Nan::New(KEY_F4));
    Nan::Set(target, Nan::New("KEY_F5").ToLocalChecked(),
                Nan::New(KEY_F5));
    Nan::Set(target, Nan::New("KEY_F6").ToLocalChecked(),
                Nan::New(KEY_F6));
    Nan::Set(target, Nan::New("KEY_F7").ToLocalChecked(),
                Nan::New(KEY_F7));
    Nan::Set(target, Nan::New("KEY_F8").ToLocalChecked(),
                Nan::New(KEY_F8));
    Nan::Set(target, Nan::New("KEY_F9").ToLocalChecked(),
                Nan::New(KEY_F9));
    Nan::Set(target, Nan::New("KEY_F10").ToLocalChecked(),
                Nan::New(KEY_F10));
    Nan::Set(target, Nan::New("KEY_NUMLOCK").ToLocalChecked(),
                Nan::New(KEY_NUMLOCK));
    Nan::Set(target, Nan::New("KEY_SCROLLLOCK").ToLocalChecked(),
                Nan::New(KEY_SCROLLLOCK));
    Nan::Set(target, Nan::New("KEY_KP7").ToLocalChecked(),
                Nan::New(KEY_KP7));
    Nan::Set(target, Nan::New("KEY_KP8").ToLocalChecked(),
                Nan::New(KEY_KP8));
    Nan::Set(target, Nan::New("KEY_KP9").ToLocalChecked(),
                Nan::New(KEY_KP9));
    Nan::Set(target, Nan::New("KEY_KPMINUS").ToLocalChecked(),
                Nan::New(KEY_KPMINUS));
    Nan::Set(target, Nan::New("KEY_KP4").ToLocalChecked(),
                Nan::New(KEY_KP4));
    Nan::Set(target, Nan::New("KEY_KP5").ToLocalChecked(),
                Nan::New(KEY_KP5));
    Nan::Set(target, Nan::New("KEY_KP6").ToLocalChecked(),
                Nan::New(KEY_KP6));
    Nan::Set(target, Nan::New("KEY_KPPLUS").ToLocalChecked(),
                Nan::New(KEY_KPPLUS));
    Nan::Set(target, Nan::New("KEY_KP1").ToLocalChecked(),
                Nan::New(KEY_KP1));
    Nan::Set(target, Nan::New("KEY_KP2").ToLocalChecked(),
                Nan::New(KEY_KP2));
    Nan::Set(target, Nan::New("KEY_KP3").ToLocalChecked(),
                Nan::New(KEY_KP3));
    Nan::Set(target, Nan::New("KEY_KP0").ToLocalChecked(),
                Nan::New(KEY_KP0));
    Nan::Set(target, Nan::New("KEY_KPDOT").ToLocalChecked(),
                Nan::New(KEY_KPDOT));
    Nan::Set(target, Nan::New("KEY_ZENKAKUHANKAKU").ToLocalChecked(),
                Nan::New(KEY_ZENKAKUHANKAKU));
    Nan::Set(target, Nan::New("KEY_102ND").ToLocalChecked(),
                Nan::New(KEY_102ND));
    Nan::Set(target, Nan::New("KEY_F11").ToLocalChecked(),
                Nan::New(KEY_F11));
    Nan::Set(target, Nan::New("KEY_F12").ToLocalChecked(),
                Nan::New(KEY_F12));
    Nan::Set(target, Nan::New("KEY_RO").ToLocalChecked(),
                Nan::New(KEY_RO));
    Nan::Set(target, Nan::New("KEY_KATAKANA").ToLocalChecked(),
                Nan::New(KEY_KATAKANA));
    Nan::Set(target, Nan::New("KEY_HIRAGANA").ToLocalChecked(),
                Nan::New(KEY_HIRAGANA));
    Nan::Set(target, Nan::New("KEY_HENKAN").ToLocalChecked(),
                Nan::New(KEY_HENKAN));
    Nan::Set(target, Nan::New("KEY_KATAKANAHIRAGANA").ToLocalChecked(),
                Nan::New(KEY_KATAKANAHIRAGANA));
    Nan::Set(target, Nan::New("KEY_MUHENKAN").ToLocalChecked(),
                Nan::New(KEY_MUHENKAN));
    Nan::Set(target, Nan::New("KEY_KPJPCOMMA").ToLocalChecked(),
                Nan::New(KEY_KPJPCOMMA));
    Nan::Set(target, Nan::New("KEY_KPENTER").ToLocalChecked(),
                Nan::New(KEY_KPENTER));
    Nan::Set(target, Nan::New("KEY_RIGHTCTRL").ToLocalChecked(),
                Nan::New(KEY_RIGHTCTRL));
    Nan::Set(target, Nan::New("KEY_KPSLASH").ToLocalChecked(),
                Nan::New(KEY_KPSLASH));
    Nan::Set(target, Nan::New("KEY_SYSRQ").ToLocalChecked(),
                Nan::New(KEY_SYSRQ));
    Nan::Set(target, Nan::New("KEY_RIGHTALT").ToLocalChecked(),
                Nan::New(KEY_RIGHTALT));
    Nan::Set(target, Nan::New("KEY_LINEFEED").ToLocalChecked(),
                Nan::New(KEY_LINEFEED));
    Nan::Set(target, Nan::New("KEY_HOME").ToLocalChecked(),
                Nan::New(KEY_HOME));
    Nan::Set(target, Nan::New("KEY_UP").ToLocalChecked(),
                Nan::New(KEY_UP));
    Nan::Set(target, Nan::New("KEY_PAGEUP").ToLocalChecked(),
                Nan::New(KEY_PAGEUP));
    Nan::Set(target, Nan::New("KEY_LEFT").ToLocalChecked(),
                Nan::New(KEY_LEFT));
    Nan::Set(target, Nan::New("KEY_RIGHT").ToLocalChecked(),
                Nan::New(KEY_RIGHT));
    Nan::Set(target, Nan::New("KEY_END").ToLocalChecked(),
                Nan::New(KEY_END));
    Nan::Set(target, Nan::New("KEY_DOWN").ToLocalChecked(),
                Nan::New(KEY_DOWN));
    Nan::Set(target, Nan::New("KEY_PAGEDOWN").ToLocalChecked(),
                Nan::New(KEY_PAGEDOWN));
    Nan::Set(target, Nan::New("KEY_INSERT").ToLocalChecked(),
                Nan::New(KEY_INSERT));
    Nan::Set(target, Nan::New("KEY_DELETE").ToLocalChecked(),
                Nan::New(KEY_DELETE));
    Nan::Set(target, Nan::New("KEY_MACRO").ToLocalChecked(),
                Nan::New(KEY_MACRO));
    Nan::Set(target, Nan::New("KEY_MUTE").ToLocalChecked(),
                Nan::New(KEY_MUTE));
    Nan::Set(target, Nan::New("KEY_VOLUMEDOWN").ToLocalChecked(),
                Nan::New(KEY_VOLUMEDOWN));
    Nan::Set(target, Nan::New("KEY_VOLUMEUP").ToLocalChecked(),
                Nan::New(KEY_VOLUMEUP));
    Nan::Set(target, Nan::New("KEY_POWER").ToLocalChecked(),
                Nan::New(KEY_POWER));
    Nan::Set(target, Nan::New("KEY_KPEQUAL").ToLocalChecked(),
                Nan::New(KEY_KPEQUAL));
    Nan::Set(target, Nan::New("KEY_KPPLUSMINUS").ToLocalChecked(),
                Nan::New(KEY_KPPLUSMINUS));
    Nan::Set(target, Nan::New("KEY_PAUSE").ToLocalChecked(),
                Nan::New(KEY_PAUSE));
    Nan::Set(target, Nan::New("KEY_SCALE").ToLocalChecked(),
                Nan::New(KEY_SCALE));
    Nan::Set(target, Nan::New("KEY_KPCOMMA").ToLocalChecked(),
                Nan::New(KEY_KPCOMMA));
    Nan::Set(target, Nan::New("KEY_HANGEUL").ToLocalChecked(),
                Nan::New(KEY_HANGEUL));
    Nan::Set(target, Nan::New("KEY_HANGUEL").ToLocalChecked(),
                Nan::New(KEY_HANGUEL));
    Nan::Set(target, Nan::New("KEY_HANJA").ToLocalChecked(),
                Nan::New(KEY_HANJA));
    Nan::Set(target, Nan::New("KEY_YEN").ToLocalChecked(),
                Nan::New(KEY_YEN));
    Nan::Set(target, Nan::New("KEY_LEFTMETA").ToLocalChecked(),
                Nan::New(KEY_LEFTMETA));
    Nan::Set(target, Nan::New("KEY_RIGHTMETA").ToLocalChecked(),
                Nan::New(KEY_RIGHTMETA));
    Nan::Set(target, Nan::New("KEY_COMPOSE").ToLocalChecked(),
                Nan::New(KEY_COMPOSE));
    Nan::Set(target, Nan::New("KEY_STOP").ToLocalChecked(),
                Nan::New(KEY_STOP));
    Nan::Set(target, Nan::New("KEY_AGAIN").ToLocalChecked(),
                Nan::New(KEY_AGAIN));
    Nan::Set(target, Nan::New("KEY_PROPS").ToLocalChecked(),
                Nan::New(KEY_PROPS));
    Nan::Set(target, Nan::New("KEY_UNDO").ToLocalChecked(),
                Nan::New(KEY_UNDO));
    Nan::Set(target, Nan::New("KEY_FRONT").ToLocalChecked(),
                Nan::New(KEY_FRONT));
    Nan::Set(target, Nan::New("KEY_COPY").ToLocalChecked(),
                Nan::New(KEY_COPY));
    Nan::Set(target, Nan::New("KEY_OPEN").ToLocalChecked(),
                Nan::New(KEY_OPEN));
    Nan::Set(target, Nan::New("KEY_PASTE").ToLocalChecked(),
                Nan::New(KEY_PASTE));
    Nan::Set(target, Nan::New("KEY_FIND").ToLocalChecked(),
                Nan::New(KEY_FIND));
    Nan::Set(target, Nan::New("KEY_CUT").ToLocalChecked(),
                Nan::New(KEY_CUT));
    Nan::Set(target, Nan::New("KEY_HELP").ToLocalChecked(),
                Nan::New(KEY_HELP));
    Nan::Set(target, Nan::New("KEY_MENU").ToLocalChecked(),
                Nan::New(KEY_MENU));
    Nan::Set(target, Nan::New("KEY_CALC").ToLocalChecked(),
                Nan::New(KEY_CALC));
    Nan::Set(target, Nan::New("KEY_SETUP").ToLocalChecked(),
                Nan::New(KEY_SETUP));
    Nan::Set(target, Nan::New("KEY_SLEEP").ToLocalChecked(),
                Nan::New(KEY_SLEEP));
    Nan::Set(target, Nan::New("KEY_WAKEUP").ToLocalChecked(),
                Nan::New(KEY_WAKEUP));
    Nan::Set(target, Nan::New("KEY_FILE").ToLocalChecked(),
                Nan::New(KEY_FILE));
    Nan::Set(target, Nan::New("KEY_SENDFILE").ToLocalChecked(),
                Nan::New(KEY_SENDFILE));
    Nan::Set(target, Nan::New("KEY_DELETEFILE").ToLocalChecked(),
                Nan::New(KEY_DELETEFILE));
    Nan::Set(target, Nan::New("KEY_XFER").ToLocalChecked(),
                Nan::New(KEY_XFER));
    Nan::Set(target, Nan::New("KEY_PROG1").ToLocalChecked(),
                Nan::New(KEY_PROG1));
    Nan::Set(target, Nan::New("KEY_PROG2").ToLocalChecked(),
                Nan::New(KEY_PROG2));
    Nan::Set(target, Nan::New("KEY_WWW").ToLocalChecked(),
                Nan::New(KEY_WWW));
    Nan::Set(target, Nan::New("KEY_MSDOS").ToLocalChecked(),
                Nan::New(KEY_MSDOS));
    Nan::Set(target, Nan::New("KEY_COFFEE").ToLocalChecked(),
                Nan::New(KEY_COFFEE));
    Nan::Set(target, Nan::New("KEY_SCREENLOCK").ToLocalChecked(),
                Nan::New(KEY_SCREENLOCK));
    Nan::Set(target, Nan::New("KEY_DIRECTION").ToLocalChecked(),
                Nan::New(KEY_DIRECTION));
    Nan::Set(target, Nan::New("KEY_CYCLEWINDOWS").ToLocalChecked(),
                Nan::New(KEY_CYCLEWINDOWS));
    Nan::Set(target, Nan::New("KEY_MAIL").ToLocalChecked(),
                Nan::New(KEY_MAIL));
    Nan::Set(target, Nan::New("KEY_BOOKMARKS").ToLocalChecked(),
                Nan::New(KEY_BOOKMARKS));
    Nan::Set(target, Nan::New("KEY_COMPUTER").ToLocalChecked(),
                Nan::New(KEY_COMPUTER));
    Nan::Set(target, Nan::New("KEY_BACK").ToLocalChecked(),
                Nan::New(KEY_BACK));
    Nan::Set(target, Nan::New("KEY_FORWARD").ToLocalChecked(),
                Nan::New(KEY_FORWARD));
    Nan::Set(target, Nan::New("KEY_CLOSECD").ToLocalChecked(),
                Nan::New(KEY_CLOSECD));
    Nan::Set(target, Nan::New("KEY_EJECTCD").ToLocalChecked(),
                Nan::New(KEY_EJECTCD));
    Nan::Set(target, Nan::New("KEY_EJECTCLOSECD").ToLocalChecked(),
                Nan::New(KEY_EJECTCLOSECD));
    Nan::Set(target, Nan::New("KEY_NEXTSONG").ToLocalChecked(),
                Nan::New(KEY_NEXTSONG));
    Nan::Set(target, Nan::New("KEY_PLAYPAUSE").ToLocalChecked(),
                Nan::New(KEY_PLAYPAUSE));
    Nan::Set(target, Nan::New("KEY_PREVIOUSSONG").ToLocalChecked(),
                Nan::New(KEY_PREVIOUSSONG));
    Nan::Set(target, Nan::New("KEY_STOPCD").ToLocalChecked(),
                Nan::New(KEY_STOPCD));
    Nan::Set(target, Nan::New("KEY_RECORD").ToLocalChecked(),
                Nan::New(KEY_RECORD));
    Nan::Set(target, Nan::New("KEY_REWIND").ToLocalChecked(),
                Nan::New(KEY_REWIND));
    Nan::Set(target, Nan::New("KEY_PHONE").ToLocalChecked(),
                Nan::New(KEY_PHONE));
    Nan::Set(target, Nan::New("KEY_ISO").ToLocalChecked(),
                Nan::New(KEY_ISO));
    Nan::Set(target, Nan::New("KEY_CONFIG").ToLocalChecked(),
                Nan::New(KEY_CONFIG));
    Nan::Set(target, Nan::New("KEY_HOMEPAGE").ToLocalChecked(),
                Nan::New(KEY_HOMEPAGE));
    Nan::Set(target, Nan::New("KEY_REFRESH").ToLocalChecked(),
                Nan::New(KEY_REFRESH));
    Nan::Set(target, Nan::New("KEY_EXIT").ToLocalChecked(),
                Nan::New(KEY_EXIT));
    Nan::Set(target, Nan::New("KEY_MOVE").ToLocalChecked(),
                Nan::New(KEY_MOVE));
    Nan::Set(target, Nan::New("KEY_EDIT").ToLocalChecked(),
                Nan::New(KEY_EDIT));
    Nan::Set(target, Nan::New("KEY_SCROLLUP").ToLocalChecked(),
                Nan::New(KEY_SCROLLUP));
    Nan::Set(target, Nan::New("KEY_SCROLLDOWN").ToLocalChecked(),
                Nan::New(KEY_SCROLLDOWN));
    Nan::Set(target, Nan::New("KEY_KPLEFTPAREN").ToLocalChecked(),
                Nan::New(KEY_KPLEFTPAREN));
    Nan::Set(target, Nan::New("KEY_KPRIGHTPAREN").ToLocalChecked(),
                Nan::New(KEY_KPRIGHTPAREN));
    Nan::Set(target, Nan::New("KEY_NEW").ToLocalChecked(),
                Nan::New(KEY_NEW));
    Nan::Set(target, Nan::New("KEY_REDO").ToLocalChecked(),
                Nan::New(KEY_REDO));
    Nan::Set(target, Nan::New("KEY_F13").ToLocalChecked(),
                Nan::New(KEY_F13));
    Nan::Set(target, Nan::New("KEY_F14").ToLocalChecked(),
                Nan::New(KEY_F14));
    Nan::Set(target, Nan::New("KEY_F15").ToLocalChecked(),
                Nan::New(KEY_F15));
    Nan::Set(target, Nan::New("KEY_F16").ToLocalChecked(),
                Nan::New(KEY_F16));
    Nan::Set(target, Nan::New("KEY_F17").ToLocalChecked(),
                Nan::New(KEY_F17));
    Nan::Set(target, Nan::New("KEY_F18").ToLocalChecked(),
                Nan::New(KEY_F18));
    Nan::Set(target, Nan::New("KEY_F19").ToLocalChecked(),
                Nan::New(KEY_F19));
    Nan::Set(target, Nan::New("KEY_F20").ToLocalChecked(),
                Nan::New(KEY_F20));
    Nan::Set(target, Nan::New("KEY_F21").ToLocalChecked(),
                Nan::New(KEY_F21));
    Nan::Set(target, Nan::New("KEY_F22").ToLocalChecked(),
                Nan::New(KEY_F22));
    Nan::Set(target, Nan::New("KEY_F23").ToLocalChecked(),
                Nan::New(KEY_F23));
    Nan::Set(target, Nan::New("KEY_F24").ToLocalChecked(),
                Nan::New(KEY_F24));
    Nan::Set(target, Nan::New("KEY_PLAYCD").ToLocalChecked(),
                Nan::New(KEY_PLAYCD));
    Nan::Set(target, Nan::New("KEY_PAUSECD").ToLocalChecked(),
                Nan::New(KEY_PAUSECD));
    Nan::Set(target, Nan::New("KEY_PROG3").ToLocalChecked(),
                Nan::New(KEY_PROG3));
    Nan::Set(target, Nan::New("KEY_PROG4").ToLocalChecked(),
                Nan::New(KEY_PROG4));
    Nan::Set(target, Nan::New("KEY_DASHBOARD").ToLocalChecked(),
                Nan::New(KEY_DASHBOARD));
    Nan::Set(target, Nan::New("KEY_SUSPEND").ToLocalChecked(),
                Nan::New(KEY_SUSPEND));
    Nan::Set(target, Nan::New("KEY_CLOSE").ToLocalChecked(),
                Nan::New(KEY_CLOSE));
    Nan::Set(target, Nan::New("KEY_PLAY").ToLocalChecked(),
                Nan::New(KEY_PLAY));
    Nan::Set(target, Nan::New("KEY_FASTFORWARD").ToLocalChecked(),
                Nan::New(KEY_FASTFORWARD));
    Nan::Set(target, Nan::New("KEY_BASSBOOST").ToLocalChecked(),
                Nan::New(KEY_BASSBOOST));
    Nan::Set(target, Nan::New("KEY_PRINT").ToLocalChecked(),
                Nan::New(KEY_PRINT));
    Nan::Set(target, Nan::New("KEY_HP").ToLocalChecked(),
                Nan::New(KEY_HP));
    Nan::Set(target, Nan::New("KEY_CAMERA").ToLocalChecked(),
                Nan::New(KEY_CAMERA));
    Nan::Set(target, Nan::New("KEY_SOUND").ToLocalChecked(),
                Nan::New(KEY_SOUND));
    Nan::Set(target, Nan::New("KEY_QUESTION").ToLocalChecked(),
                Nan::New(KEY_QUESTION));
    Nan::Set(target, Nan::New("KEY_EMAIL").ToLocalChecked(),
                Nan::New(KEY_EMAIL));
    Nan::Set(target, Nan::New("KEY_CHAT").ToLocalChecked(),
                Nan::New(KEY_CHAT));
    Nan::Set(target, Nan::New("KEY_SEARCH").ToLocalChecked(),
                Nan::New(KEY_SEARCH));
    Nan::Set(target, Nan::New("KEY_CONNECT").ToLocalChecked(),
                Nan::New(KEY_CONNECT));
    Nan::Set(target, Nan::New("KEY_FINANCE").ToLocalChecked(),
                Nan::New(KEY_FINANCE));
    Nan::Set(target, Nan::New("KEY_SPORT").ToLocalChecked(),
                Nan::New(KEY_SPORT));
    Nan::Set(target, Nan::New("KEY_SHOP").ToLocalChecked(),
                Nan::New(KEY_SHOP));
    Nan::Set(target, Nan::New("KEY_ALTERASE").ToLocalChecked(),
                Nan::New(KEY_ALTERASE));
    Nan::Set(target, Nan::New("KEY_CANCEL").ToLocalChecked(),
                Nan::New(KEY_CANCEL));
    Nan::Set(target, Nan::New("KEY_BRIGHTNESSDOWN").ToLocalChecked(),
                Nan::New(KEY_BRIGHTNESSDOWN));
    Nan::Set(target, Nan::New("KEY_BRIGHTNESSUP").ToLocalChecked(),
                Nan::New(KEY_BRIGHTNESSUP));
    Nan::Set(target, Nan::New("KEY_MEDIA").ToLocalChecked(),
                Nan::New(KEY_MEDIA));
    Nan::Set(target, Nan::New("KEY_SWITCHVIDEOMODE").ToLocalChecked(),
                Nan::New(KEY_SWITCHVIDEOMODE));
    Nan::Set(target, Nan::New("KEY_KBDILLUMTOGGLE").ToLocalChecked(),
                Nan::New(KEY_KBDILLUMTOGGLE));
    Nan::Set(target, Nan::New("KEY_KBDILLUMDOWN").ToLocalChecked(),
                Nan::New(KEY_KBDILLUMDOWN));
    Nan::Set(target, Nan::New("KEY_KBDILLUMUP").ToLocalChecked(),
                Nan::New(KEY_KBDILLUMUP));
    Nan::Set(target, Nan::New("KEY_SEND").ToLocalChecked(),
                Nan::New(KEY_SEND));
    Nan::Set(target, Nan::New("KEY_REPLY").ToLocalChecked(),
                Nan::New(KEY_REPLY));
    Nan::Set(target, Nan::New("KEY_FORWARDMAIL").ToLocalChecked(),
                Nan::New(KEY_FORWARDMAIL));
    Nan::Set(target, Nan::New("KEY_SAVE").ToLocalChecked(),
                Nan::New(KEY_SAVE));
    Nan::Set(target, Nan::New("KEY_DOCUMENTS").ToLocalChecked(),
                Nan::New(KEY_DOCUMENTS));
    Nan::Set(target, Nan::New("KEY_BATTERY").ToLocalChecked(),
                Nan::New(KEY_BATTERY));
    Nan::Set(target, Nan::New("KEY_BLUETOOTH").ToLocalChecked(),
                Nan::New(KEY_BLUETOOTH));
    Nan::Set(target, Nan::New("KEY_WLAN").ToLocalChecked(),
                Nan::New(KEY_WLAN));
    Nan::Set(target, Nan::New("KEY_UWB").ToLocalChecked(),
                Nan::New(KEY_UWB));
    Nan::Set(target, Nan::New("KEY_UNKNOWN").ToLocalChecked(),
                Nan::New(KEY_UNKNOWN));
    Nan::Set(target, Nan::New("KEY_VIDEO_NEXT").ToLocalChecked(),
                Nan::New(KEY_VIDEO_NEXT));
    Nan::Set(target, Nan::New("KEY_VIDEO_PREV").ToLocalChecked(),
                Nan::New(KEY_VIDEO_PREV));
    Nan::Set(target, Nan::New("KEY_BRIGHTNESS_CYCLE").ToLocalChecked(),
                Nan::New(KEY_BRIGHTNESS_CYCLE));
    Nan::Set(target, Nan::New("KEY_BRIGHTNESS_ZERO").ToLocalChecked(),
                Nan::New(KEY_BRIGHTNESS_ZERO));
    Nan::Set(target, Nan::New("KEY_DISPLAY_OFF").ToLocalChecked(),
                Nan::New(KEY_DISPLAY_OFF));
    Nan::Set(target, Nan::New("KEY_WIMAX").ToLocalChecked(),
                Nan::New(KEY_WIMAX));
    Nan::Set(target, Nan::New("KEY_RFKILL").ToLocalChecked(),
                Nan::New(KEY_RFKILL));
    Nan::Set(target, Nan::New("KEY_MICMUTE").ToLocalChecked(),
                Nan::New(KEY_MICMUTE));
    Nan::Set(target, Nan::New("BTN_MISC").ToLocalChecked(),
                Nan::New(BTN_MISC));
    Nan::Set(target, Nan::New("BTN_0").ToLocalChecked(),
                Nan::New(BTN_0));
    Nan::Set(target, Nan::New("BTN_1").ToLocalChecked(),
                Nan::New(BTN_1));
    Nan::Set(target, Nan::New("BTN_2").ToLocalChecked(),
                Nan::New(BTN_2));
    Nan::Set(target, Nan::New("BTN_3").ToLocalChecked(),
                Nan::New(BTN_3));
    Nan::Set(target, Nan::New("BTN_4").ToLocalChecked(),
                Nan::New(BTN_4));
    Nan::Set(target, Nan::New("BTN_5").ToLocalChecked(),
                Nan::New(BTN_5));
    Nan::Set(target, Nan::New("BTN_6").ToLocalChecked(),
                Nan::New(BTN_6));
    Nan::Set(target, Nan::New("BTN_7").ToLocalChecked(),
                Nan::New(BTN_7));
    Nan::Set(target, Nan::New("BTN_8").ToLocalChecked(),
                Nan::New(BTN_8));
    Nan::Set(target, Nan::New("BTN_9").ToLocalChecked(),
                Nan::New(BTN_9));
    Nan::Set(target, Nan::New("BTN_MOUSE").ToLocalChecked(),
                Nan::New(BTN_MOUSE));
    Nan::Set(target, Nan::New("BTN_LEFT").ToLocalChecked(),
                Nan::New(BTN_LEFT));
    Nan::Set(target, Nan::New("BTN_RIGHT").ToLocalChecked(),
                Nan::New(BTN_RIGHT));
    Nan::Set(target, Nan::New("BTN_MIDDLE").ToLocalChecked(),
                Nan::New(BTN_MIDDLE));
    Nan::Set(target, Nan::New("BTN_SIDE").ToLocalChecked(),
                Nan::New(BTN_SIDE));
    Nan::Set(target, Nan::New("BTN_EXTRA").ToLocalChecked(),
                Nan::New(BTN_EXTRA));
    Nan::Set(target, Nan::New("BTN_FORWARD").ToLocalChecked(),
                Nan::New(BTN_FORWARD));
    Nan::Set(target, Nan::New("BTN_BACK").ToLocalChecked(),
                Nan::New(BTN_BACK));
    Nan::Set(target, Nan::New("BTN_TASK").ToLocalChecked(),
                Nan::New(BTN_TASK));
    Nan::Set(target, Nan::New("BTN_JOYSTICK").ToLocalChecked(),
                Nan::New(BTN_JOYSTICK));
    Nan::Set(target, Nan::New("BTN_TRIGGER").ToLocalChecked(),
                Nan::New(BTN_TRIGGER));
    Nan::Set(target, Nan::New("BTN_THUMB").ToLocalChecked(),
                Nan::New(BTN_THUMB));
    Nan::Set(target, Nan::New("BTN_THUMB2").ToLocalChecked(),
                Nan::New(BTN_THUMB2));
    Nan::Set(target, Nan::New("BTN_TOP").ToLocalChecked(),
                Nan::New(BTN_TOP));
    Nan::Set(target, Nan::New("BTN_TOP2").ToLocalChecked(),
                Nan::New(BTN_TOP2));
    Nan::Set(target, Nan::New("BTN_PINKIE").ToLocalChecked(),
                Nan::New(BTN_PINKIE));
    Nan::Set(target, Nan::New("BTN_BASE").ToLocalChecked(),
                Nan::New(BTN_BASE));
    Nan::Set(target, Nan::New("BTN_BASE2").ToLocalChecked(),
                Nan::New(BTN_BASE2));
    Nan::Set(target, Nan::New("BTN_BASE3").ToLocalChecked(),
                Nan::New(BTN_BASE3));
    Nan::Set(target, Nan::New("BTN_BASE4").ToLocalChecked(),
                Nan::New(BTN_BASE4));
    Nan::Set(target, Nan::New("BTN_BASE5").ToLocalChecked(),
                Nan::New(BTN_BASE5));
    Nan::Set(target, Nan::New("BTN_BASE6").ToLocalChecked(),
                Nan::New(BTN_BASE6));
    Nan::Set(target, Nan::New("BTN_DEAD").ToLocalChecked(),
                Nan::New(BTN_DEAD));
    Nan::Set(target, Nan::New("BTN_GAMEPAD").ToLocalChecked(),
                Nan::New(BTN_GAMEPAD));
    Nan::Set(target, Nan::New("BTN_A").ToLocalChecked(),
                Nan::New(BTN_A));
    Nan::Set(target, Nan::New("BTN_B").ToLocalChecked(),
                Nan::New(BTN_B));
    Nan::Set(target, Nan::New("BTN_C").ToLocalChecked(),
                Nan::New(BTN_C));
    Nan::Set(target, Nan::New("BTN_X").ToLocalChecked(),
                Nan::New(BTN_X));
    Nan::Set(target, Nan::New("BTN_Y").ToLocalChecked(),
                Nan::New(BTN_Y));
    Nan::Set(target, Nan::New("BTN_Z").ToLocalChecked(),
                Nan::New(BTN_Z));
    Nan::Set(target, Nan::New("BTN_TL").ToLocalChecked(),
                Nan::New(BTN_TL));
    Nan::Set(target, Nan::New("BTN_TR").ToLocalChecked(),
                Nan::New(BTN_TR));
    Nan::Set(target, Nan::New("BTN_TL2").ToLocalChecked(),
                Nan::New(BTN_TL2));
    Nan::Set(target, Nan::New("BTN_TR2").ToLocalChecked(),
                Nan::New(BTN_TR2));
    Nan::Set(target, Nan::New("BTN_SELECT").ToLocalChecked(),
                Nan::New(BTN_SELECT));
    Nan::Set(target, Nan::New("BTN_START").ToLocalChecked(),
                Nan::New(BTN_START));
    Nan::Set(target, Nan::New("BTN_MODE").ToLocalChecked(),
                Nan::New(BTN_MODE));
    Nan::Set(target, Nan::New("BTN_THUMBL").ToLocalChecked(),
                Nan::New(BTN_THUMBL));
    Nan::Set(target, Nan::New("BTN_THUMBR").ToLocalChecked(),
                Nan::New(BTN_THUMBR));
    Nan::Set(target, Nan::New("BTN_DIGI").ToLocalChecked(),
                Nan::New(BTN_DIGI));
    Nan::Set(target, Nan::New("BTN_TOOL_PEN").ToLocalChecked(),
                Nan::New(BTN_TOOL_PEN));
    Nan::Set(target, Nan::New("BTN_TOOL_RUBBER").ToLocalChecked(),
                Nan::New(BTN_TOOL_RUBBER));
    Nan::Set(target, Nan::New("BTN_TOOL_BRUSH").ToLocalChecked(),
                Nan::New(BTN_TOOL_BRUSH));
    Nan::Set(target, Nan::New("BTN_TOOL_PENCIL").ToLocalChecked(),
                Nan::New(BTN_TOOL_PENCIL));
    Nan::Set(target, Nan::New("BTN_TOOL_AIRBRUSH").ToLocalChecked(),
                Nan::New(BTN_TOOL_AIRBRUSH));
    Nan::Set(target, Nan::New("BTN_TOOL_FINGER").ToLocalChecked(),
                Nan::New(BTN_TOOL_FINGER));
    Nan::Set(target, Nan::New("BTN_TOOL_MOUSE").ToLocalChecked(),
                Nan::New(BTN_TOOL_MOUSE));
    Nan::Set(target, Nan::New("BTN_TOOL_LENS").ToLocalChecked(),
                Nan::New(BTN_TOOL_LENS));
    Nan::Set(target, Nan::New("BTN_TOOL_QUINTTAP").ToLocalChecked(),
                Nan::New(BTN_TOOL_QUINTTAP));
    Nan::Set(target, Nan::New("BTN_TOUCH").ToLocalChecked(),
                Nan::New(BTN_TOUCH));
    Nan::Set(target, Nan::New("BTN_STYLUS").ToLocalChecked(),
                Nan::New(BTN_STYLUS));
    Nan::Set(target, Nan::New("BTN_STYLUS2").ToLocalChecked(),
                Nan::New(BTN_STYLUS2));
    Nan::Set(target, Nan::New("BTN_TOOL_DOUBLETAP").ToLocalChecked(),
                Nan::New(BTN_TOOL_DOUBLETAP));
    Nan::Set(target, Nan::New("BTN_TOOL_TRIPLETAP").ToLocalChecked(),
                Nan::New(BTN_TOOL_TRIPLETAP));
    Nan::Set(target, Nan::New("BTN_TOOL_QUADTAP").ToLocalChecked(),
                Nan::New(BTN_TOOL_QUADTAP));
    Nan::Set(target, Nan::New("BTN_WHEEL").ToLocalChecked(),
                Nan::New(BTN_WHEEL));
    Nan::Set(target, Nan::New("BTN_GEAR_DOWN").ToLocalChecked(),
                Nan::New(BTN_GEAR_DOWN));
    Nan::Set(target, Nan::New("BTN_GEAR_UP").ToLocalChecked(),
                Nan::New(BTN_GEAR_UP));
    Nan::Set(target, Nan::New("KEY_OK").ToLocalChecked(),
                Nan::New(KEY_OK));
    Nan::Set(target, Nan::New("KEY_SELECT").ToLocalChecked(),
                Nan::New(KEY_SELECT));
    Nan::Set(target, Nan::New("KEY_GOTO").ToLocalChecked(),
                Nan::New(KEY_GOTO));
    Nan::Set(target, Nan::New("KEY_CLEAR").ToLocalChecked(),
                Nan::New(KEY_CLEAR));
    Nan::Set(target, Nan::New("KEY_POWER2").ToLocalChecked(),
                Nan::New(KEY_POWER2));
    Nan::Set(target, Nan::New("KEY_OPTION").ToLocalChecked(),
                Nan::New(KEY_OPTION));
    Nan::Set(target, Nan::New("KEY_INFO").ToLocalChecked(),
                Nan::New(KEY_INFO));
    Nan::Set(target, Nan::New("KEY_TIME").ToLocalChecked(),
                Nan::New(KEY_TIME));
    Nan::Set(target, Nan::New("KEY_VENDOR").ToLocalChecked(),
                Nan::New(KEY_VENDOR));
    Nan::Set(target, Nan::New("KEY_ARCHIVE").ToLocalChecked(),
                Nan::New(KEY_ARCHIVE));
    Nan::Set(target, Nan::New("KEY_PROGRAM").ToLocalChecked(),
                Nan::New(KEY_PROGRAM));
    Nan::Set(target, Nan::New("KEY_CHANNEL").ToLocalChecked(),
                Nan::New(KEY_CHANNEL));
    Nan::Set(target, Nan::New("KEY_FAVORITES").ToLocalChecked(),
                Nan::New(KEY_FAVORITES));
    Nan::Set(target, Nan::New("KEY_EPG").ToLocalChecked(),
                Nan::New(KEY_EPG));
    Nan::Set(target, Nan::New("KEY_PVR").ToLocalChecked(),
                Nan::New(KEY_PVR));
    Nan::Set(target, Nan::New("KEY_MHP").ToLocalChecked(),
                Nan::New(KEY_MHP));
    Nan::Set(target, Nan::New("KEY_LANGUAGE").ToLocalChecked(),
                Nan::New(KEY_LANGUAGE));
    Nan::Set(target, Nan::New("KEY_TITLE").ToLocalChecked(),
                Nan::New(KEY_TITLE));
    Nan::Set(target, Nan::New("KEY_SUBTITLE").ToLocalChecked(),
                Nan::New(KEY_SUBTITLE));
    Nan::Set(target, Nan::New("KEY_ANGLE").ToLocalChecked(),
                Nan::New(KEY_ANGLE));
    Nan::Set(target, Nan::New("KEY_ZOOM").ToLocalChecked(),
                Nan::New(KEY_ZOOM));
    Nan::Set(target, Nan::New("KEY_MODE").ToLocalChecked(),
                Nan::New(KEY_MODE));
    Nan::Set(target, Nan::New("KEY_KEYBOARD").ToLocalChecked(),
                Nan::New(KEY_KEYBOARD));
    Nan::Set(target, Nan::New("KEY_SCREEN").ToLocalChecked(),
                Nan::New(KEY_SCREEN));
    Nan::Set(target, Nan::New("KEY_PC").ToLocalChecked(),
                Nan::New(KEY_PC));
    Nan::Set(target, Nan::New("KEY_TV").ToLocalChecked(),
                Nan::New(KEY_TV));
    Nan::Set(target, Nan::New("KEY_TV2").ToLocalChecked(),
                Nan::New(KEY_TV2));
    Nan::Set(target, Nan::New("KEY_VCR").ToLocalChecked(),
                Nan::New(KEY_VCR));
    Nan::Set(target, Nan::New("KEY_VCR2").ToLocalChecked(),
                Nan::New(KEY_VCR2));
    Nan::Set(target, Nan::New("KEY_SAT").ToLocalChecked(),
                Nan::New(KEY_SAT));
    Nan::Set(target, Nan::New("KEY_SAT2").ToLocalChecked(),
                Nan::New(KEY_SAT2));
    Nan::Set(target, Nan::New("KEY_CD").ToLocalChecked(),
                Nan::New(KEY_CD));
    Nan::Set(target, Nan::New("KEY_TAPE").ToLocalChecked(),
                Nan::New(KEY_TAPE));
    Nan::Set(target, Nan::New("KEY_RADIO").ToLocalChecked(),
                Nan::New(KEY_RADIO));
    Nan::Set(target, Nan::New("KEY_TUNER").ToLocalChecked(),
                Nan::New(KEY_TUNER));
    Nan::Set(target, Nan::New("KEY_PLAYER").ToLocalChecked(),
                Nan::New(KEY_PLAYER));
    Nan::Set(target, Nan::New("KEY_TEXT").ToLocalChecked(),
                Nan::New(KEY_TEXT));
    Nan::Set(target, Nan::New("KEY_DVD").ToLocalChecked(),
                Nan::New(KEY_DVD));
    Nan::Set(target, Nan::New("KEY_AUX").ToLocalChecked(),
                Nan::New(KEY_AUX));
    Nan::Set(target, Nan::New("KEY_MP3").ToLocalChecked(),
                Nan::New(KEY_MP3));
    Nan::Set(target, Nan::New("KEY_AUDIO").ToLocalChecked(),
                Nan::New(KEY_AUDIO));
    Nan::Set(target, Nan::New("KEY_VIDEO").ToLocalChecked(),
                Nan::New(KEY_VIDEO));
    Nan::Set(target, Nan::New("KEY_DIRECTORY").ToLocalChecked(),
                Nan::New(KEY_DIRECTORY));
    Nan::Set(target, Nan::New("KEY_LIST").ToLocalChecked(),
                Nan::New(KEY_LIST));
    Nan::Set(target, Nan::New("KEY_MEMO").ToLocalChecked(),
                Nan::New(KEY_MEMO));
    Nan::Set(target, Nan::New("KEY_CALENDAR").ToLocalChecked(),
                Nan::New(KEY_CALENDAR));
    Nan::Set(target, Nan::New("KEY_RED").ToLocalChecked(),
                Nan::New(KEY_RED));
    Nan::Set(target, Nan::New("KEY_GREEN").ToLocalChecked(),
                Nan::New(KEY_GREEN));
    Nan::Set(target, Nan::New("KEY_YELLOW").ToLocalChecked(),
                Nan::New(KEY_YELLOW));
    Nan::Set(target, Nan::New("KEY_BLUE").ToLocalChecked(),
                Nan::New(KEY_BLUE));
    Nan::Set(target, Nan::New("KEY_CHANNELUP").ToLocalChecked(),
                Nan::New(KEY_CHANNELUP));
    Nan::Set(target, Nan::New("KEY_CHANNELDOWN").ToLocalChecked(),
                Nan::New(KEY_CHANNELDOWN));
    Nan::Set(target, Nan::New("KEY_FIRST").ToLocalChecked(),
                Nan::New(KEY_FIRST));
    Nan::Set(target, Nan::New("KEY_LAST").ToLocalChecked(),
                Nan::New(KEY_LAST));
    Nan::Set(target, Nan::New("KEY_AB").ToLocalChecked(),
                Nan::New(KEY_AB));
    Nan::Set(target, Nan::New("KEY_NEXT").ToLocalChecked(),
                Nan::New(KEY_NEXT));
    Nan::Set(target, Nan::New("KEY_RESTART").ToLocalChecked(),
                Nan::New(KEY_RESTART));
    Nan::Set(target, Nan::New("KEY_SLOW").ToLocalChecked(),
                Nan::New(KEY_SLOW));
    Nan::Set(target, Nan::New("KEY_SHUFFLE").ToLocalChecked(),
                Nan::New(KEY_SHUFFLE));
    Nan::Set(target, Nan::New("KEY_BREAK").ToLocalChecked(),
                Nan::New(KEY_BREAK));
    Nan::Set(target, Nan::New("KEY_PREVIOUS").ToLocalChecked(),
                Nan::New(KEY_PREVIOUS));
    Nan::Set(target, Nan::New("KEY_DIGITS").ToLocalChecked(),
                Nan::New(KEY_DIGITS));
    Nan::Set(target, Nan::New("KEY_TEEN").ToLocalChecked(),
                Nan::New(KEY_TEEN));
    Nan::Set(target, Nan::New("KEY_TWEN").ToLocalChecked(),
                Nan::New(KEY_TWEN));
    Nan::Set(target, Nan::New("KEY_VIDEOPHONE").ToLocalChecked(),
                Nan::New(KEY_VIDEOPHONE));
    Nan::Set(target, Nan::New("KEY_GAMES").ToLocalChecked(),
                Nan::New(KEY_GAMES));
    Nan::Set(target, Nan::New("KEY_ZOOMIN").ToLocalChecked(),
                Nan::New(KEY_ZOOMIN));
    Nan::Set(target, Nan::New("KEY_ZOOMOUT").ToLocalChecked(),
                Nan::New(KEY_ZOOMOUT));
    Nan::Set(target, Nan::New("KEY_ZOOMRESET").ToLocalChecked(),
                Nan::New(KEY_ZOOMRESET));
    Nan::Set(target, Nan::New("KEY_WORDPROCESSOR").ToLocalChecked(),
                Nan::New(KEY_WORDPROCESSOR));
    Nan::Set(target, Nan::New("KEY_EDITOR").ToLocalChecked(),
                Nan::New(KEY_EDITOR));
    Nan::Set(target, Nan::New("KEY_SPREADSHEET").ToLocalChecked(),
                Nan::New(KEY_SPREADSHEET));
    Nan::Set(target, Nan::New("KEY_GRAPHICSEDITOR").ToLocalChecked(),
                Nan::New(KEY_GRAPHICSEDITOR));
    Nan::Set(target, Nan::New("KEY_PRESENTATION").ToLocalChecked(),
                Nan::New(KEY_PRESENTATION));
    Nan::Set(target, Nan::New("KEY_DATABASE").ToLocalChecked(),
                Nan::New(KEY_DATABASE));
    Nan::Set(target, Nan::New("KEY_NEWS").ToLocalChecked(),
                Nan::New(KEY_NEWS));
    Nan::Set(target, Nan::New("KEY_VOICEMAIL").ToLocalChecked(),
                Nan::New(KEY_VOICEMAIL));
    Nan::Set(target, Nan::New("KEY_ADDRESSBOOK").ToLocalChecked(),
                Nan::New(KEY_ADDRESSBOOK));
    Nan::Set(target, Nan::New("KEY_MESSENGER").ToLocalChecked(),
                Nan::New(KEY_MESSENGER));
    Nan::Set(target, Nan::New("KEY_DISPLAYTOGGLE").ToLocalChecked(),
                Nan::New(KEY_DISPLAYTOGGLE));
    Nan::Set(target, Nan::New("KEY_SPELLCHECK").ToLocalChecked(),
                Nan::New(KEY_SPELLCHECK));
    Nan::Set(target, Nan::New("KEY_LOGOFF").ToLocalChecked(),
                Nan::New(KEY_LOGOFF));
    Nan::Set(target, Nan::New("KEY_DOLLAR").ToLocalChecked(),
                Nan::New(KEY_DOLLAR));
    Nan::Set(target, Nan::New("KEY_EURO").ToLocalChecked(),
                Nan::New(KEY_EURO));
    Nan::Set(target, Nan::New("KEY_FRAMEBACK").ToLocalChecked(),
                Nan::New(KEY_FRAMEBACK));
    Nan::Set(target, Nan::New("KEY_FRAMEFORWARD").ToLocalChecked(),
                Nan::New(KEY_FRAMEFORWARD));
    Nan::Set(target, Nan::New("KEY_CONTEXT_MENU").ToLocalChecked(),
                Nan::New(KEY_CONTEXT_MENU));
    Nan::Set(target, Nan::New("KEY_MEDIA_REPEAT").ToLocalChecked(),
                Nan::New(KEY_MEDIA_REPEAT));
    Nan::Set(target, Nan::New("KEY_10CHANNELSUP").ToLocalChecked(),
                Nan::New(KEY_10CHANNELSUP));
    Nan::Set(target, Nan::New("KEY_10CHANNELSDOWN").ToLocalChecked(),
                Nan::New(KEY_10CHANNELSDOWN));
    Nan::Set(target, Nan::New("KEY_IMAGES").ToLocalChecked(),
                Nan::New(KEY_IMAGES));
    Nan::Set(target, Nan::New("KEY_DEL_EOL").ToLocalChecked(),
                Nan::New(KEY_DEL_EOL));
    Nan::Set(target, Nan::New("KEY_DEL_EOS").ToLocalChecked(),
                Nan::New(KEY_DEL_EOS));
    Nan::Set(target, Nan::New("KEY_INS_LINE").ToLocalChecked(),
                Nan::New(KEY_INS_LINE));
    Nan::Set(target, Nan::New("KEY_DEL_LINE").ToLocalChecked(),
                Nan::New(KEY_DEL_LINE));
    Nan::Set(target, Nan::New("KEY_FN").ToLocalChecked(),
                Nan::New(KEY_FN));
    Nan::Set(target, Nan::New("KEY_FN_ESC").ToLocalChecked(),
                Nan::New(KEY_FN_ESC));
    Nan::Set(target, Nan::New("KEY_FN_F1").ToLocalChecked(),
                Nan::New(KEY_FN_F1));
    Nan::Set(target, Nan::New("KEY_FN_F2").ToLocalChecked(),
                Nan::New(KEY_FN_F2));
    Nan::Set(target, Nan::New("KEY_FN_F3").ToLocalChecked(),
                Nan::New(KEY_FN_F3));
    Nan::Set(target, Nan::New("KEY_FN_F4").ToLocalChecked(),
                Nan::New(KEY_FN_F4));
    Nan::Set(target, Nan::New("KEY_FN_F5").ToLocalChecked(),
                Nan::New(KEY_FN_F5));
    Nan::Set(target, Nan::New("KEY_FN_F6").ToLocalChecked(),
                Nan::New(KEY_FN_F6));
    Nan::Set(target, Nan::New("KEY_FN_F7").ToLocalChecked(),
                Nan::New(KEY_FN_F7));
    Nan::Set(target, Nan::New("KEY_FN_F8").ToLocalChecked(),
                Nan::New(KEY_FN_F8));
    Nan::Set(target, Nan::New("KEY_FN_F9").ToLocalChecked(),
                Nan::New(KEY_FN_F9));
    Nan::Set(target, Nan::New("KEY_FN_F10").ToLocalChecked(),
                Nan::New(KEY_FN_F10));
    Nan::Set(target, Nan::New("KEY_FN_F11").ToLocalChecked(),
                Nan::New(KEY_FN_F11));
    Nan::Set(target, Nan::New("KEY_FN_F12").ToLocalChecked(),
                Nan::New(KEY_FN_F12));
    Nan::Set(target, Nan::New("KEY_FN_1").ToLocalChecked(),
                Nan::New(KEY_FN_1));
    Nan::Set(target, Nan::New("KEY_FN_2").ToLocalChecked(),
                Nan::New(KEY_FN_2));
    Nan::Set(target, Nan::New("KEY_FN_D").ToLocalChecked(),
                Nan::New(KEY_FN_D));
    Nan::Set(target, Nan::New("KEY_FN_E").ToLocalChecked(),
                Nan::New(KEY_FN_E));
    Nan::Set(target, Nan::New("KEY_FN_F").ToLocalChecked(),
                Nan::New(KEY_FN_F));
    Nan::Set(target, Nan::New("KEY_FN_S").ToLocalChecked(),
                Nan::New(KEY_FN_S));
    Nan::Set(target, Nan::New("KEY_FN_B").ToLocalChecked(),
                Nan::New(KEY_FN_B));
    Nan::Set(target, Nan::New("KEY_BRL_DOT1").ToLocalChecked(),
                Nan::New(KEY_BRL_DOT1));
    Nan::Set(target, Nan::New("KEY_BRL_DOT2").ToLocalChecked(),
                Nan::New(KEY_BRL_DOT2));
    Nan::Set(target, Nan::New("KEY_BRL_DOT3").ToLocalChecked(),
                Nan::New(KEY_BRL_DOT3));
    Nan::Set(target, Nan::New("KEY_BRL_DOT4").ToLocalChecked(),
                Nan::New(KEY_BRL_DOT4));
    Nan::Set(target, Nan::New("KEY_BRL_DOT5").ToLocalChecked(),
                Nan::New(KEY_BRL_DOT5));
    Nan::Set(target, Nan::New("KEY_BRL_DOT6").ToLocalChecked(),
                Nan::New(KEY_BRL_DOT6));
    Nan::Set(target, Nan::New("KEY_BRL_DOT7").ToLocalChecked(),
                Nan::New(KEY_BRL_DOT7));
    Nan::Set(target, Nan::New("KEY_BRL_DOT8").ToLocalChecked(),
                Nan::New(KEY_BRL_DOT8));
    Nan::Set(target, Nan::New("KEY_BRL_DOT9").ToLocalChecked(),
                Nan::New(KEY_BRL_DOT9));
    Nan::Set(target, Nan::New("KEY_BRL_DOT10").ToLocalChecked(),
                Nan::New(KEY_BRL_DOT10));
    Nan::Set(target, Nan::New("KEY_NUMERIC_0").ToLocalChecked(),
                Nan::New(KEY_NUMERIC_0));
    Nan::Set(target, Nan::New("KEY_NUMERIC_1").ToLocalChecked(),
                Nan::New(KEY_NUMERIC_1));
    Nan::Set(target, Nan::New("KEY_NUMERIC_2").ToLocalChecked(),
                Nan::New(KEY_NUMERIC_2));
    Nan::Set(target, Nan::New("KEY_NUMERIC_3").ToLocalChecked(),
                Nan::New(KEY_NUMERIC_3));
    Nan::Set(target, Nan::New("KEY_NUMERIC_4").ToLocalChecked(),
                Nan::New(KEY_NUMERIC_4));
    Nan::Set(target, Nan::New("KEY_NUMERIC_5").ToLocalChecked(),
                Nan::New(KEY_NUMERIC_5));
    Nan::Set(target, Nan::New("KEY_NUMERIC_6").ToLocalChecked(),
                Nan::New(KEY_NUMERIC_6));
    Nan::Set(target, Nan::New("KEY_NUMERIC_7").ToLocalChecked(),
                Nan::New(KEY_NUMERIC_7));
    Nan::Set(target, Nan::New("KEY_NUMERIC_8").ToLocalChecked(),
                Nan::New(KEY_NUMERIC_8));
    Nan::Set(target, Nan::New("KEY_NUMERIC_9").ToLocalChecked(),
                Nan::New(KEY_NUMERIC_9));
    Nan::Set(target, Nan::New("KEY_NUMERIC_STAR").ToLocalChecked(),
                Nan::New(KEY_NUMERIC_STAR));
    Nan::Set(target, Nan::New("KEY_NUMERIC_POUND").ToLocalChecked(),
                Nan::New(KEY_NUMERIC_POUND));
    Nan::Set(target, Nan::New("KEY_CAMERA_FOCUS").ToLocalChecked(),
                Nan::New(KEY_CAMERA_FOCUS));
    Nan::Set(target, Nan::New("KEY_WPS_BUTTON").ToLocalChecked(),
                Nan::New(KEY_WPS_BUTTON));
    Nan::Set(target, Nan::New("KEY_TOUCHPAD_TOGGLE").ToLocalChecked(),
                Nan::New(KEY_TOUCHPAD_TOGGLE));
    Nan::Set(target, Nan::New("KEY_TOUCHPAD_ON").ToLocalChecked(),
                Nan::New(KEY_TOUCHPAD_ON));
    Nan::Set(target, Nan::New("KEY_TOUCHPAD_OFF").ToLocalChecked(),
                Nan::New(KEY_TOUCHPAD_OFF));
    Nan::Set(target, Nan::New("KEY_CAMERA_ZOOMIN").ToLocalChecked(),
                Nan::New(KEY_CAMERA_ZOOMIN));
    Nan::Set(target, Nan::New("KEY_CAMERA_ZOOMOUT").ToLocalChecked(),
                Nan::New(KEY_CAMERA_ZOOMOUT));
    Nan::Set(target, Nan::New("KEY_CAMERA_UP").ToLocalChecked(),
                Nan::New(KEY_CAMERA_UP));
    Nan::Set(target, Nan::New("KEY_CAMERA_DOWN").ToLocalChecked(),
                Nan::New(KEY_CAMERA_DOWN));
    Nan::Set(target, Nan::New("KEY_CAMERA_LEFT").ToLocalChecked(),
                Nan::New(KEY_CAMERA_LEFT));
    Nan::Set(target, Nan::New("KEY_CAMERA_RIGHT").ToLocalChecked(),
                Nan::New(KEY_CAMERA_RIGHT));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY1").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY1));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY2").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY2));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY3").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY3));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY4").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY4));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY5").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY5));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY6").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY6));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY7").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY7));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY8").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY8));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY9").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY9));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY10").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY10));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY11").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY11));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY12").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY12));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY13").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY13));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY14").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY14));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY15").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY15));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY16").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY16));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY17").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY17));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY18").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY18));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY19").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY19));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY20").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY20));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY21").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY21));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY22").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY22));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY23").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY23));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY24").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY24));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY25").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY25));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY26").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY26));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY27").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY27));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY28").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY28));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY29").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY29));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY30").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY30));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY31").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY31));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY32").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY32));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY33").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY33));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY34").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY34));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY35").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY35));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY36").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY36));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY37").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY37));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY38").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY38));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY39").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY39));
    Nan::Set(target, Nan::New("BTN_TRIGGER_HAPPY40").ToLocalChecked(),
                Nan::New(BTN_TRIGGER_HAPPY40));
    Nan::Set(target, Nan::New("KEY_MIN_INTERESTING").ToLocalChecked(),
                Nan::New(KEY_MIN_INTERESTING));
    Nan::Set(target, Nan::New("KEY_MAX").ToLocalChecked(),
                Nan::New(KEY_MAX));
    Nan::Set(target, Nan::New("KEY_CNT").ToLocalChecked(),
                Nan::New(KEY_CNT));
    Nan::Set(target, Nan::New("REL_X").ToLocalChecked(),
                Nan::New(REL_X));
    Nan::Set(target, Nan::New("REL_Y").ToLocalChecked(),
                Nan::New(REL_Y));
    Nan::Set(target, Nan::New("REL_Z").ToLocalChecked(),
                Nan::New(REL_Z));
    Nan::Set(target, Nan::New("REL_RX").ToLocalChecked(),
                Nan::New(REL_RX));
    Nan::Set(target, Nan::New("REL_RY").ToLocalChecked(),
                Nan::New(REL_RY));
    Nan::Set(target, Nan::New("REL_RZ").ToLocalChecked(),
                Nan::New(REL_RZ));
    Nan::Set(target, Nan::New("REL_HWHEEL").ToLocalChecked(),
                Nan::New(REL_HWHEEL));
    Nan::Set(target, Nan::New("REL_DIAL").ToLocalChecked(),
                Nan::New(REL_DIAL));
    Nan::Set(target, Nan::New("REL_WHEEL").ToLocalChecked(),
                Nan::New(REL_WHEEL));
    Nan::Set(target, Nan::New("REL_MISC").ToLocalChecked(),
                Nan::New(REL_MISC));
    Nan::Set(target, Nan::New("REL_MAX").ToLocalChecked(),
                Nan::New(REL_MAX));
    Nan::Set(target, Nan::New("REL_CNT").ToLocalChecked(),
                Nan::New(REL_CNT));
    Nan::Set(target, Nan::New("ABS_X").ToLocalChecked(),
                Nan::New(ABS_X));
    Nan::Set(target, Nan::New("ABS_Y").ToLocalChecked(),
                Nan::New(ABS_Y));
    Nan::Set(target, Nan::New("ABS_Z").ToLocalChecked(),
                Nan::New(ABS_Z));
    Nan::Set(target, Nan::New("ABS_RX").ToLocalChecked(),
                Nan::New(ABS_RX));
    Nan::Set(target, Nan::New("ABS_RY").ToLocalChecked(),
                Nan::New(ABS_RY));
    Nan::Set(target, Nan::New("ABS_RZ").ToLocalChecked(),
                Nan::New(ABS_RZ));
    Nan::Set(target, Nan::New("ABS_THROTTLE").ToLocalChecked(),
                Nan::New(ABS_THROTTLE));
    Nan::Set(target, Nan::New("ABS_RUDDER").ToLocalChecked(),
                Nan::New(ABS_RUDDER));
    Nan::Set(target, Nan::New("ABS_WHEEL").ToLocalChecked(),
                Nan::New(ABS_WHEEL));
    Nan::Set(target, Nan::New("ABS_GAS").ToLocalChecked(),
                Nan::New(ABS_GAS));
    Nan::Set(target, Nan::New("ABS_BRAKE").ToLocalChecked(),
                Nan::New(ABS_BRAKE));
    Nan::Set(target, Nan::New("ABS_HAT0X").ToLocalChecked(),
                Nan::New(ABS_HAT0X));
    Nan::Set(target, Nan::New("ABS_HAT0Y").ToLocalChecked(),
                Nan::New(ABS_HAT0Y));
    Nan::Set(target, Nan::New("ABS_HAT1X").ToLocalChecked(),
                Nan::New(ABS_HAT1X));
    Nan::Set(target, Nan::New("ABS_HAT1Y").ToLocalChecked(),
                Nan::New(ABS_HAT1Y));
    Nan::Set(target, Nan::New("ABS_HAT2X").ToLocalChecked(),
                Nan::New(ABS_HAT2X));
    Nan::Set(target, Nan::New("ABS_HAT2Y").ToLocalChecked(),
                Nan::New(ABS_HAT2Y));
    Nan::Set(target, Nan::New("ABS_HAT3X").ToLocalChecked(),
                Nan::New(ABS_HAT3X));
    Nan::Set(target, Nan::New("ABS_HAT3Y").ToLocalChecked(),
                Nan::New(ABS_HAT3Y));
    Nan::Set(target, Nan::New("ABS_PRESSURE").ToLocalChecked(),
                Nan::New(ABS_PRESSURE));
    Nan::Set(target, Nan::New("ABS_DISTANCE").ToLocalChecked(),
                Nan::New(ABS_DISTANCE));
    Nan::Set(target, Nan::New("ABS_TILT_X").ToLocalChecked(),
                Nan::New(ABS_TILT_X));
    Nan::Set(target, Nan::New("ABS_TILT_Y").ToLocalChecked(),
                Nan::New(ABS_TILT_Y));
    Nan::Set(target, Nan::New("ABS_TOOL_WIDTH").ToLocalChecked(),
                Nan::New(ABS_TOOL_WIDTH));
    Nan::Set(target, Nan::New("ABS_VOLUME").ToLocalChecked(),
                Nan::New(ABS_VOLUME));
    Nan::Set(target, Nan::New("ABS_MISC").ToLocalChecked(),
                Nan::New(ABS_MISC));
    Nan::Set(target, Nan::New("ABS_MT_SLOT").ToLocalChecked(),
                Nan::New(ABS_MT_SLOT));
    Nan::Set(target, Nan::New("ABS_MT_TOUCH_MAJOR").ToLocalChecked(),
                Nan::New(ABS_MT_TOUCH_MAJOR));
    Nan::Set(target, Nan::New("ABS_MT_TOUCH_MINOR").ToLocalChecked(),
                Nan::New(ABS_MT_TOUCH_MINOR));
    Nan::Set(target, Nan::New("ABS_MT_WIDTH_MAJOR").ToLocalChecked(),
                Nan::New(ABS_MT_WIDTH_MAJOR));
    Nan::Set(target, Nan::New("ABS_MT_WIDTH_MINOR").ToLocalChecked(),
                Nan::New(ABS_MT_WIDTH_MINOR));
    Nan::Set(target, Nan::New("ABS_MT_ORIENTATION").ToLocalChecked(),
                Nan::New(ABS_MT_ORIENTATION));
    Nan::Set(target, Nan::New("ABS_MT_POSITION_X").ToLocalChecked(),
                Nan::New(ABS_MT_POSITION_X));
    Nan::Set(target, Nan::New("ABS_MT_POSITION_Y").ToLocalChecked(),
                Nan::New(ABS_MT_POSITION_Y));
    Nan::Set(target, Nan::New("ABS_MT_TOOL_TYPE").ToLocalChecked(),
                Nan::New(ABS_MT_TOOL_TYPE));
    Nan::Set(target, Nan::New("ABS_MT_BLOB_ID").ToLocalChecked(),
                Nan::New(ABS_MT_BLOB_ID));
    Nan::Set(target, Nan::New("ABS_MT_TRACKING_ID").ToLocalChecked(),
                Nan::New(ABS_MT_TRACKING_ID));
    Nan::Set(target, Nan::New("ABS_MT_PRESSURE").ToLocalChecked(),
                Nan::New(ABS_MT_PRESSURE));
    Nan::Set(target, Nan::New("ABS_MT_DISTANCE").ToLocalChecked(),
                Nan::New(ABS_MT_DISTANCE));
    Nan::Set(target, Nan::New("ABS_MAX").ToLocalChecked(),
                Nan::New(ABS_MAX));
    Nan::Set(target, Nan::New("ABS_CNT").ToLocalChecked(),
                Nan::New(ABS_CNT));
    Nan::Set(target, Nan::New("SW_LID").ToLocalChecked(),
                Nan::New(SW_LID));
    Nan::Set(target, Nan::New("SW_TABLET_MODE").ToLocalChecked(),
                Nan::New(SW_TABLET_MODE));
    Nan::Set(target, Nan::New("SW_HEADPHONE_INSERT").ToLocalChecked(),
                Nan::New(SW_HEADPHONE_INSERT));
    Nan::Set(target, Nan::New("SW_RFKILL_ALL").ToLocalChecked(),
                Nan::New(SW_RFKILL_ALL));
    Nan::Set(target, Nan::New("SW_RADIO").ToLocalChecked(),
                Nan::New(SW_RADIO));
    Nan::Set(target, Nan::New("SW_MICROPHONE_INSERT").ToLocalChecked(),
                Nan::New(SW_MICROPHONE_INSERT));
    Nan::Set(target, Nan::New("SW_DOCK").ToLocalChecked(),
                Nan::New(SW_DOCK));
    Nan::Set(target, Nan::New("SW_LINEOUT_INSERT").ToLocalChecked(),
                Nan::New(SW_LINEOUT_INSERT));
    Nan::Set(target, Nan::New("SW_JACK_PHYSICAL_INSERT").ToLocalChecked(),
                Nan::New(SW_JACK_PHYSICAL_INSERT));
    Nan::Set(target, Nan::New("SW_VIDEOOUT_INSERT").ToLocalChecked(),
                Nan::New(SW_VIDEOOUT_INSERT));
    Nan::Set(target, Nan::New("SW_CAMERA_LENS_COVER").ToLocalChecked(),
                Nan::New(SW_CAMERA_LENS_COVER));
    Nan::Set(target, Nan::New("SW_KEYPAD_SLIDE").ToLocalChecked(),
                Nan::New(SW_KEYPAD_SLIDE));
    Nan::Set(target, Nan::New("SW_FRONT_PROXIMITY").ToLocalChecked(),
                Nan::New(SW_FRONT_PROXIMITY));
    Nan::Set(target, Nan::New("SW_ROTATE_LOCK").ToLocalChecked(),
                Nan::New(SW_ROTATE_LOCK));
    Nan::Set(target, Nan::New("SW_LINEIN_INSERT").ToLocalChecked(),
                Nan::New(SW_LINEIN_INSERT));
    Nan::Set(target, Nan::New("SW_MAX").ToLocalChecked(),
                Nan::New(SW_MAX));
    Nan::Set(target, Nan::New("SW_CNT").ToLocalChecked(),
                Nan::New(SW_CNT));
    Nan::Set(target, Nan::New("MSC_SERIAL").ToLocalChecked(),
                Nan::New(MSC_SERIAL));
    Nan::Set(target, Nan::New("MSC_PULSELED").ToLocalChecked(),
                Nan::New(MSC_PULSELED));
    Nan::Set(target, Nan::New("MSC_GESTURE").ToLocalChecked(),
                Nan::New(MSC_GESTURE));
    Nan::Set(target, Nan::New("MSC_RAW").ToLocalChecked(),
                Nan::New(MSC_RAW));
    Nan::Set(target, Nan::New("MSC_SCAN").ToLocalChecked(),
                Nan::New(MSC_SCAN));
    Nan::Set(target, Nan::New("MSC_MAX").ToLocalChecked(),
                Nan::New(MSC_MAX));
    Nan::Set(target, Nan::New("MSC_CNT").ToLocalChecked(),
                Nan::New(MSC_CNT));
    Nan::Set(target, Nan::New("LED_NUML").ToLocalChecked(),
                Nan::New(LED_NUML));
    Nan::Set(target, Nan::New("LED_CAPSL").ToLocalChecked(),
                Nan::New(LED_CAPSL));
    Nan::Set(target, Nan::New("LED_SCROLLL").ToLocalChecked(),
                Nan::New(LED_SCROLLL));
    Nan::Set(target, Nan::New("LED_COMPOSE").ToLocalChecked(),
                Nan::New(LED_COMPOSE));
    Nan::Set(target, Nan::New("LED_KANA").ToLocalChecked(),
                Nan::New(LED_KANA));
    Nan::Set(target, Nan::New("LED_SLEEP").ToLocalChecked(),
                Nan::New(LED_SLEEP));
    Nan::Set(target, Nan::New("LED_SUSPEND").ToLocalChecked(),
                Nan::New(LED_SUSPEND));
    Nan::Set(target, Nan::New("LED_MUTE").ToLocalChecked(),
                Nan::New(LED_MUTE));
    Nan::Set(target, Nan::New("LED_MISC").ToLocalChecked(),
                Nan::New(LED_MISC));
    Nan::Set(target, Nan::New("LED_MAIL").ToLocalChecked(),
                Nan::New(LED_MAIL));
    Nan::Set(target, Nan::New("LED_CHARGING").ToLocalChecked(),
                Nan::New(LED_CHARGING));
    Nan::Set(target, Nan::New("LED_MAX").ToLocalChecked(),
                Nan::New(LED_MAX));
    Nan::Set(target, Nan::New("LED_CNT").ToLocalChecked(),
                Nan::New(LED_CNT));
    Nan::Set(target, Nan::New("REP_DELAY").ToLocalChecked(),
                Nan::New(REP_DELAY));
    Nan::Set(target, Nan::New("REP_PERIOD").ToLocalChecked(),
                Nan::New(REP_PERIOD));
    Nan::Set(target, Nan::New("REP_MAX").ToLocalChecked(),
                Nan::New(REP_MAX));
    Nan::Set(target, Nan::New("REP_CNT").ToLocalChecked(),
                Nan::New(REP_CNT));
    Nan::Set(target, Nan::New("SND_CLICK").ToLocalChecked(),
                Nan::New(SND_CLICK));
    Nan::Set(target, Nan::New("SND_BELL").ToLocalChecked(),
                Nan::New(SND_BELL));
    Nan::Set(target, Nan::New("SND_TONE").ToLocalChecked(),
                Nan::New(SND_TONE));
    Nan::Set(target, Nan::New("SND_MAX").ToLocalChecked(),
                Nan::New(SND_MAX));
    Nan::Set(target, Nan::New("SND_CNT").ToLocalChecked(),
                Nan::New(SND_CNT));
    Nan::Set(target, Nan::New("ID_BUS").ToLocalChecked(),
                Nan::New(ID_BUS));
    Nan::Set(target, Nan::New("ID_VENDOR").ToLocalChecked(),
                Nan::New(ID_VENDOR));
    Nan::Set(target, Nan::New("ID_PRODUCT").ToLocalChecked(),
                Nan::New(ID_PRODUCT));
    Nan::Set(target, Nan::New("ID_VERSION").ToLocalChecked(),
                Nan::New(ID_VERSION));
    Nan::Set(target, Nan::New("BUS_PCI").ToLocalChecked(),
                Nan::New(BUS_PCI));
    Nan::Set(target, Nan::New("BUS_ISAPNP").ToLocalChecked(),
                Nan::New(BUS_ISAPNP));
    Nan::Set(target, Nan::New("BUS_USB").ToLocalChecked(),
                Nan::New(BUS_USB));
    Nan::Set(target, Nan::New("BUS_HIL").ToLocalChecked(),
                Nan::New(BUS_HIL));
    Nan::Set(target, Nan::New("BUS_BLUETOOTH").ToLocalChecked(),
                Nan::New(BUS_BLUETOOTH));
    Nan::Set(target, Nan::New("BUS_VIRTUAL").ToLocalChecked(),
                Nan::New(BUS_VIRTUAL));
    Nan::Set(target, Nan::New("BUS_ISA").ToLocalChecked(),
                Nan::New(BUS_ISA));
    Nan::Set(target, Nan::New("BUS_I8042").ToLocalChecked(),
                Nan::New(BUS_I8042));
    Nan::Set(target, Nan::New("BUS_XTKBD").ToLocalChecked(),
                Nan::New(BUS_XTKBD));
    Nan::Set(target, Nan::New("BUS_RS232").ToLocalChecked(),
                Nan::New(BUS_RS232));
    Nan::Set(target, Nan::New("BUS_GAMEPORT").ToLocalChecked(),
                Nan::New(BUS_GAMEPORT));
    Nan::Set(target, Nan::New("BUS_PARPORT").ToLocalChecked(),
                Nan::New(BUS_PARPORT));
    Nan::Set(target, Nan::New("BUS_AMIGA").ToLocalChecked(),
                Nan::New(BUS_AMIGA));
    Nan::Set(target, Nan::New("BUS_ADB").ToLocalChecked(),
                Nan::New(BUS_ADB));
    Nan::Set(target, Nan::New("BUS_I2C").ToLocalChecked(),
                Nan::New(BUS_I2C));
    Nan::Set(target, Nan::New("BUS_HOST").ToLocalChecked(),
                Nan::New(BUS_HOST));
    Nan::Set(target, Nan::New("BUS_GSC").ToLocalChecked(),
                Nan::New(BUS_GSC));
    Nan::Set(target, Nan::New("BUS_ATARI").ToLocalChecked(),
                Nan::New(BUS_ATARI));
    Nan::Set(target, Nan::New("BUS_SPI").ToLocalChecked(),
                Nan::New(BUS_SPI));
    Nan::Set(target, Nan::New("MT_TOOL_FINGER").ToLocalChecked(),
                Nan::New(MT_TOOL_FINGER));
    Nan::Set(target, Nan::New("MT_TOOL_PEN").ToLocalChecked(),
                Nan::New(MT_TOOL_PEN));
    Nan::Set(target, Nan::New("MT_TOOL_MAX").ToLocalChecked(),
                Nan::New(MT_TOOL_MAX));
    Nan::Set(target, Nan::New("FF_STATUS_STOPPED").ToLocalChecked(),
                Nan::New(FF_STATUS_STOPPED));
    Nan::Set(target, Nan::New("FF_STATUS_PLAYING").ToLocalChecked(),
                Nan::New(FF_STATUS_PLAYING));
    Nan::Set(target, Nan::New("FF_STATUS_MAX").ToLocalChecked(),
                Nan::New(FF_STATUS_MAX));
    Nan::Set(target, Nan::New("FF_RUMBLE").ToLocalChecked(),
                Nan::New(FF_RUMBLE));
    Nan::Set(target, Nan::New("FF_PERIODIC").ToLocalChecked(),
                Nan::New(FF_PERIODIC));
    Nan::Set(target, Nan::New("FF_CONSTANT").ToLocalChecked(),
                Nan::New(FF_CONSTANT));
    Nan::Set(target, Nan::New("FF_SPRING").ToLocalChecked(),
                Nan::New(FF_SPRING));
    Nan::Set(target, Nan::New("FF_FRICTION").ToLocalChecked(),
                Nan::New(FF_FRICTION));
    Nan::Set(target, Nan::New("FF_DAMPER").ToLocalChecked(),
                Nan::New(FF_DAMPER));
    Nan::Set(target, Nan::New("FF_INERTIA").ToLocalChecked(),
                Nan::New(FF_INERTIA));
    Nan::Set(target, Nan::New("FF_RAMP").ToLocalChecked(),
                Nan::New(FF_RAMP));
    Nan::Set(target, Nan::New("FF_EFFECT_MIN").ToLocalChecked(),
                Nan::New(FF_EFFECT_MIN));
    Nan::Set(target, Nan::New("FF_EFFECT_MAX").ToLocalChecked(),
                Nan::New(FF_EFFECT_MAX));
    Nan::Set(target, Nan::New("FF_SQUARE").ToLocalChecked(),
                Nan::New(FF_SQUARE));
    Nan::Set(target, Nan::New("FF_TRIANGLE").ToLocalChecked(),
                Nan::New(FF_TRIANGLE));
    Nan::Set(target, Nan::New("FF_SINE").ToLocalChecked(),
                Nan::New(FF_SINE));
    Nan::Set(target, Nan::New("FF_SAW_UP").ToLocalChecked(),
                Nan::New(FF_SAW_UP));
    Nan::Set(target, Nan::New("FF_SAW_DOWN").ToLocalChecked(),
                Nan::New(FF_SAW_DOWN));
    Nan::Set(target, Nan::New("FF_CUSTOM").ToLocalChecked(),
                Nan::New(FF_CUSTOM));
    Nan::Set(target, Nan::New("FF_WAVEFORM_MIN").ToLocalChecked(),
                Nan::New(FF_WAVEFORM_MIN));
    Nan::Set(target, Nan::New("FF_WAVEFORM_MAX").ToLocalChecked(),
                Nan::New(FF_WAVEFORM_MAX));
    Nan::Set(target, Nan::New("FF_GAIN").ToLocalChecked(),
                Nan::New(FF_GAIN));
    Nan::Set(target, Nan::New("FF_AUTOCENTER").ToLocalChecked(),
                Nan::New(FF_AUTOCENTER));
    Nan::Set(target, Nan::New("FF_MAX").ToLocalChecked(),
                Nan::New(FF_MAX));
    Nan::Set(target, Nan::New("FF_CNT").ToLocalChecked(),
                Nan::New(FF_CNT));

    /* uinput.h */
    Nan::Set(target, Nan::New("UI_DEV_CREATE").ToLocalChecked(),
                Nan::New(UI_DEV_CREATE));
    Nan::Set(target, Nan::New("UI_DEV_DESTROY").ToLocalChecked(),
                Nan::New(UI_DEV_DESTROY));
    Nan::Set(target, Nan::New("UI_SET_EVBIT").ToLocalChecked(),
                Nan::New(static_cast<uint32_t>(UI_SET_EVBIT)));
    Nan::Set(target, Nan::New("UI_SET_KEYBIT").ToLocalChecked(),
                Nan::New(static_cast<uint32_t>(UI_SET_KEYBIT)));
    Nan::Set(target, Nan::New("UI_SET_RELBIT").ToLocalChecked(),
                Nan::New(static_cast<uint32_t>(UI_SET_RELBIT)));
    Nan::Set(target, Nan::New("UI_SET_ABSBIT").ToLocalChecked(),
                Nan::New(static_cast<uint32_t>(UI_SET_ABSBIT)));
    Nan::Set(target, Nan::New("UI_SET_MSCBIT").ToLocalChecked(),
                Nan::New(static_cast<uint32_t>(UI_SET_MSCBIT)));
    Nan::Set(target, Nan::New("UI_SET_LEDBIT").ToLocalChecked(),
                Nan::New(static_cast<uint32_t>(UI_SET_LEDBIT)));
    Nan::Set(target, Nan::New("UI_SET_SNDBIT").ToLocalChecked(),
                Nan::New(static_cast<uint32_t>(UI_SET_SNDBIT)));
    Nan::Set(target, Nan::New("UI_SET_FFBIT").ToLocalChecked(),
                Nan::New(static_cast<uint32_t>(UI_SET_FFBIT)));
    Nan::Set(target, Nan::New("UI_SET_PHYS").ToLocalChecked(),
                Nan::New(static_cast<uint32_t>(UI_SET_PHYS)));
    Nan::Set(target, Nan::New("UI_SET_SWBIT").ToLocalChecked(),
                Nan::New(static_cast<uint32_t>(UI_SET_SWBIT)));
    Nan::Set(target, Nan::New("UI_SET_PROPBIT").ToLocalChecked(),
                Nan::New(static_cast<uint32_t>(UI_SET_PROPBIT)));
    Nan::Set(target, Nan::New("UI_BEGIN_FF_UPLOAD").ToLocalChecked(),
                Nan::New(static_cast<uint32_t>(UI_BEGIN_FF_UPLOAD)));
    Nan::Set(target, Nan::New("UI_END_FF_UPLOAD").ToLocalChecked(),
                Nan::New(static_cast<uint32_t>(UI_END_FF_UPLOAD)));
    Nan::Set(target, Nan::New("UI_BEGIN_FF_ERASE").ToLocalChecked(),
                Nan::New(static_cast<uint32_t>(UI_BEGIN_FF_ERASE)));
    Nan::Set(target, Nan::New("UI_END_FF_ERASE").ToLocalChecked(),
                Nan::New(static_cast<uint32_t>(UI_END_FF_ERASE)));
    Nan::Set(target, Nan::New("EV_UINPUT").ToLocalChecked(),
                Nan::New(EV_UINPUT));
    Nan::Set(target, Nan::New("UI_FF_UPLOAD").ToLocalChecked(),
                Nan::New(UI_FF_UPLOAD));
    Nan::Set(target, Nan::New("UI_FF_ERASE").ToLocalChecked(),
                Nan::New(UI_FF_ERASE));
    Nan::Set(target, Nan::New("UINPUT_MAX_NAME_SIZE").ToLocalChecked(),
                Nan::New(UINPUT_MAX_NAME_SIZE));
}
}

NODE_MODULE(uinput, Initialize)
