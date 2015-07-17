cwd=`pwd`
export PATH=$PATH:/usr/local/go/bin
export GOPATH=$HOME/pratap/go:$GOPATH
export GOBIN=$HOME/pratap/go/bin:$GOBIN

cd ~/pratap/go/src/github.com/couchbase/indexing/secondary/
./build.sh
cp /root/pratap/go/src/github.com/couchbase/indexing/secondary/cmd/indexer/indexer /opt/couchbase/bin/
cp /root/pratap/go/src/github.com/couchbase/indexing/secondary/cmd/projector/projector /opt/couchbase/bin/

cd $cwd
