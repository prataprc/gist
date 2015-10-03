HOST=ec2-54-151-143-42.ap-southeast-1.compute.amazonaws.com
UP=Administrator:asdasd

./cbindex -server $HOST:8091 -auth $UP -type create -bucket default -index idx1 -fields=name -using memdb

go build
./cbindex -server $HOST:8091 -auth Administrator:asdasd -type nodes
./cbindex -server $HOST:8091 -auth Administrator:asdasd -type list
#
# CREATE
#
#./cbindex -server $HOST:8091 -auth $UP -type create -bucket default -index idx1 -fields=name -with '{"defer_build": true}' -using memdb
#./cbindex -server $HOST:8091 -auth $UP -type create -bucket default -index idx2 -fields=language -with '{"defer_build": true}' -using memdb
#./cbindex -server $HOST:8091 -auth $UP -type create -bucket default -index idx3 -fields=members -with '{"defer_build": true}' -using memdb
#./cbindex -server $HOST:8091 -auth $UP -type create -bucket default -index idx4 -fields=type -with '{"defer_build": true}' -using memdb
#./cbindex -server $HOST:8091 -auth $UP -type build -indexes default:idx1,default:idx2,default:idx3,default:idx4
#
# SCAN
#
#./cbindex -server $HOST:8091 -auth $UP -type count -bucket default -index #primary
#./cbindex -server $HOST:8091 -auth $UP -type count -bucket default -index idx1 -equal '[(512) Pale]'
#./cbindex -server $HOST:8091 -auth $UP -type count -bucket default -index idx2 -high '["#17 Cream Ale"]' -low '["(512) Pecan Porter"]'
#./cbindex -server $HOST:8091 -auth $UP -type scan -bucket default -index #primary -equal '["User-10000888974168323269"]'
#
# DROP
#
#./cbindex -server $HOST:8091 -auth $UP -type drop -bucket default -index #primary
#./cbindex -server $HOST:8091 -auth $UP -type drop -bucket default -index idx1
#./cbindex -server $HOST:8091 -auth $UP -type drop -bucket default -index idx2