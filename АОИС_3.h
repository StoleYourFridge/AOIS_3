#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include <list>

using namespace std;

bool checker_for_own_input(string& function);
int priority(char symbol);
void translate(string& function);
bool summary(bool first, bool  second);
bool decrypt_function_to_bool(string& function, vector<bool>& triple);
pair< vector<vector<bool>>, vector<vector<bool >>> transformator(string& name);

vector<bool> digitization(int number);
bool checker_for_index(string& index);
pair< vector<vector<bool>>, vector<vector<bool >>> index_to_skdnf(string& string_index);

bool checker_for_numeral(string& sdnf_string);
pair<vector<int>, vector<int>> from_string_to_numeral(string& sdnf_string);
pair< vector<vector<bool>>, vector<vector<bool >>> numeral_to_skdnf(vector<int>numeralsdnf, vector<int>numeralsknf);

void vec_print(vector<bool>term);
void sdnfprint(vector<vector<bool>> sdnfprototype);
void sknfprint(vector<vector<bool>> sknfprototype);
string from_implicants_to_sdnf_string(vector<vector<pair<int, bool>>>& sdnf_implicants);
string from_implicants_to_sknf_string(vector<vector<pair<int, bool>>>& sknf_implicants);

bool checker_for_coincidence(vector<bool>& term_one, vector<bool>& term_two);
vector<pair<int, bool>> implicant(vector<bool>& term_one, vector<bool>& term_two);
vector<vector<pair<int, bool>>> gluing(vector<vector<bool>>& sdnfprototype);

int checker_for_calculate_method_skdnf(vector<pair<int, bool>> term_one, vector<pair<int, bool>> term_two, bool is_it_sdnf);
void calculate_method_from_skdnf(vector<vector<pair<int, bool>>>& implicants, bool is_it_sdnf);
pair<string, string> calculate_method(vector<vector<bool>>& sdnfprototype, vector<vector<bool>>& sknfprototype);

bool checker_for_implicant_and_constituent(vector<bool>& constituent, vector<pair<int, bool>>& implicant);
pair<vector<vector<bool>>, vector<int>> table_of_crosses(vector<vector<bool>>& sdnfprototype, vector<vector<pair<int, bool>>>& implicants);
void one_line_deleting(vector<vector<bool>>& table, int line, int& current_amount_of_cleaning_crosses);
bool table_checker(vector<vector<bool>> table);
void creator_for_set_of_exceptions(map<int, bool>visited, vector<vector<bool>> table, int number_of_cleaning_line, vector<int>& main_line_for_result, vector<int>current_line_for_result, int& main_amount_of_crosses, int current_amount_of_crosses);
vector<int> set_of_exceptions(vector<vector<bool>> table, int number_of_start_implicant, map<int, bool> visited);
vector<int> result_exeption(vector<vector<bool>> table, vector<int> numbers_of_correct_implicants);
void exceptioned_implicants(vector<vector<pair<int, bool>>>& implicants, vector<int> exception);
pair<string, string> calculate_table_method(vector<vector<bool>>& sdnfprototype, vector<vector<bool>>& sknfprototype);

struct map_square
{
    bool sign;
    int amount_of_meetings = 0;
    vector<bool> code;
};
bool is_there_one_checker(vector<bool>vertical, vector<bool> horizontal, vector<vector<bool>>& sdnfprototype, vector<bool>& is_there_one);
vector<vector<map_square>> karnaugh_map_builder_sdnf(vector<vector<bool>>& sdnfprototype, vector<vector<bool>>& sknfprototype);
vector<map_square*> neighbor_builder(int i, int j, vector<vector<map_square>>& karnaugh_map, bool is_it_sdnf);
void compare_with_neighbors(int i, int j, vector<vector<map_square>>& karnaugh_map, vector<vector<pair<int, bool>>>& result, bool is_it_sdnf);
vector<vector<pair<int, bool>>> from_map_to_implicants(vector<vector<map_square>>& karnaugh_map, bool is_it_sdnf);
pair<string, string> res_table_method(vector<vector<bool>>& sdnfprototype, vector<vector<bool>>& sknfprototype);
pair<string, string> table_method(vector<vector<bool>>& sdnfprototype, vector<vector<bool>>& sknfprototype);

bool Test1();
bool Test2();
bool Test3();
bool Test4();
bool Test5();
bool Test6();
bool Test7();
bool Test8();
bool Test9();
bool Test10();
bool Test11();
bool Test12();
void tests();
void our_own_input();
