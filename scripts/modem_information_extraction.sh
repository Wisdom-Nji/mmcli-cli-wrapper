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
		mmcli -m 8 | grep "operator name" | grep -oe ": [a-zA-Z]*" | grep -oe "[a-zA-Z]*"
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
		else
			echo "Not sent"
		fi
	elif [ "$_type" == "received" ] ; then
		modem_index=$3

		output=$( mmcli -m $modem_index --messaging-list-sms | grep -oe "[0-9]* (received)" | grep -oe "[0-9]*" )
		if [ ! -z "$output" ] ; then 
			echo "$output"
		fi
	elif [ "$_type" == "read_sms" ] ; then
		modem_index=$4
		message_index=$3

		message_number=$( mmcli -m 8 --sms 188 | grep number | grep -oe "[+0-9]*" )
		message_text=$( mmcli -m 8 --sms 188 | grep text | grep -oe ": [a-zA-Z0-9\W :<=?]*" | cut -b 3- )
		echo -e "message_number\n$message_text"

	fi
fi
