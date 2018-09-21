echo "Current working directory -" $1
cd $1

eosiocpp -o $2.wast $2.cpp
