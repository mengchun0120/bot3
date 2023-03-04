if [ $# != 1 ]; then
    echo "Usage: $0 mapFile"
    exit 1
fi

./build/app/rungame/rungame --appConfig config/bot_config.json \
                            --logFile rungame.log \
                            --logLevel DEBUG \
                            --appDir . \
                            --mapFile $1
