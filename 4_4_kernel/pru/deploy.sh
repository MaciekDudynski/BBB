#! /bin/bash

while getopts "p:" opt; do
  case $opt in
    p)
      proj=${OPTARG}
      ;;
  esac
done

PRU_CORE=1

echo "-Placing firmware"
	cp ${proj}/gen/*.out /lib/firmware/am335x-pru${PRU_CORE}-fw

echo "-Rebooting"
	if [ $PRU_CORE -eq 0 ]
	then
		echo "4a334000.pru0" > /sys/bus/platform/drivers/pru-rproc/unbind 2> /dev/null
		echo "4a334000.pru0" > /sys/bus/platform/drivers/pru-rproc/bind
	else
		echo "4a338000.pru1" > /sys/bus/platform/drivers/pru-rproc/unbind 2> /dev/null
		echo "4a338000.pru1" > /sys/bus/platform/drivers/pru-rproc/bind
	fi
