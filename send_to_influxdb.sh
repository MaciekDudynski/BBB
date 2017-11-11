#! /bin/bash

usage() { echo "Usage: $0 -v <value>" 1>&2; exit 1; }

while getopts "v:" flag
do
    case $flag in
        v)
             v=${OPTARG}
             shift
             ;;
    esac
    shift
done

if [ -z "${v}" ];
then
    curl -i -s -X POST 'http://192.168.0.21:8086/write?db=mydb' --data-binary 'adc_spi value='$1'' > /dev/null
else
    curl -i -s -X POST 'http://192.168.0.21:8086/write?db=mydb' --data-binary 'adc_spi value='${v}'' > /dev/null
fi
