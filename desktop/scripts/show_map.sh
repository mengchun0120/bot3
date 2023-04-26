if [ $# -ne 1 ]; then
    echo "Usage: $0 mapFile"
    exit 1
fi

./build/app/bot show_map \
                --appConfig config/bot_config.json \
                --logFile show_map.log \
                --logLevel DEBUG \
                --mapFile $1 \
                --appDir ..
