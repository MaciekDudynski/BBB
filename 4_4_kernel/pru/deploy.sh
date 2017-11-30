#! /bin/bash

PRU_CORE=1

while getopts "p:c:" opt; do
	case $opt in
		p)
			PROJ=${OPTARG}
			;;
		c)
			PRU_CORE=${OPTARG}
			;;
	esac
done

	make p=${PROJ}
echo "************************************************************"
echo "Placing firmware on PRU${PRU_CORE}"
	cp ${PROJ}/gen/*.out /lib/firmware/am335x-pru${PRU_CORE}-fw
echo "************************************************************"
echo ""
echo "************************************************************"
echo "Rebooting PRU${PRU_CORE}"
	if [ $PRU_CORE -eq 0 ]
	then
		echo "4a334000.pru0" > /sys/bus/platform/drivers/pru-rproc/unbind 2> /dev/null
		echo "4a334000.pru0" > /sys/bus/platform/drivers/pru-rproc/bind
	else
		echo "4a338000.pru1" > /sys/bus/platform/drivers/pru-rproc/unbind 2> /dev/null
		echo "4a338000.pru1" > /sys/bus/platform/drivers/pru-rproc/bind
	fi
echo "************************************************************"
echo ""
