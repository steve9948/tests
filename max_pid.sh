#!/bin/bash

pid_max=$(cat /proc/sys/kernel/pid_max)
echo "Maximum Process ID (PID) Value: $pid_max"
