#include "check_value.h"
#include "high_scores.h"
#include "argument.h"

#include <iostream>

int main(int argc, char **argv)
{
    const std::string high_scores_filename = "high_scores.txt";
    int max{100};
    bool table{false};

    auto code = parce_args(argc, argv, &max, &table);
    if (code != 0)
    {
        return code;
    }

    if (!table)
    {
        auto name = get_name();
        auto score = check_value(max);

        code = write_new_score(high_scores_filename, name, score);
        if (code != 0)
        {
            return code;
        }
    }

    code = read_score_table(high_scores_filename);
    if (code != 0)
    {
        return code;
    }
}