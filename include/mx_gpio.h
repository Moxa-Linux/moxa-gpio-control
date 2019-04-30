/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Name:
 *	MOXA GPIO Library
 *
 * Description:
 *	Library for GPIO.
 *
 * Authors:
 *	2018	Ken CJ Chou	<KenCJ.Chou@moxa.com>
 */

#ifndef _MOXA_GPIO_H
#define _MOXA_GPIO_H

enum gpio_direction {
	GPIO_DIRECTION_IN = 0,
	GPIO_DIRECTION_OUT = 1
};

enum gpio_value {
	GPIO_VALUE_LOW = 0,
	GPIO_VALUE_HIGH = 1
};

#ifdef __cplusplus
extern "C" {
#endif

extern int mx_gpio_is_exported(int gpio_num);
extern int mx_gpio_export(int gpio_num);
extern int mx_gpio_unexport(int gpio_num);
extern int mx_gpio_set_direction(int gpio_num, int direction);
extern int mx_gpio_get_direction(int gpio_num, int *direction);
extern int mx_gpio_set_value(int gpio_num, int value);
extern int mx_gpio_get_value(int gpio_num, int *value);

#ifdef __cplusplus
}
#endif

#endif /* _MOXA_GPIO_H */

