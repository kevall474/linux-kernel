# SPDX-License-Identifier: GPL-2.0
#
# Makefile for the Motorola 8xx FEC ethernet controller
#

obj-$(CONFIG_SERIAL_CPM) += cpm_uart.o

# Select the correct platform objects.
cpm_uart-objs-$(CONFIG_CPM2)	+= cpm_uart_cpm2.o
cpm_uart-objs-$(CONFIG_CPM1)	+= cpm_uart_cpm1.o

cpm_uart-objs	:= cpm_uart_core.o $(cpm_uart-objs-y)
