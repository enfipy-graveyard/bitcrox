echo "Current working directory -" $1
cd $1

cleos set contract $2 ../$2 -p $2@active
