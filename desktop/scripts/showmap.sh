if [ $# != 1 ]; then
    echo "Usage $0 mapfile"
    exit 1
fi

./build/app/showmap/showmap --appConfig config/bot_config.json \
                            --logFile showmap.log \
                            --logLevel DEBUG \
                            --appDir .. \
                            --mapFile $1
