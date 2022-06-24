#include "check_value.h"

#include "high_scores.h"

int main()
{
    const std::string high_scores_filename = "high_scores.txt";

    auto name = get_name();
    auto score = check_value();

    auto code = write_new_score(high_scores_filename, name, score);
    if (code != 0)
    {
        return code;
    }

    code = read_score_table(high_scores_filename);
    if (code != 0)
    {
        return code;
    }
}