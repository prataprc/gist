cwd=`pwd`
export PATH=$PATH:/usr/local/go/bin
export GOPATH=$HOME/pratap/go:$GOPATH
export GOBIN=$HOME/pratap/go/bin:$GOBIN
cd ~/pratap/go/src/github.com/couchbase/query/parser/n1ql
./build.sh
cd ~/pratap/go/src/github.com/couchbase/query/server/cbq-engine
./build.sh
cp cbq-engine /opt/couchbase/bin/
cd $cwd
