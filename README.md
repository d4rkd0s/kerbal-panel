# kerbal-panel
A collection of code to run external buttons/switches/lights on an Arduino for use with Kerbal Space Program

## Requirements

- At least an Arduino Leonardo for USB-HID keyboard emulation support

https://www.amazon.com/Arduino-org-A000057-Arduino-Leonardo-Headers/dp/B008A36R2Y/ref=sr_1_3?s=electronics&ie=UTF8&qid=1491265710&sr=1-3&keywords=arduino+leonardo

- Any PC to flash arduino code to board
- Micro USB if you are using Leonardo


## Kerbal Abort Button

The kerbal abort button is the easiest one in the collection and can be used with any button and light. We used a button with a light in it.

### Kerbal Button Requirements

- 1 button normally open (2 pins)
- 1 LED light (2 pins)

![KSP Abort Button](/ksp_abort_button/ksp_abort_button.gif?raw=true "KSP Abort Button")


### Kerbal Panel Requirements

- 5 buttons normally open with lights (4 pins each)
- 1 joystick (4 switches normally open) (2 pins each switch)

## Kerbal Panel

The kerbal panel is a joystick with 4 normally open switched and 5 buttons with lights in them.

![KSP Panel](/ksp_panel/ksp_panel.jpg?raw=true "KSP Panel")
