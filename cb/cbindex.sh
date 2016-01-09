HOST=ec2-54-151-143-42.ap-southeast-1.compute.amazonaws.com
UP=Administrator:asdasd

./cbindex -server $HOST:8091 -auth $UP -type create -bucket default -index idx1 -fields=name -using memdb

go build
./cbindex -server $HOST:8091 -auth Administrator:asdasd -type nodes
./cbindex -server $HOST:8091 -auth Administrator:asdasd -type list

#
# CREATE
#

./cbindex -server ec2-54-151-161-68.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket bucket1 -index idx1 -fields=type -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-161-68.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket bucket1 -index idx2 -fields=name -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-161-68.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket bucket1 -index idx3 -fields=age -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-161-68.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket bucket1 -index idx4 -fields=field1 -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-161-68.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket bucket1 -index idx5 -fields=picture -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-161-68.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket bucket2 -index idx1 -fields=type -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-161-68.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket bucket2 -index idx2 -fields=name -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-161-68.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket bucket2 -index idx3 -fields=age -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-161-68.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket bucket2 -index idx4 -fields=field1 -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-161-68.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket bucket2 -index idx5 -fields=picture -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-161-68.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket bucket3 -index idx1 -fields=type -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-161-68.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket bucket3 -index idx2 -fields=name -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-161-68.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket bucket3 -index idx3 -fields=age -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-161-68.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket bucket3 -index idx4 -fields=field1 -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-161-68.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type create -bucket bucket3 -index idx5 -fields=picture -with '{"defer_build": true}' -using memdb
./cbindex -server ec2-54-151-161-68.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type build -indexes bucket1:idx1,bucket1:idx2,bucket1:idx3,bucket1:idx4,bucket1:idx5,bucket2:idx1,bucket2:idx2,bucket2:idx3,bucket2:idx4,bucket2:idx5,bucket3:idx1,bucket3:idx2,bucket3:idx3,bucket3:idx4,bucket3:idx5

for bucket in bucket1 bucket2 bucket3; do
    for index in idx1 idx2 idx3 idx4 idx5; do
        ./cbindex -server ec2-54-151-161-68.ap-southeast-1.compute.amazonaws.com:8091 -auth Administrator:asdasd -type drop -bucket $bucket -index $index
    done
done

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

# cbq

CREATE INDEX pv_ndx_00 ON comm(UserId,meta().id,Type) WHERE Type='pv' AND TONUMBER(UserId)%4 = 0 USING GSI WITH {"defer_build":true};
CREATE INDEX pv_ndx_01 ON comm(UserId,meta().id,Type) WHERE Type='pv' AND TONUMBER(UserId)%4 = 1 USING GSI WITH {"defer_build":true};
CREATE INDEX pv_ndx_02 ON comm(UserId,meta().id,Type) WHERE Type='pv' AND TONUMBER(UserId)%4 = 2 USING GSI WITH {"defer_build":true};
CREATE INDEX pv_ndx_03 ON comm(UserId,meta().id,Type) WHERE Type='pv' AND TONUMBER(UserId)%4 = 3 USING GSI WITH {"defer_build":true};

BUILD INDEX ON comm(pv_ndx_00,pv_ndx_01,pv_ndx_02,pv_ndx_03) USING GSI;

curl -v http://localhost:9499/query/service -d 'statement=select * from default&scan_consistency=at_plus&scan_vector={"512":{"guard":"90891046896681","value":1}}'
curl -v http://localhost:9499/query/service -d 'statement=select * from default&scan_consistency=request_plus'
curl -v http://localhost:9499/query/service -d 'statement=select * from default&scan_consistency=not_bounded'
