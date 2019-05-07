# API References

---
### int mx_gpio_is_exported(int gpio_num)

Check if the GPIO is exported.

#### Parameters
* gpio_num: the GPIO pin number.

#### Return value
* 1 for true, the GPIO is exported.
* 0 for false, the GPIO is not exported.

---
### int mx_gpio_export(int gpio_num)

Export the GPIO.

#### Parameters
* gpio_num: the GPIO pin number.

#### Return value
* 0 on success.
* negative numbers on error.

---
### int mx_gpio_unexport(int gpio_num)

Unexport the GPIO.

#### Parameters
* gpio_num: the GPIO pin number.

#### Return value
* 0 on success.
* negative numbers on error.

---
### int mx_gpio_set_direction(int gpio_num, int direction)

Set the direction of the GPIO.

#### Parameters
* gpio_num: the GPIO pin number.
* direction:
	* 0: in
	* 1: out

#### Return value
* 0 on success.
* negative numbers on error.

---
### int mx_gpio_get_direction(int gpio_num, int *direction)

Get the direction of the GPIO.

#### Parameters
* gpio_num: the GPIO pin number.
* direction: where the output value will be set.

#### Return value
* 0 on success.
* negative numbers on error.

---
### int mx_gpio_set_value(int gpio_num, int value)

Set the value of the GPIO.

#### Parameters
* gpio_num: the GPIO pin number.
* value:
	* 0: low
	* 1: high

#### Return value
* 0 on success.
* negative numbers on error.

---
### int mx_gpio_get_value(int gpio_num, int *value)

Get the value of the GPIO.

#### Parameters
* gpio_num: the GPIO pin number.
* value: where the output value will be set.

#### Return value
* 0 on success.
* negative numbers on error.

---
