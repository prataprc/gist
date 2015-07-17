cwd=`pwd`
yum install git
yum groupinstall "Development Tools"
export PATH=$PATH:/usr/local/go/bin
export GOPATH=$HOME/pratap/go:$GOPATH
export GOBIN=$HOME/pratap/go/bin:$GOBIN
go get github.com/couchbase/query
cd ~/pratap/go/src/github.com/couchbase/query
go get ...

