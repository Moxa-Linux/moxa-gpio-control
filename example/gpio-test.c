/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Name:
 *	C Example code for MOXA GPIO Library
 *
 * Description:
 *	Example code for demonstrating the usage of GPIO Library in C
 *
 * Authors:
 *	2019	Ken CJ Chou	<KenCJ.Chou@moxa.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <moxa/mx_gpio.h>

static int is_exported_at_first;

static void exit_reset_gpio(int exit_code, int gpio_num)
{
	if (!is_exported_at_first) {
		printf("Unexport GPIO %d.\n", gpio_num);
		mx_gpio_unexport(gpio_num);
	}

	exit(exit_code);
}

int main(int argc, char *argv[])
{

	int gpio_num, ret;
	int direction, value;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <gpio_num>\n", argv[0]);
		exit(99);
	}
	gpio_num = atoi(argv[1]);

	printf("Testing GPIO %d\n", gpio_num);
	printf("====================\n");

	if (mx_gpio_is_exported(gpio_num)) {
		printf("- GPIO %d is exported.\n", gpio_num);
		is_exported_at_first = 1;
	} else {
		printf("- GPIO %d is not exported,\n", gpio_num);
		printf("  export GPIO %d now.\n", gpio_num);

		ret = mx_gpio_export(gpio_num);
		if (ret < 0) {
			fprintf(stderr, "Error: Failed to export GPIO %d\n", gpio_num);
			fprintf(stderr, "Return code: %d\n", ret);
			exit(1);
		}
		is_exported_at_first = 0;
	}

	ret = mx_gpio_get_direction(gpio_num, &direction);
	if (ret < 0) {
		fprintf(stderr, "Error: Failed to get GPIO %d's direction\n", gpio_num);
		fprintf(stderr, "Return code: %d\n", ret);
		exit_reset_gpio(1, gpio_num);
	}
	ret = mx_gpio_get_value(gpio_num, &value);
	if (ret < 0) {
		fprintf(stderr, "Error: Failed to get GPIO %d's value\n", gpio_num);
		fprintf(stderr, "Return code: %d\n", ret);
		exit_reset_gpio(1, gpio_num);
	}
	printf("  The direction is %d\n", direction);
	printf("  The value is %d\n", value);

	printf("- Setting GPIO %d to \"out\" and \"high\"\n", gpio_num);
	ret = mx_gpio_set_direction(gpio_num, GPIO_DIRECTION_OUT);
	if (ret < 0) {
		fprintf(stderr, "Error: Failed to set GPIO %d's direction\n", gpio_num);
		fprintf(stderr, "Return code: %d\n", ret);
		exit_reset_gpio(1, gpio_num);
	}
	ret = mx_gpio_set_value(gpio_num, GPIO_VALUE_HIGH);
	if (ret < 0) {
		fprintf(stderr, "Error: Failed to set GPIO %d's value\n", gpio_num);
		fprintf(stderr, "Return code: %d\n", ret);
		exit_reset_gpio(1, gpio_num);
	}
	sleep(2);

	ret = mx_gpio_get_direction(gpio_num, &direction);
	if (ret < 0) {
		fprintf(stderr, "Error: Failed to get GPIO %d's direction\n", gpio_num);
		fprintf(stderr, "Return code: %d\n", ret);
		exit_reset_gpio(1, gpio_num);
	}
	ret = mx_gpio_get_value(gpio_num, &value);
	if (ret < 0) {
		fprintf(stderr, "Error: Failed to get GPIO %d's value\n", gpio_num);
		fprintf(stderr, "Return code: %d\n", ret);
		exit_reset_gpio(1, gpio_num);
	}
	printf("  The direction is %d\n", direction);
	printf("  The value is %d\n", value);

	sleep(1);
	printf("====================\n");
	printf("Test OK.\n");
	exit_reset_gpio(0, gpio_num);
}
