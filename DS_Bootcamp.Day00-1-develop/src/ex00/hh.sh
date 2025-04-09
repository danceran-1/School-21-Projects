#!/bin/bash
curl -G "https://api.hh.ru/vacancies" \
     --data-urlencode "text=data scientist" \
     --data "per_page=20" \
     -o temp_hh.json
jq '.items' temp_hh.json > hh.json
rm temp_hh.json
