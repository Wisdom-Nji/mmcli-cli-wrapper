#!/bin/bash


#man-page says using the -K command would make the data more developer friends (key->value)
#SHOULD HAVE READ THIS FROM THE START... WOULD REFACTOR ALL THIS TO REFLECT THAT


#check for available modems
if [ "$1" == "list" ] ; then
	mmcli -L | grep -oP "[/\s][0-9]." | cut -b 2-

elif [ "$1" == "extract" ] ; then
	modem_index=$3
	_command=$2
	if [ "$_command" == "e_id" ] ; then
		mmcli -m $modem_index 2>&1 | grep "equipment id" | grep -oP "[0-9]*"
	elif [ "$_command" == "sig_qual" ] ; then
		mmcli -m $modem_index 2>&1 | grep "signal quality" | grep -oP "[0-9]*"
	elif [ "$_command" == "op_name" ] ; then
		mmcli -m 8 | grep "operator name" | grep -oP ": [a-zA-Z]*" | grep -oP "[a-zA-Z]*"
	fi

elif [ "$1" == "sms" ] ; then
	_type=$2
	if [ "$_type" == "send" ] ; then
		message=$3
		number=$4
		modem_index=$5
		
		output=$( mmcli -m $modem_index --messaging-create-sms="text='$message', number='$number'" )
		sms_index=$( echo $output | grep -oP "[/\s][0-9]." | cut -b 2- )
		if [ $(mmcli -m $modem_index -s $sms_index --send > /dev/null 2>&1) ] ; then
			echo sent
		else
			echo "Not sent"
		fi
	elif [ "$_type" == "received" ] ; then
		modem_index=$3

		output=$( mmcli -m $modem_index --messaging-list-sms | grep -oP "[0-9]* (received)" | grep -oP "[0-9]*" )
		if [ ! -z "$output" ] ; then 
			echo "$output"
		fi
	elif [ "$_type" == "read_sms" ] ; then
		modem_index=$4
		message_index=$3

		message_number=$( mmcli -m $modem_index --sms $message_index| grep number | grep -oP "[+0-9]*" )
		message_text=$( mmcli -m $modem_index --sms $message_index | grep text | grep -oP ": [a-zA-Z0-9\W :<=?]*" | cut -b 3- )
		timestamp=$( mmcli -m $modem_index --sms $message_index | grep timestamp: | grep -oP ": [a-zA-Z0-9\W]*" | cut -b 3- ) 
		echo -e "$message_number\n$message_text\n$timestamp"

	fi
fi
