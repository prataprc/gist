cwd=`pwd`
export PATH=$PATH:/usr/local/go/bin
export GOPATH=$HOME/pratap/go:$GOPATH
export GOBIN=$HOME/pratap/go/bin:$GOBIN

wget https://snappy.googlecode.com/files/snappy-1.1.1.tar.gz
tar -zxvf snappy-1.1.1.tar.gz
cd snappy-1.1.1
./configure && make && make install

sudo yum install libaio-devel

wget http://www.cmake.org/files/v2.8/cmake-2.8.12.1.tar.gz
tar zxvf cmake-2.8.12.1.tar.gz
cd cmake-2.8.12.1
./bootstrap && make && sudo make install

cd forestdb
mkdir build
cd build
cmake ..
make all
sudo make install


