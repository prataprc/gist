while true ;
do
    curl -u Administrator:asdasd -X POST localhost:9108/settings --data '{ "queryport.client.maxPayload": 20000000}'
    sleep 10
    curl -u Administrator:asdasd -X POST localhost:9108/settings --data '{"queryport.client.readDeadline": 400000}'
    sleep 10
    curl -u Administrator:asdasd -X POST localhost:9108/settings --data '{"queryport.client.writeDeadline": 5000}'
    sleep 10
    curl -u Administrator:asdasd -X POST localhost:9108/settings --data '{"queryport.client.connPoolTimeout": 2000}'
    sleep 10
    curl -u Administrator:asdasd -X POST localhost:9108/settings --data '{"queryport.client.connPoolAvailWaitTimeout": 2}'
    sleep 10
    curl -u Administrator:asdasd -X POST localhost:9108/settings --data '{"queryport.client.retryScanPort": 4}'
    sleep 10
    curl -u Administrator:asdasd -X POST localhost:9108/settings --data '{"queryport.client.retryIntervalScanport": 20}'
    sleep 10
    curl -u Administrator:asdasd -X POST localhost:9108/settings --data '{"queryport.client.load.randomWeight": 0.8}'
    sleep 10
    curl -u Administrator:asdasd -X POST localhost:9108/settings --data '{"queryport.client.load.equivalenceFactor": 0.1}'
    sleep 10
    curl -u Administrator:asdasd -X POST localhost:9108/settings --data '{"queryport.client.backfillLimit": 6000}'
    sleep 10
    curl -u Administrator:asdasd -X POST localhost:9108/settings --data '{"queryport.client.servicesNotifierRetryTm": 2000}'
    sleep 10
    curl -u Administrator:asdasd -X POST localhost:9108/settings --data '{"queryport.client.logtick": 70000}'

    sleep 10
    curl -u Administrator:asdasd -X POST localhost:9108/settings --data '{ "queryport.client.maxPayload": 10000000}'
    sleep 10
    curl -u Administrator:asdasd -X POST localhost:9108/settings --data '{"queryport.client.readDeadline": 300000}'
    sleep 10
    curl -u Administrator:asdasd -X POST localhost:9108/settings --data '{"queryport.client.writeDeadline": 4000}'
    sleep 10
    curl -u Administrator:asdasd -X POST localhost:9108/settings --data '{"queryport.client.connPoolTimeout": 1000}'
    sleep 10
    curl -u Administrator:asdasd -X POST localhost:9108/settings --data '{"queryport.client.connPoolAvailWaitTimeout": 1}'
    sleep 10
    curl -u Administrator:asdasd -X POST localhost:9108/settings --data '{"queryport.client.retryScanPort": 2}'
    sleep 10
    curl -u Administrator:asdasd -X POST localhost:9108/settings --data '{"queryport.client.retryIntervalScanport": 10}'
    sleep 10
    curl -u Administrator:asdasd -X POST localhost:9108/settings --data '{"queryport.client.load.randomWeight": 0.9}'
    sleep 10
    curl -u Administrator:asdasd -X POST localhost:9108/settings --data '{"queryport.client.load.equivalenceFactor": 0.5}'
    sleep 10
    curl -u Administrator:asdasd -X POST localhost:9108/settings --data '{"queryport.client.backfillLimit": 5000}'
    sleep 10
    curl -u Administrator:asdasd -X POST localhost:9108/settings --data '{"queryport.client.servicesNotifierRetryTm": 1000}'
    sleep 10
    curl -u Administrator:asdasd -X POST localhost:9108/settings --data '{"queryport.client.logtick": 50000}'
done
