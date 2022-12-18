if [ $# != 1 ]; then
    echo "Usage: $0 mapFile"
    exit 1
fi

mapFile=$1
./build/app/genmap/genmap --appConfig config/bot_config.json \
                          --logFile genmap.log \
                          --logLevel DEBUG \
                          --appDir . \
                          --algorithm island \
                          --algorithmConfig config/island_gen_map_config.json \
                          --mapFile $mapFile
