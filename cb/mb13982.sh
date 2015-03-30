#! /usr/bin/env bash

URL=http://localhost:9499/query
HEADER='-H Content-Type:text/plain'

run_query(){
    echo $1
    curl -s -X POST $HEADER --data "$1" $URL | $2
    echo
}

# cleanup
#run_query 'DROP INDEX default:default.idxage USING GSI'       'grep "error\|cause\|msg\|success" -i'

## create-index
#run_query 'CREATE INDEX idxage ON default:default(age) USING GSI'  'grep "error\|cause\|msg\|success" -i'
#
#SLEEP=5
#echo "Sleeping for $SLEEP seconds ..."
##sleep $SLEEP
#
## query
#run_query 'SELECT \* FROM system:`indexes`'  'cat'
run_query 'SELECT \* FROM default WHERE age > 0'     'cat'

#run_query 'SELECT COUNT FROM default;'
