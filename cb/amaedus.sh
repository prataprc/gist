go build; GOMAXPROCS=20 ./loadgen -auth Administrator:asdasd -bagdir /home/prataprc/devgo/src/github.com/prataprc/monster/bags -count 100000 -par 100 -buckets default -prods /Users/prataprc/devgo/src/github.com/prataprc/monster/prods/amadeus.prod -ratio=0,0,0 http://apple:8091

CREATE INDEX idx1 ON default(chain_code) USING GSI WITH {"defer_build":true, "index_type" : "memory_optimized"};
CREATE INDEX idx2 ON default(reservation_id) USING GSI WITH {"defer_build":true, "index_type" : "memory_optimized"};
CREATE INDEX idx3 ON default(chain_code, criteria_for_search.creation_time) USING GSI WITH {"defer_build":true, "index_type" : "memory_optimized"};
CREATE INDEX idx4 ON default(chain_code, criteria_for_search.modification_time) USING GSI WITH {"defer_build":true, "index_type" : "memory_optimized"};
CREATE INDEX idx5 ON default(chain_code, criteria_for_search.checkOutDates, criteria_for_search.checkInDates) USING GSI WITH {"defer_build":true, "index_type" : "memory_optimized"};
CREATE INDEX idx6 ON default(chain_code, criteria_for_search.guestsLastName) USING GSI WITH {"defer_build":true, "index_type" : "memory_optimized"};
CREATE INDEX idx7 ON default(chain_code, criteria_for_search.groupName) USING GSI WITH {"defer_build":true, "index_type" : "memory_optimized"};
CREATE INDEX idx8 ON default(chain_code, criteria_for_search.profileIds) USING GSI WITH {"defer_build":true, "index_type" : "memory_optimized"};
CREATE INDEX idx9 ON default(chain_code, criteria_for_search.optionDate) USING GSI WITH {"defer_build":true, "index_type" : "memory_optimized"};
CREATE INDEX idx10 ON default(chain_code, criteria_for_search.pnrNumber) USING GSI WITH {"defer_build":true, "index_type" : "memory_optimized"};

BUILD INDEX ON default(idx1,idx2,idx3,idx4,idx5,idx6,idx7,idx8,idx9,idx10) USING GSI;
