cli=~/0cb/install/bin/couchbase-cli

$cli bucket-create --cluster=127.0.0.1:9000 --user=Administrator \
    --password=asdasd --bucket=bucket1 --bucket-password="" \
    --bucket-ramsize=100 --bucket-replica=0 \
    --bucket-type=couchbase --enable-flush=1 --wait
$cli bucket-create --cluster=127.0.0.1:9000 --user=Administrator \
    --password=asdasd --bucket=bucket2 --bucket-password="" \
    --bucket-ramsize=100 --bucket-replica=0 \
    --bucket-type=couchbase --enable-flush=1 --wait
$cli bucket-create --cluster=127.0.0.1:9000 --user=Administrator \
    --password=asdasd --bucket=bucket3 --bucket-password="" \
    --bucket-ramsize=100 --bucket-replica=0 \
    --bucket-type=couchbase --enable-flush=1 --wait
$cli bucket-create --cluster=127.0.0.1:9000 --user=Administrator \
    --password=asdasd --bucket=bucket4 --bucket-password="" \
    --bucket-ramsize=100 --bucket-replica=0 \
    --bucket-type=couchbase --enable-flush=1 --wait
$cli bucket-create --cluster=127.0.0.1:9000 --user=Administrator \
    --password=asdasd --bucket=bucket5 --bucket-password="" \
    --bucket-ramsize=100 --bucket-replica=0 \
    --bucket-type=couchbase --enable-flush=1 --wait
$cli bucket-create --cluster=127.0.0.1:9000 --user=Administrator \
    --password=asdasd --bucket=bucket6 --bucket-password="" \
    --bucket-ramsize=100 --bucket-replica=0 \
    --bucket-type=couchbase --enable-flush=1 --wait
$cli bucket-create --cluster=127.0.0.1:9000 --user=Administrator \
    --password=asdasd --bucket=bucket7 --bucket-password="" \
    --bucket-ramsize=100 --bucket-replica=0 \
    --bucket-type=couchbase --enable-flush=1 --wait
$cli bucket-create --cluster=127.0.0.1:9000 --user=Administrator \
    --password=asdasd --bucket=bucket8 --bucket-password="" \
    --bucket-ramsize=100 --bucket-replica=0 \
    --bucket-type=couchbase --enable-flush=1 --wait
$cli bucket-create --cluster=127.0.0.1:9000 --user=Administrator \
    --password=asdasd --bucket=bucket9 --bucket-password="" \
    --bucket-ramsize=100 --bucket-replica=0 \
    --bucket-type=couchbase --enable-flush=1 --wait

repo=/Users/prataprc/devgo/src/github.com/couchbase/indexing/secondary

#cd $repo/tools/loadgen;
#bagdir=/Users/prataprc/devgo/src/github.com/prataprc/monster/bags
#prodfile=/Users/prataprc/devgo/src/github.com/prataprc/monster/prods/users.prod
#arg="-auth Administrator:asdasd -bagdir $bagdir -count 10 -prods $prodfile"
#go run loadgen.go $arg -buckets bucket1 127.0.0.1:9000
#go run loadgen.go $arg -buckets bucket2 127.0.0.1:9000
#go run loadgen.go $arg -buckets bucket3 127.0.0.1:9000
#go run loadgen.go $arg -buckets bucket4 127.0.0.1:9000
#go run loadgen.go $arg -buckets bucket5 127.0.0.1:9000
#go run loadgen.go $arg -buckets bucket6 127.0.0.1:9000
#go run loadgen.go $arg -buckets bucket7 127.0.0.1:9000
#go run loadgen.go $arg -buckets bucket8 127.0.0.1:9000
#go run loadgen.go $arg -buckets bucket9 127.0.0.1:9000
#cd -;

createargs="-server 127.0.0.1:9000 -auth Administrator:asdasd -type create"
countargs="-server 127.0.0.1:9000 -auth Administrator:asdasd -type count"

cd $repo/cmd/cbindex;
./cbindex $createargs -primary -bucket bucket1 -index bucket1_primary -fields=nope
./cbindex $countargs -bucket bucket1 -index bucket1_primary

./cbindex $createargs -primary -bucket bucket2 -index bucket2_primary -fields=nope
./cbindex $countargs -bucket bucket2 -index bucket2_primary

./cbindex $createargs -primary -bucket bucket3 -index bucket3_primary -fields=nope
./cbindex $countargs -bucket bucket3 -index bucket3_primary

./cbindex $createargs -primary -bucket bucket4 -index bucket4_primary -fields=nope
./cbindex $countargs -bucket bucket4 -index bucket4_primary

./cbindex $createargs -primary -bucket bucket5 -index bucket5_primary -fields=nope
./cbindex $countargs -bucket bucket5 -index bucket5_primary

./cbindex $createargs -primary -bucket bucket6 -index bucket6_primary -fields=nope
./cbindex $countargs -bucket bucket6 -index bucket6_primary

./cbindex $createargs -primary -bucket bucket7 -index bucket7_primary -fields=nope
./cbindex $countargs -bucket bucket7 -index bucket7_primary

./cbindex $createargs -primary -bucket bucket8 -index bucket8_primary -fields=nope
./cbindex $countargs -bucket bucket8 -index bucket8_primary

./cbindex $createargs -primary -bucket bucket9 -index bucket9_primary -fields=nope
./cbindex $countargs -bucket bucket9 -index bucket9_primary

./cbindex $createargs -bucket bucket1 -index bucket1_age -fields=age
./cbindex $countargs -bucket bucket1 -index bucket1_age

./cbindex $createargs -bucket bucket2 -index bucket2_age -fields=age
./cbindex $countargs -bucket bucket2 -index bucket2_age

./cbindex $createargs -bucket bucket3 -index bucket3_age -fields=age
./cbindex $countargs -bucket bucket3 -index bucket3_age

./cbindex $createargs -bucket bucket4 -index bucket4_age -fields=age
./cbindex $countargs -bucket bucket4 -index bucket4_age

./cbindex $createargs -bucket bucket5 -index bucket5_age -fields=age
./cbindex $countargs -bucket bucket5 -index bucket5_age

./cbindex $createargs -bucket bucket6 -index bucket6_age -fields=age
./cbindex $countargs -bucket bucket6 -index bucket6_age

./cbindex $createargs -bucket bucket7 -index bucket7_age -fields=age
./cbindex $countargs -bucket bucket7 -index bucket7_age

./cbindex $createargs -bucket bucket8 -index bucket8_age -fields=age
./cbindex $countargs -bucket bucket8 -index bucket8_age

./cbindex $createargs -bucket bucket9 -index bucket9_age -fields=age
./cbindex $countargs -bucket bucket9 -index bucket9_age
cd -

cd $repo/cmd/cbindex;
./cbindex -type drop -bucket bucket1 -index bucket1_primary
./cbindex -type drop -bucket bucket2 -index bucket2_primary
./cbindex -type drop -bucket bucket3 -index bucket3_primary
./cbindex -type drop -bucket bucket4 -index bucket4_primary
./cbindex -type drop -bucket bucket5 -index bucket5_primary
./cbindex -type drop -bucket bucket6 -index bucket6_primary
./cbindex -type drop -bucket bucket7 -index bucket7_primary
./cbindex -type drop -bucket bucket8 -index bucket8_primary
./cbindex -type drop -bucket bucket9 -index bucket9_primary

./cbindex -type drop -bucket bucket1 -index bucket1_age
./cbindex -type drop -bucket bucket2 -index bucket2_age
./cbindex -type drop -bucket bucket3 -index bucket3_age
./cbindex -type drop -bucket bucket4 -index bucket4_age
./cbindex -type drop -bucket bucket5 -index bucket5_age
./cbindex -type drop -bucket bucket6 -index bucket6_age
./cbindex -type drop -bucket bucket7 -index bucket7_age
./cbindex -type drop -bucket bucket8 -index bucket8_age
./cbindex -type drop -bucket bucket9 -index bucket9_age
cd -;
