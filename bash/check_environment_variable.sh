if [ -z "$CROSS_C_ROOT_PATH" ]; then
echo "Need to set CROSS_C_ROOT_PATH"
fi

${STATE?"Need to set STATE"}
${DEST:?"Need to set DEST non-empty"}
