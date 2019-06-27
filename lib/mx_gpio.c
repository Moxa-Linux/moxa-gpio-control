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

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <mx_gpio.h>

#define SYSFS_GPIO_PATH "/sys/class/gpio"
#define MAX_FILEPATH_LEN 256	/* reserved length for file path */
#define MAX_BUFFER_LEN 32	/* reserved length for buffer */

/*
 * static functions
 */
static int is_gpio_exported(int gpio_num)
{
	char filepath[MAX_FILEPATH_LEN];

	/* check if value file existed */
	sprintf(filepath, "%s/gpio%d/value", SYSFS_GPIO_PATH, gpio_num);
	if (access(filepath, F_OK) < 0)
		return 0;

	return 1;
}

static int read_file(char *filepath, char *data)
{
	int fd;

	fd = open(filepath, O_RDONLY);
	if (fd < 0) 
		return -1; /* E_SYSFUNCERR */

	if (read(fd, data, sizeof(data)) <= 0) {
		close(fd);
		return -1; /* E_SYSFUNCERR */
	}
	close(fd);
	return 0;
}

static int write_file(char *filepath, const char *data)
{
	int fd;

	fd = open(filepath, O_WRONLY);
	if (fd < 0)
		return -1; /* E_SYSFUNCERR */

	if (write(fd, data, strlen(data)) < 0) {
		close(fd);
		return -1; /* E_SYSFUNCERR */
	}
	close(fd);
	return 0;
}

/*
 * APIs
 */
int mx_gpio_is_exported(int gpio_num)
{
	return is_gpio_exported(gpio_num);
}

int mx_gpio_export(int gpio_num)
{
	char filepath[MAX_FILEPATH_LEN];
	char buffer[MAX_BUFFER_LEN];

	/* if device node is existed, do nothing */
	if (is_gpio_exported(gpio_num))
		return 0;

	sprintf(filepath, "%s/export", SYSFS_GPIO_PATH);
	sprintf(buffer, "%d", gpio_num);

	return write_file(filepath, buffer);
}

int mx_gpio_unexport(int gpio_num)
{
	char filepath[MAX_FILEPATH_LEN];
	char buffer[MAX_BUFFER_LEN];

	/* if device node is not existed, do nothing */
	if (!is_gpio_exported(gpio_num))
		return 0;

	sprintf(filepath, "%s/unexport", SYSFS_GPIO_PATH);
	sprintf(buffer, "%d", gpio_num);

	return write_file(filepath, buffer);
}

int mx_gpio_set_direction(int gpio_num, int direction)
{
	char filepath[MAX_FILEPATH_LEN];

	if (!is_gpio_exported(gpio_num))
		return -20; /* E_GPIO_NOTEXP */

	sprintf(filepath, "%s/gpio%d/direction", SYSFS_GPIO_PATH, gpio_num);
	if (direction == GPIO_DIRECTION_IN) {
		return write_file(filepath, "in");
	} else if (direction == GPIO_DIRECTION_OUT) {
		return write_file(filepath, "out");
	} else {
		return -2; /* E_INVAL */
	}
}

int mx_gpio_get_direction(int gpio_num, int *direction)
{
	char filepath[MAX_FILEPATH_LEN];
	char buffer[MAX_BUFFER_LEN];
	int ret;

	if (!is_gpio_exported(gpio_num))
		return -20; /* E_GPIO_NOTEXP */

	sprintf(filepath, "%s/gpio%d/direction", SYSFS_GPIO_PATH, gpio_num);

	ret = read_file(filepath, buffer);
	if (ret < 0)
		return ret;

	if (!strncmp(buffer, "in", 2)) {
		*direction = GPIO_DIRECTION_IN;
		return 0;
	} else if (!strncmp(buffer, "out", 3)) {
		*direction = GPIO_DIRECTION_OUT;
		return 0;
	}
	return -21; /* E_GPIO_UNKDIR */
}

int mx_gpio_set_value(int gpio_num, int value)
{
	char filepath[MAX_FILEPATH_LEN];

	if (!is_gpio_exported(gpio_num))
		return -20; /* E_GPIO_NOTEXP */

	sprintf(filepath, "%s/gpio%d/value", SYSFS_GPIO_PATH, gpio_num);
	if (value == GPIO_VALUE_LOW) {
		return write_file(filepath, "0");
	} else if (value == GPIO_VALUE_HIGH) {
		return write_file(filepath, "1");
	} else {
		return -2; /* E_INVAL */
	}
}

int mx_gpio_get_value(int gpio_num, int *value)
{
	char filepath[MAX_FILEPATH_LEN];
	char buffer[MAX_BUFFER_LEN];
	int ret;

	if (!is_gpio_exported(gpio_num))
		return -20; /* E_GPIO_NOTEXP */

	sprintf(filepath, "%s/gpio%d/value", SYSFS_GPIO_PATH, gpio_num);

	ret = read_file(filepath, buffer);
	if (ret < 0)
		return ret;

	if (!strncmp(buffer, "0", 1)) {
		*value = GPIO_VALUE_LOW;
		return 0;
	} else if (!strncmp(buffer, "1", 1)) {
		*value = GPIO_VALUE_HIGH;
		return 0;
	}
	return -22; /* E_GPIO_UNKVAL */
}
