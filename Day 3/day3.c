#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <regex.h>
#include <string.h>

int main() {
    FILE* file = fopen("input.txt", "rt");
    assert(file);

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char*)malloc(fileSize + 1);
    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';

    fclose(file);

    const char *patternMul = "mul\\([0-9]+,[0-9]+\\)";
    const char *patternDo = "do\\(\\)";
    const char *patternDont = "don't\\(\\)";

    regex_t regexMul, regexDo, regexDont;
    int ret = regcomp(&regexMul, patternMul, REG_EXTENDED);
    assert(ret == 0);

    ret = regcomp(&regexDo, patternDo, REG_EXTENDED);
    assert(ret == 0);

    ret = regcomp(&regexDont, patternDont, REG_EXTENDED);
    assert(ret == 0);

    regmatch_t pmatch[1];
    const char *start = buffer;

    long sum = 0;
    int mulEnable = 1;

    while (*start != '\0') {
        ret = regexec(&regexMul, start, 1, pmatch, 0);

        if (ret == 0) {
            char matchedString[pmatch[0].rm_eo - pmatch[0].rm_so + 1];
            strncpy(matchedString, start + pmatch[0].rm_so, pmatch[0].rm_eo - pmatch[0].rm_so);
            matchedString[pmatch[0].rm_eo - pmatch[0].rm_so] = '\0';

            if (mulEnable) {
                int num1 = 0, num2 = 0;
                sscanf(matchedString, "mul(%d,%d)", &num1, &num2);
                sum += num1 * num2;
            }

            start += pmatch[0].rm_eo;
            continue;
        }

        ret = regexec(&regexDo, start, 1, pmatch, 0);

        if (ret == 0) {
            mulEnable = 1;
            start += pmatch[0].rm_eo;
            continue;
        }

        ret = regexec(&regexDont, start, 1, pmatch, 0);

        if (ret == 0) {
            mulEnable = 0;
            start += pmatch[0].rm_eo;
            continue;
        }

        start++;
    }

    printf("Sum: %d\n", sum);

    regfree(&regexMul);
    regfree(&regexDo);
    regfree(&regexDont);
    free(buffer);
    buffer = NULL;

    return 0;
}