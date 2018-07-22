//  Copyright (c) 2013 Couchbase, Inc.
//  Licensed under the Apache License, Version 2.0 (the "License"); you may not
//  use this file except in compliance with the License. You may obtain a copy
//  of the License at
//      http://www.apache.org/licenses/LICENSE-2.0
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
//  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
//  License for the specific language governing permissions and limitations
//  under the License.

package lib

import (
    "testing"
    "reflect"

    "github.com/prataprc/goparsec"
)

var text = `(+-) Entry differs between files
  in emea/0.couch.1:
    Doc ID: Ans~Org.101499~Schema.48519.WIP
    seq: 26
    rev: 1
    content_meta: 0
    cas: 5026724688100, expiry: 0, flags: 274
    data: {"Schemas":null,"Facts":null,"ProductId":"TxnyD.ProductInfo.102.1","CommunityId":"TxnyD.Communities.15.1"}

  in asia/0.couch.1:
    Doc ID: Ans~Org.101499~Schema.48519.WIP
    seq: 33
    rev: 2
    content_meta: 0
    cas: 5026724688100, expiry: 0, flags: 274
    data: {"Schemas":null,"Facts":null,"ProductId":"TxnyD.ProductInfo.102.1","CommunityId":"TxnyD.Communities.15.1"}`

func TestXDCRDiff(t *testing.T) {
    nt := XDCRDiffParse([]byte(text)).([]parsec.ParsecNode)
    m1, m2 := nt[1].(map[string]interface{}), nt[2].(map[string]interface{})
    t.Log(m1)
    t.Log(m2)
    if reflect.DeepEqual(m1, m2) == false {
        t.Errorf("Failed")
    }
}

func BenchmarkXDCRDiff(b *testing.B) {
    for i := 0; i < b.N; i++ {
        nt := XDCRDiffParse([]byte(text)).([]parsec.ParsecNode)
        m1, m2 := nt[1].(map[string]interface{}), nt[2].(map[string]interface{})
        reflect.DeepEqual(m1, m2)
    }
}
