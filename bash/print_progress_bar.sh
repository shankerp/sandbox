#!/bin/bash
# progress-bar.sh

# Author: Dotan Barak (very minor revisions by ABS Guide author).
# Used in ABS Guide with permission (thanks!).


print_progress_bar()
{
    BAR_CHAR_START="[";
    BAR_CHAR_END="]";
    BAR_CHAR_EMPTY=".";
    BAR_CHAR_FULL="=";
    BRACKET_CHARS=2;
    LIMIT=100;

# Calculate how many characters will be full.
    let "full_limit = ((($1 - $BRACKET_CHARS) * $2) / $LIMIT)";
    echo "Full Limit $full_limit"

# Calculate how many characters will be empty.
    let "empty_limit = ($1 - $BRACKET_CHARS) - ${full_limit}";
    echo "Empty limit $empty_limit"

# Prepare the bar.
    bar_line="${BAR_CHAR_START}";
    for ((j=0; j<full_limit; j++)); do
        bar_line="${bar_line}${BAR_CHAR_FULL}";
    done

        for ((j=0; j<empty_limit; j++)); do
            bar_line="${bar_line}${BAR_CHAR_EMPTY}";
    done

        bar_line="${bar_line}${BAR_CHAR_END}";

    printf "%3d%% %s" $2 ${bar_line};
}

# Here is a sample of code that uses it.
BAR_WIDTH=50
MAX_PERCENT=100
for ((i=0; i<=MAX_PERCENT; i++)); do
        #
        usleep 10000
        # ... Or run some other commands ...
        #
        print_progress_bar ${BAR_WIDTH} ${i}
        echo -en "\r"
done

echo ""

exit
