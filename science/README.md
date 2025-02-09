# Science

## Sample Collection

This is the large module hanging of the front of the rover to collect the soil.

### Auger

Uses a [SparkMax](https://www.revrobotics.com/rev-11-2158/) controller for speed control.

### Extension to Ground Level

Uses a [Tic T249](https://www.pololu.com/product/3138/resources) to control a stepper motor.

### Soil Splitting

Uses a [Tic T249](https://www.pololu.com/product/3138/resources) to control a stepper motor.

### Water flooding

Uses [SMC G2 18v25](https://www.pololu.com/product/1366) to control peristaltic pump.

### Send Sample Solution to Dectors

Uses [SMC G2 18v25](https://www.pololu.com/product/1366) to control 2 independent peristaltic pump.
Uses 2 PWM channels to control 2 servos.

## Subsurface Conditions

> Currently no information

## Fluorometer

Attempts to detect life from the

### Priming Micro-Pump

Uses a [Tic T249](https://www.pololu.com/product/3138/resources) to control stepper motor peristaltic pump.
Uses PWM to control servo motor

### Heating Samples

Read 2 [10k Termistors](https://www.digikey.com/en/products/detail/tewa-sensors-llc/TT6-10KC8-9-25/10264795?utm_adgroup=&utm_source=google&utm_medium=cpc&utm_campaign=PMax%20Shopping_Product_High%20ROAS%20Categories&utm_term=&utm_content=&utm_id=go_cmp-20222717502_adg-_ad-__dev-c_ext-_prd-10264795_sig-Cj0KCQjw9Km3BhDjARIsAGUb4nzYKdWEd4HnxEjrfXoDowEsBvi6U8k_2F0oMVRyM61vd6S9V9jipWAaAnHbEALw_wcB&gad_source=1&gclid=Cj0KCQjw9Km3BhDjARIsAGUb4nzYKdWEd4HnxEjrfXoDowEsBvi6U8k_2F0oMVRyM61vd6S9V9jipWAaAnHbEALw_wcB)
Power 2 [Heater Strips](https://www.amazon.com/10mmx93mm-Adhesive-Heating-Elements-Polyimide/dp/B0CDL81T1T/ref=sr_1_17?crid=1FT245JF9GWXQ&keywords=heat+strips&qid=1706575100&sprefix=heat+strips%2Caps%2C123&sr=8-17)

### Select Sample to Read with Fluorometer

Uses a [Tic T249](https://www.pololu.com/product/3138/resources) to control stepper motor linear actuator.
Read from I2C ADC (test code is already written)

## Spectrometer/Ethanol Test

### Select Sample to Read with Spectrometer

Uses a [Tic T249](https://www.pololu.com/product/3138/resources) to control stepper motor linear actuator.
Read from spectrometer module (test code is already written)

### Display Readings on Base Station

Create graph of wavelength (nm) vs. intesity (0 to 1)
