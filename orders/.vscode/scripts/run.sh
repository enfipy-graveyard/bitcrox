echo "Current working directory -" $1
cd $1

cleos set contract bitcrox ../$2 -p bitcrox@active
