#!/bin/bash

if [ $# -lt 4 ]; then
	echo "Usage: ./$0 <DB_USER> <DB> <APP_NAME> <DUMP_FILE>"
	exit 1
fi

tables=$(echo "use $2; show tables;" | mysql -u $1 $2  | grep $3_ | tr '\n' ' ';);
echo -e "Processing $(echo $tables | wc -w) tables: \n$tables"
mysqldump -t -c -u $1 $2 $tables > $4
echo -e "\nDone"

