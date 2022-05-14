var HID = require('node-hid');
const vid = 1133
const pid = 49277

let devices = HID.devices()

console.log(devices)

if (devices.filter((o) => o.vendorId === vid && o.productId === pid).length) {
    console.log('Kyria connected')
    
    let device = new HID.HID('/dev/hidraw3')
    console.log(device)

    device.write(Buffer.from('Hello world', "utf-8"))

    device.close()
}
