#!/bin/bash


#check for available modems
if [ "$1" == "list" ] ; then
	mmcli -L | grep -oe "[/\s][0-9]." | cut -b 2-

elif [ "$1" == "extract" ] ; then
	modem_index=$3
	_command=$2
	if [ "$_command" == "e_id" ] ; then
		mmcli -m $modem_index 2>&1 | grep "equipment id" | grep -oe "[0-9]*"
	elif [ "$_command" == "sig_qual" ] ; then
		mmcli -m $modem_index 2>&1 | grep "signal quality" | grep -oe "[0-9]*"
	elif [ "$_command" == "op_name" ] ; then
		mmcli -m $modem_index 2>&1 | grep "operator name" | grep -oe "'[a-zA-Z]*'" | grep -oe "\w[a-zA-Z]*"
	fi

elif [ "$1" == "sms" ] ; then
	_type=$2
	if [ "$_type" == "send" ] ; then
		message=$3
		number=$4
		modem_index=$5
		
		output=$( mmcli -m $modem_index --messaging-create-sms="text='$message', number='$number'" )
		sms_index=$( echo $output | grep -oe "[/\s][0-9]." | cut -b 2- )
		if [ $(mmcli -m $modem_index -s $sms_index --send > /dev/null 2>&1) ] ; then
			echo sent
		fi
	fi
fi
