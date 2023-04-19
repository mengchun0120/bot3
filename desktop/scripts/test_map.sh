if [ $# -ne 1 ]; then
    echo "Usage: $0 mapFile"
    exit 1
fi

map_file=$1
./build/app/bot --appName test_map \
                --appConfig config/bot_config.json \
                --logFile test_shape.log \
                --logLevel DEBUG \
                --mapFile $map_file \
                --appDir ..
