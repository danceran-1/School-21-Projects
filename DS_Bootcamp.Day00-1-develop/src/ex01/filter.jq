jq -r '["id", "created_at", "name", "has_test", "alternate_url"], (.[] | [.id, .created_at, .name, .has_test, .alternate_url]) | @csv' ../ex00/hh.json > hh.csv


