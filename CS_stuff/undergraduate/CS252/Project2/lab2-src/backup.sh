#!/bin/sh
#
#
#
trap bashtrap INT
clear;
bashtrap(){
    echo
    echo "Bye!"
    exit
}
folder=$(pwd)
currentTime=$(date +%Y-%m-%d-%H-%M-%S)
if [ $# -ne 4 ];
then
    echo "$0 needs 4 arguements"
    echo "Example: dir backupdir 3 8"
    exit
fi
ls -lR $1 > ls-lR.last
rm -R $2
mkdir -p $2
cp -R $1 $2/$currentTime
echo " File $1 has been backuped!" | mail -s "Backup Log" wang1105@purdue.edu
interval=$3
num=0
while [ "1" ];
do
    sleep $interval
    cd $folder
    ls -lR $1 > ls-lR.new
    diff ls-lR.new ls-lR.last > temp
    if [ -s "temp" ] 
    then
	echo "Detected files changes. Backup starts."
	currentTime=$(date +%Y-%m-%d-%H-%M-%S)	
	cp -R $1 $2/$currentTime
	echo " File $1 has been backuped!" | mail -s "Backup Log" wang1105@purdue.edu
	cd $folder
	mv ls-lR.new  ls-lR.last
	#check the numer of backup files
	cd $2
	num=`ls -1 | wc -l`
	if [ $num -gt $4 ]
	    then 
	    more=`expr $num - $4`
	    cd $2
	    ls | head -$more | xargs rm -r
	    cd ..
	    echo "delete extra backups $more"
	fi
    else
	echo "No change"
    fi
done