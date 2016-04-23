#! /usr/bin/env bash

ssh jump@act.northscale.in -L 127.0.0.1:3000:apple:22 &
ssh jump@act.northscale.in -L 127.0.0.1:3001:banana:22 &
ssh jump@act.northscale.in -L 127.0.0.1:3002:choco:22 &
ssh jump@act.northscale.in -L 127.0.0.1:3003:donut:22 &
ssh jump@act.northscale.in -L 127.0.0.1:3004:docker:22 &

ssh jump@act.northscale.in -L 127.0.0.1:3100:apple:8091 &
ssh jump@act.northscale.in -L 127.0.0.1:3101:banana:8091 &
ssh jump@act.northscale.in -L 127.0.0.1:3102:choco:8091 &
ssh jump@act.northscale.in -L 127.0.0.1:3103:donut:8091 &
