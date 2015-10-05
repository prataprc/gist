HOST=ec2-54-151-143-42.ap-southeast-1.compute.amazonaws.com
UP=Administrator:asdasd

./cbindex -server $HOST:8091 -auth $UP -type create -bucket default -index idx1 -fields=name -using memdb

go build
./cbindex -server $HOST:8091 -auth Administrator:asdasd -type nodes
./cbindex -server $HOST:8091 -auth Administrator:asdasd -type list

#
# CREATE
#

./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket default -index idx1 -fields=type -using memdb
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket default -index idx2 -fields=type -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket default -index idx3 -fields=name -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket default -index idx4 -fields=name -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket default -index idx5 -fields=members -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket default -index idx6 -fields=language -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket default -index idx7 -fields=members -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket default -index idx8 -fields=language -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket default -index idx9 -fields=type -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket default -index idx10 -fields=name -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket default -index idx11 -fields=name -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket default -index idx12 -fields=members -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket default -index idx13 -fields=language -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket default -index idx14 -fields=members -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket default -index idx15 -fields=language -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket default -index idx16 -fields=type -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket default -index idx17 -fields=name -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket default -index idx18 -fields=name -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket default -index idx19 -fields=members -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket default -index idx20 -fields=language -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket default -index idx21 -fields=members -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket default -index idx22 -fields=language -with '{"defer_build": true}' -using memdb

./cbindex -server $HOST:8091 -auth $UP -type create -bucket default -index idx2 -fields=language -with '{"defer_build": true}' -using memdb
./cbindex -server $HOST:8091 -auth $UP -type create -bucket default -index idx3 -fields=members -with '{"defer_build": true}' -using memdb
./cbindex -server $HOST:8091 -auth $UP -type create -bucket default -index idx4 -fields=type -with '{"defer_build": true}' -using memdb

./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type build -indexes default:idx2,default:idx3,default:idx4,default:idx5,default:idx6,default:idx7,default:idx9,default:idx10,default:idx11,default:idx12,default:idx13,default:idx14

./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd  -type drop -bucket default -index idx1
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd  -type drop -bucket default -index idx2
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd  -type drop -bucket default -index idx3
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd  -type drop -bucket default -index idx4
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd  -type drop -bucket default -index idx5
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd  -type drop -bucket default -index idx6
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd  -type drop -bucket default -index idx7
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd  -type drop -bucket default -index idx8
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd  -type drop -bucket default -index idx9
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd  -type drop -bucket default -index idx10
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd  -type drop -bucket default -index idx11
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd  -type drop -bucket default -index idx12
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd  -type drop -bucket default -index idx13
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd  -type drop -bucket default -index idx14
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd  -type drop -bucket default -index idx15
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd  -type drop -bucket default -index idx16
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd  -type drop -bucket default -index idx17
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd  -type drop -bucket default -index idx18
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd  -type drop -bucket default -index idx19
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd  -type drop -bucket default -index idx20
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd  -type drop -bucket default -index idx21
./cbindex -server ec2-54-151-146-15.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd  -type drop -bucket default -index idx22

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
