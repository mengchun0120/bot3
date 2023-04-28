DIRS="botlib commonlib tools desktop android"
for dir in $DIRS; do
    files=$(find $dir -name "*.cpp" -or \
                 -name "*.h" -or \
                 -name "*.txt" -or \
                 -name "*.py" -or \
                 -name "*.sh" -or \
                 -name "*.json")
    for f in $files; do
        echo "processing $f"
        vim $f -c "set ff=unix" -c ":wq"
    done
done

