echo "Sync: "
time seq 8000 8005 | xargs -I {} -P 0 curl -s http://localhost:8888/sync/{}
echo "ASync: "
time seq 8000 8005 | xargs -I {} -P 0 curl -s http://localhost:8888/async/{}
