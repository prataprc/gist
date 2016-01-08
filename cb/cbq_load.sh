#! /usr/bin/env bash

URL=http://localhost:9499/query
HEADER='-H Content-Type:text/plain'

run_query() {
    echo $1
    curl -s -X POST $HEADER --data "$1" $URL | $2
    echo
}

for i in `seq 1 1000000`; do
    run_query 'SELECT name FROM default:`beer-sample` WHERE abv > 30' 'egrep success|elapsedTime'
done
