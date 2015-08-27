./cbindex -server 127.0.0.1:9000 -auth Administrator:asdasd -type drop \
    -bucket default -index iname
~/0cb/install/bin/couchbase-cli bucket-delete -u Administrator -p asdasd \
    --cluster=127.0.0.1:9000 --bucket default
~/0cb/install/bin/couchbase-cli bucket-create -u Administrator -p asdasd \
    --cluster=127.0.0.1:9000 --bucket default \
    --bucket-ramsize=1500 --bucket-type=couchbase --enable-flush=1
./cbindex -server 127.0.0.1:9000 -auth Administrator:asdasd -type create \
    -bucket default -index iname -fields=name
