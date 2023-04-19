if [ $# != 1 ]; then
    echo "Usage: $0 mapFile"
    exit 1
fi

map_file=$1
./build/app/bot --appName gen_map \
                --appConfig config/bot_config.json \
                --logFile gen_map.log \
                --logLevel DEBUG \
                --appDir .. \
                --algorithm island \
                --algorithmConfig config/island_gen_map_config.json \
                --mapFile $map_file
