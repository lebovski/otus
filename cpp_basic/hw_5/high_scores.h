#pragma once

#include <string>

std::string get_name();
int write_new_score(std::string high_scores_filename, std::string user_name, int attempts_count);
int read_score_table(std::string high_scores_filename);