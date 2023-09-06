# Using Rotary Encoder to Calculate the cycles of a motor

### Define needed Interupt pins:
    . PIN_ENCODER_A 2
    . PIN_ENCODER_B 3

### ISR_encoderPinA Function:
    Interrupt routine for encoder pin A,
     increment counter while moving clockwise direction

### ISR_encoderPinB Function:
    Interrupt routine for encoder pin B,
     increment counter while moving counter clockwise direction

### Calculating Cutoff Frequency

The cutoff frequency (also known as the maximum frequency or Nyquist frequency) of a rotary encoder is determined by the number of pulses per revolution and the maximum speed of the motorized wheel.

The distance traveled by the wheel in one revolution is equal to the circumference of the wheel, which can be calculated as:

Circumference = πd
Circumference = π(40cm)
Circumference = 125.66cm

The distance traveled by the wheel in one pulse is equal to the circumference of the encoder disc divided by the number of pulses per revolution:

    d_pulse = Circumference / ppr

    d_pulse = 125.66cm / 540

    d_pulse = 0.232cm

The maximum speed of the wheel is 0.5 m/s, which is equal to:

    v_max = 50 cm/s

The frequency at which the encoder can reliably detect pulses is equal to the maximum speed divided by the distance traveled by the wheel in one pulse:

    f_cutoff = v_max / d_pulse
    f_cutoff = 50 / 0.232
    f_cutoff = 215.52 Hz

Therefore, the cutoff frequency for this rotary encoder with 540 pulses per revolution, three wheels - one motorized with 40cm diameter and maximum speed 0.5 m/s is approximately 215.52 Hz.
