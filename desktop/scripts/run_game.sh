exercise_mode=0
if [ $# -lt 1 ]; then
    echo "Usage: $0 mapFile [exercise_mode]"
    exit 1
fi

map_file=$1

if [ $# -eq 2 ]; then
    exercise_mode=$2
else
    exercise_mode=0
fi

./build/app/bot run_game \
                --appConfig config/bot_config.json \
                --logFile run_game.log \
                --logLevel DEBUG \
                --mapFile $map_file \
                --exerciseMode $exercise_mode \
                --appDir ..
