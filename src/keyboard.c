#include <device.h>
#include <devicetree.h>
#include <stdint.h>
#include <usb/class/hid.h>
#include <usb/class/usb_hid.h>
#include <usb/usb_device.h>
#include <zephyr.h>

static const uint8_t hid_report_desc[] = HID_KEYBOARD_REPORT_DESC();
const struct device *hid_dev;
static bool configured;
static uint8_t previous_keycodes[6] = {0, 0, 0, 0, 0, 0};
static uint8_t previous_modifiers = 0;
static K_SEM_DEFINE(hid_sem, 1, 1);

static void int_in_ready_cb(const struct device *dev) {
  ARG_UNUSED(dev);
  // if (!atomic_test_and_clear_bit(hid_ep_in_busy, HID_EP_BUSY_FLAG)) {
  // }
}

/*
 * On Idle callback is available here as an example even if actual use is
 * very limited. In contrast to report_event_handler(),
 * report value is not incremented here.
 */
static void on_idle_cb(const struct device *dev, uint16_t report_id) {}

static void protocol_cb(const struct device *dev, uint8_t protocol) {}

static const struct hid_ops ops = {
    .int_in_ready = int_in_ready_cb,
    .on_idle = on_idle_cb,
    .protocol_change = protocol_cb,
};

static void status_cb(enum usb_dc_status_code status, const uint8_t *param) {
  switch (status) {
  case USB_DC_RESET:
    configured = false;
    break;
  case USB_DC_CONFIGURED:
    if (!configured) {
      int_in_ready_cb(hid_dev);
      configured = true;
    }
    break;
  case USB_DC_SOF:
    break;
  default:
    break;
  }
}

int keyboard_init() {
  hid_dev = device_get_binding("HID_0");
  usb_hid_register_device(hid_dev, hid_report_desc, sizeof hid_report_desc,
                          &ops);
  usb_hid_set_proto_code(hid_dev, HID_BOOT_IFACE_CODE_KEYBOARD);
  usb_hid_init(hid_dev);
  return usb_enable(status_cb);
}

bool is_unchanged(uint8_t keycodes[6], uint8_t modifiers) {
  int i;
  for (i = 0; i < 6; i++) {
    if (keycodes[i] != previous_keycodes[i]) {
      return false;
    };
  }
  return modifiers == previous_modifiers;
}

void store_keycodes(uint8_t keycodes[6]) {
  int i;
  for (i = 0; i < 6; i++) {
    previous_keycodes[i] = keycodes[i];
  }
}

void keyboard_send(uint8_t keycodes[6], uint8_t modifiers) {
  // probably a better way of doing this with memcmp
  if (is_unchanged(keycodes, modifiers)) {
    return;
  }

  uint8_t report[8];
  report[0] = modifiers;
  report[1] = 0x00;
  int i;
  for (i = 0; i < 6; i++) {
    report[i + 2] = keycodes[i];
  }

  k_sem_take(&hid_sem, K_MSEC(30));
  int err = hid_int_ep_write(hid_dev, report, sizeof report, NULL);

  if (err) {
    k_sem_give(&hid_sem);
    return;
  }

  // probably a better way of doing this with memcpy
  store_keycodes(keycodes);
  previous_modifiers = modifiers;
}

SYS_INIT(keyboard_init, APPLICATION, CONFIG_KERNEL_INIT_PRIORITY_DEVICE);
