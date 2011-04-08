#if 0
#include <stdio.h>

int main()
{
    int a = 12;
    printf("%d %d \n", a++, ++a);
}

    #include <stdio.h>

    main()    /* FORMATS.C   */
    {
        char          c = '#';
        static char s[] = "helloandwelcometoclanguage";

        printf("Characters:\n");
        printf("%.4X\n", 10);
        printf("%c\n", c);
        printf("%3c%3c\n", c, c);
        printf("%-3c%-3c\n", c, c);
        printf("Strings:\n");
        printf("%s\n", s);
        printf("%.5s\n", s);
        printf("%30s %s\n", "blahblah", "cool");
        printf("%30s %s\n", "bbaaaaaaaaaaabblllablahblah", "cool");
        printf("%20.5s\n", s);
        printf("%-20.5s\n", s);
        printf("%-30s %s\n", "blahblah", "cool");
        printf("%-30s %s\n", "bbaaaaaaaaaaabblllablahblah", "cool");
        printf("%-6.4f Secs %8.2f MillSecs %8ld MicroSecs\n", 3466/(1000.0*1000.0), 3466/1000.0, 3466);
        printf("%-6.4f Secs %8.2f MillSecs %8ld MicroSecs\n", 30/(1000.0*1000.0), 30/1000.0, 30);
        printf("%-6.4f Secs %8.2f MillSecs %8ld MicroSecs\n", 14411/(1000.0*1000.0), 14411/1000.0, 14411);
        printf("%-6.4f Secs %8.2f MillSecs %8ld MicroSecs\n", 5209817/(1000.0*1000.0), 5209817/1000.0, 5209817);
    }
#else
#include <stdio.h>

// Print to stdout
#define PrintToCapitalHexZeroPadded(value, numberOfZeroes) \
    printf("0x%."#numberOfZeroes"X\n", value)

#define PrintToSmallHexZeroPadded(value, numberOfZeroes) \
    printf("0x%."#numberOfZeroes"x\n", value)

#define PrintToIntZeroPadded(value, numberOfZeroes) \
    printf("%."#numberOfZeroes"d\n", value)

#define PrintToIntZeroPaddedV2(value, numberOfZeroes) \
    printf("%0"#numberOfZeroes"d\n", value)

#define PrintToStringSpacePaddedFront(value, numberOfSpaces) \
    printf("%"#numberOfSpaces"s\n", value)

#define PrintToStringSpacePaddedBack(value, numberOfSpaces) \
    printf("%-"#numberOfSpaces"s\n", value)


// Save in an array
#define SaveToCapitalHexZeroPadded(array, value, numberOfZeroes) \
    sprintf(array, "0x%."#numberOfZeroes"X", value)

#define SaveToSmallHexZeroPadded(array, value, numberOfZeroes) \
    sprintf(array, "0x%."#numberOfZeroes"x", value)

#define SaveToIntZeroPadded(array, value, numberOfZeroes) \
    sprintf(array, "%."#numberOfZeroes"d", value)

#define SaveToIntZeroPaddedV2(array, value, numberOfZeroes) \
    sprintf(array, "%0"#numberOfZeroes"d", value)

#define SaveToStringSpacePaddedFront(array, value, numberOfSpaces) \
    sprintf(array, "%"#numberOfSpaces"s", value)

#define SaveToStringSpacePaddedBack(array, value, numberOfSpaces) \
    sprintf(array, "%-"#numberOfSpaces"s", value)

#define TRACE(var, fmt) \
            printf("TRACE: " #var " = " #fmt "\n", var)


int main()
{
    char array[1024];

    PrintToCapitalHexZeroPadded(2, 4);
    PrintToCapitalHexZeroPadded('c', 4);
    PrintToCapitalHexZeroPadded(10, 4);
    printf("\n");

    PrintToSmallHexZeroPadded(2, 4);
    PrintToSmallHexZeroPadded('c', 4);
    PrintToSmallHexZeroPadded(10, 4);
    printf("\n");

    PrintToIntZeroPadded(0xA, 4);
    PrintToIntZeroPadded('c', 4);
    PrintToIntZeroPadded(10, 4);
    printf("\n");

    PrintToIntZeroPaddedV2(0xA, 4);
    PrintToIntZeroPaddedV2('c', 4);
    PrintToIntZeroPaddedV2(10, 4);
    printf("\n");

    PrintToStringSpacePaddedFront("Hello", 10);
    PrintToStringSpacePaddedFront("c", 10);
    PrintToStringSpacePaddedFront("coo", 10);
    printf("\n");

    PrintToStringSpacePaddedBack("Hello", 10);
    PrintToStringSpacePaddedBack("c", 10);
    PrintToStringSpacePaddedBack("coo", 10);
    printf("\n");

    SaveToCapitalHexZeroPadded(array, 2, 4);
    printf("Array value is %s\n", array);
    SaveToCapitalHexZeroPadded(array, 'c', 4);
    printf("Array value is %s\n", array);
    SaveToCapitalHexZeroPadded(array, 0, 4);
    printf("Array value is %s\n", array);
    printf("\n");

    SaveToSmallHexZeroPadded(array, 2, 4);
    printf("Array value is %s\n", array);
    SaveToSmallHexZeroPadded(array, 'c', 4);
    printf("Array value is %s\n", array);
    SaveToSmallHexZeroPadded(array, 10, 4);
    printf("Array value is %s\n", array);
    printf("\n");

    SaveToIntZeroPadded(array, 0xA, 4);
    printf("Array value is %s\n", array);
    SaveToIntZeroPadded(array, 'c', 4);
    printf("Array value is %s\n", array);
    SaveToIntZeroPadded(array, 10, 4);
    printf("Array value is %s\n", array);
    printf("\n");

    SaveToIntZeroPaddedV2(array, 0xA, 4);
    printf("Array value is %s\n", array);
    SaveToIntZeroPaddedV2(array, 'c', 4);
    printf("Array value is %s\n", array);
    SaveToIntZeroPaddedV2(array, 10, 4);
    printf("Array value is %s\n", array);
    printf("\n");

    SaveToStringSpacePaddedFront(array, "Hello", 10);
    printf("Array value is %s\n", array);
    SaveToStringSpacePaddedFront(array, "c", 10);
    printf("Array value is %s\n", array);
    SaveToStringSpacePaddedFront(array, "coo", 10);
    printf("Array value is %s\n", array);
    printf("\n");

    SaveToStringSpacePaddedBack(array, "Hello", 10);
    printf("Array value is %s\n", array);
    SaveToStringSpacePaddedBack(array, "c", 10);
    printf("Array value is %s\n", array);
    SaveToStringSpacePaddedBack(array, "coo", 10);
    printf("Array value is %s\n", array);
    printf("\n");

    int var = 2;
    TRACE(var, %d);
}
#endif
