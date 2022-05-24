# Input System
Cleo's input system has been designed to be adaptable enough for just about any game and almost any keyboard or gamepad. Touch and gyro events are not currently supported.

## Overview

In your project's `input.json` file you'll define the bindings your game will use. 

### User Profiles
The top level of this json is an object where the keys correspond to user profiles. At least a default profile should be provided. Users should not be able to edit this default profile.

### Modes
Often games have various modes of interaction. It makes sense to separate menu interactions from regular gameplay. If your has vehicles with different controls than the regular gameplay input modes are a good way to segment them.

### Virtual Inputs
Virtual inputs are a high level abstraction that your game logic can hook into ergonomically. Ideally the gameplay designer won't have to worry whether a player is using a keyboard, a gamepad, or some other device. Sometimes the differences between input modes are too great and the designer will have to worry about whether the player is using a mouse but for most situations this can be avoided.

There are only three types of virtual inputs

- button, a binary input that reports its state and whether it was pressed or released this tick.
- axis1d, a one dimensional axis with an `x` component and various filtering modes.
- axis2d, a two dimensional axis with an `x` and `y` component and various filtering modes.

### Physical Inputs
Of course the virtual inputs ultimately get their values from real, physical inputs. There are several different kinds.

- key, a key on the keyboard. Key values are given for US keyboards and mapped to other keyboards automatically. So for example the `w` key will always be below the `2` and `3` number keys no matter what localization is used.
- physical_key, an actual physical key, so a `w` will be at different positions depending on the keyboard's localization.  
- mouse_button, a button on the mouse, as mapped by the mouse. `lmb` and `1` are aliased as are `rmb` and `2`. Higher keys are referenced only by number.
- mouse_axis_delta, the change in the position of the mouse since last tick.
- mouse_axis_absolute, the position of the mouse in the window in pixels.
- pad_button, a physical button on a gamepad. By convention xbox names are used e.g. a for the bottom face button, b for the right, rb for the right bumper, rt for the right trigger, rs for pushing the right stick in, and so on. Two special button names are provided: confirm and back. a always refers to the bottom face button on a controller which on a Nintendo device is actually the b button. confirm always refers to the controller specific confirm button wherever it is and back works similarly.
- pad_axis, an axis of a thumbstick, directional pad, or trigger.