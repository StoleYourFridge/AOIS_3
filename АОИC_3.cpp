#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include <list>

using namespace std;

//traslation functions
bool checker_for_own_input(string& function)
{
    int counter = 0, i = 0;
    while (!function.empty() && i < function.size())
    {
        if (function[i] == ' ') {
            function.erase(function.begin() + i);
            continue;
        }
        i++;
    }
    if (!function.size()) return false;
    if (function[0] != 'a' && function[0] != 'b' && function[0] != 'c' && function[0] != '(' && function[0] != '!') return false;
    for (int i = 0; i < function.size() - 1; i++)
    {
        if (function[i] == 'a' || function[i] == 'b' || function[i] == 'c') {
            if (function[i + 1] != '*' && function[i + 1] != '+' && function[i + 1] != ')') return false;
        }
        else if (function[i] == '!') {
            if (function[i + 1] != 'a' && function[i + 1] != 'b' && function[i + 1] != 'c' && function[i + 1] != '(') return false;
        }
        else if (function[i] == '*' && function[i] == '+') {
            if (function[i + 1] != 'a' && function[i + 1] != 'b' && function[i + 1] != 'c' && function[i + 1] != '(' && function[i + 1] != '!') return false;
        }
        if (function[i] == '(') {
            counter++;
            if (function[i + 1] != 'a' && function[i + 1] != 'b' && function[i + 1] != 'c' && function[i + 1] != '!' && function[i + 1] != '(') return false;
        }
        else if (function[i] == ')') {
            counter--;
            if (function[i + 1] != '+' && function[i + 1] != '*' && function[i + 1] != ')') return false;
        }
    }
    i = function.size() - 1;
    if (function[i] != 'a' && function[i] != 'b' && function[i] != 'c' && function[i] != ')') return false;
    if (function[i] == ')') counter--;
    if (counter != 0) return false;
    return true;
}
int priority(char symbol)
{
    if (symbol == '!') return 4;
    else if (symbol == '*') return 3;
    else if (symbol == '+') return 2;
    return 1;
}
void translate(string& function)
{
    string result;
    stack<char>stack;
    for (int i = 0; i < function.size(); i++)
    {
        if (function[i] == 'a' || function[i] == 'b' || function[i] == 'c') {
            result.push_back(function[i]);
        }
        else if (function[i] == '(') stack.push(function[i]);
        else if (function[i] == ')') {
            while (stack.top() != '(')
            {
                result.push_back(stack.top());
                stack.pop();
            }
            stack.pop();
        }
        else if (function[i] == '!') stack.push(function[i]);
        else if (function[i] == '+' || function[i] == '*') {
            while (!stack.empty() && priority(stack.top()) >= priority(function[i])) {
                result.push_back(stack.top());
                stack.pop();
            }
            stack.push(function[i]);
        }
    }
    while (!stack.empty()) {
        result.push_back(stack.top());
        stack.pop();
    }
    function = result;
}
bool summary(bool first, bool  second)
{
    if (first && second) return true;
    else return (first + second);
}
bool decrypt_function_to_bool(string& function, vector<bool>& triple)
{
    stack<bool>result;
    bool first, second;
    for (int i = 0; i < function.size(); i++)
    {
        if (function[i] == 'a') result.push(triple[0]);
        else if (function[i] == 'b') result.push(triple[1]);
        else if (function[i] == 'c') result.push(triple[2]);
        else if (function[i] == '!') {
            first = result.top();
            result.pop();
            result.push(!first);
        }
        else if (function[i] == '+') {
            first = result.top();
            result.pop();
            second = result.top();
            result.pop();
            result.push(summary(first, second));
        }
        else if (function[i] == '*') {
            first = result.top();
            result.pop();
            second = result.top();
            result.pop();
            result.push(first * second);
        }
    }
    return result.top();
}
pair< vector<vector<bool>>, vector<vector<bool >>> transformator(string& name)
{
    vector<vector<bool>> data{ {0,0,0},{0,0,1},{0,1,0},{0,1,1},{1,0,0},{1,0,1},{1,1,0},{1,1,1} };
    vector<vector<bool>> sdnfprototype;
    vector<vector<bool>> sknfprototype;
    vector<bool>number;
    translate(name);
    int index;
    for (int i = 0; i < data.size(); i++)
    {
        if (decrypt_function_to_bool(name, data[i])) {
            sdnfprototype.push_back(data[i]);
            number.push_back(1);
        }
        else {
            sknfprototype.push_back(data[i]);
            number.push_back(0);
        }
    }
    pair< vector<vector<bool>>, vector<vector<bool >>> output(sdnfprototype, sknfprototype);
    return output;
}

vector<bool> digitization(int number)
{
    vector<bool> result;
    while (true)
    {
        if (!number)
        {
            result.insert(result.begin(), 0);
            break;
        }
        if (number != 1) {
            result.insert(result.begin(), number % 2);
        }
        else {
            result.insert(result.begin(), 1);
            break;
        }
        number /= 2;
    }
    return result;
}
bool checker_for_index(string& index)
{
    if (index.size() > 3) return false;
    for (int i = 0; i < index.size(); i++)
    {
        if (index[i] != '1' && index[i] != '2' && index[i] != '3' && index[i] != '4' && index[i] != '5' && index[i] != '6' && index[i] != '7' && index[i] != '8' && index[i] != '9' && index[i] != '0')
            return false;
    }
    if (stoi(index) > 255) return false;
    return true;
}
pair< vector<vector<bool>>, vector<vector<bool >>> index_to_skdnf(string& string_index)
{
    int index = stoi(string_index);
    vector<vector<bool>> data{ {0,0,0},{0,0,1},{0,1,0},{0,1,1},{1,0,0},{1,0,1},{1,1,0},{1,1,1} };
    vector<vector<bool>> sdnfprototype;
    vector<vector<bool>> sknfprototype;
    vector<bool>binaryindex = digitization(index);
    while (binaryindex.size() < 8)
    {
        binaryindex.insert(binaryindex.begin(), 0);
    }
    for (int i = 0; i < binaryindex.size(); i++)
    {
        if (binaryindex[i]) sdnfprototype.push_back(data[i]);
        else sknfprototype.push_back(data[i]);
    }
    pair< vector<vector<bool>>, vector<vector<bool >>> output(sdnfprototype, sknfprototype);
    return output;
}

bool checker_for_numeral(string& sdnf_string)
{
    int i = 0;
    map<char, bool> number_checker;
    while (!sdnf_string.empty() && i < sdnf_string.size())
    {
        if (sdnf_string[i] == ' ') {
            sdnf_string.erase(sdnf_string.begin() + i);
            continue;
        }
        i++;
    }
    if (!(sdnf_string[0] == '(' && sdnf_string[sdnf_string.size() - 1] == ')') || sdnf_string.size() < 3) return false;
    for (int i = 1; i < sdnf_string.size() - 1; i++)
    {
        if (sdnf_string[i] == '0' || sdnf_string[i] == '1' || sdnf_string[i] == '2' || sdnf_string[i] == '3' || sdnf_string[i] == '4' || sdnf_string[i] == '5' || sdnf_string[i] == '6' || sdnf_string[i] == '7') {
            if (sdnf_string[i + 1] != ')' && sdnf_string[i + 1] != ',') return false;
            if (number_checker[sdnf_string[i]]) return false;
            else number_checker[sdnf_string[i]] = true;
        }
        else if (sdnf_string[i] == ',') {
            if (sdnf_string[i + 1] != '0' && sdnf_string[i + 1] != '1' && sdnf_string[i + 1] != '2' && sdnf_string[i + 1] != '3' && sdnf_string[i + 1] != '4' && sdnf_string[i + 1] != '5' && sdnf_string[i + 1] != '6' && sdnf_string[i + 1] != '7')  return false;
        }
        else return false;
    }
    return true;
}
pair<vector<int>, vector<int>> from_string_to_numeral(string& sdnf_string)
{
    vector<int>numeral_sdnf, numeral_sknf{ 0,1,2,3,4,5,6,7 };
    int i = 1;
    while (i <  sdnf_string.size() && (sdnf_string[i+1] == ',' || sdnf_string[i+1] == ')'))
    {
        if (sdnf_string[i] == '1') numeral_sdnf.push_back(1);
        else if(sdnf_string[i] == '2') numeral_sdnf.push_back(2);
        else if (sdnf_string[i] == '3') numeral_sdnf.push_back(3);
        else if (sdnf_string[i] == '4') numeral_sdnf.push_back(4);
        else if (sdnf_string[i] == '5') numeral_sdnf.push_back(5);
        else if (sdnf_string[i] == '6') numeral_sdnf.push_back(6);
        else if (sdnf_string[i] == '7') numeral_sdnf.push_back(7);
        else if (sdnf_string[i] == '0') numeral_sdnf.push_back(0);
        i += 2;
    }
    
    for (int i = 0; i < numeral_sdnf.size(); i++)
    {
        for (int j = 0; j < numeral_sknf.size(); j++)
        {
            if (numeral_sknf[j] == numeral_sdnf[i]) {
                numeral_sknf.erase(numeral_sknf.begin() + j);
                break;
            }
        }
    }
    pair<vector<int>, vector<int>> output(numeral_sdnf, numeral_sknf);
    return output;
}
pair< vector<vector<bool>>, vector<vector<bool >>> numeral_to_skdnf(vector<int>numeralsdnf, vector<int>numeralsknf)
{
    vector<vector<bool>> sdnfprototype;
    vector<vector<bool>> sknfprototype;
    vector<bool> tool;
    for (int i = 0; i < numeralsdnf.size(); i++)
    {
        tool = digitization(numeralsdnf[i]);
        while (tool.size() < 3) 
        {
            tool.insert(tool.begin(), 0);
        }
        sdnfprototype.push_back(tool);
    }
    for (int i = 0; i < numeralsknf.size(); i++)
    {
        tool = digitization(numeralsknf[i]);
        while (tool.size() < 3)
        {
            tool.insert(tool.begin(), 0);
        }
        sknfprototype.push_back(tool);
    }
    pair< vector<vector<bool>>, vector<vector<bool >>> output(sdnfprototype, sknfprototype);
    return output;
}

//print sdnf and sknf functions 
void vec_print(vector<bool>term)
{
    for (int i = 0; i < term.size(); i++)
    {
        cout << term[i];
    }
}
void sdnfprint(vector<vector<bool>> sdnfprototype)
{
    cout << "F(sdnf)(a,b,c) = ";
    for (int i = 0; i < sdnfprototype.size(); i++)
    {
        cout << "(";
        if (sdnfprototype[i][0]) cout << "a*";
        else cout << "!a*";
        if (sdnfprototype[i][1]) cout << "b*";
        else cout << "!b*";
        if (sdnfprototype[i][2]) cout << "c";
        else cout << "!c";
        cout << ")";
        if (i != (sdnfprototype.size() - 1)) cout << " + ";

    }
    cout << ";" << endl;
}
void sknfprint(vector<vector<bool>> sknfprototype)
{
    cout << "F(sknf)(a,b,c) = ";
    for (int i = 0; i < sknfprototype.size(); i++)
    {
        cout << "(";
        if (!sknfprototype[i][0]) cout << "a+";
        else cout << "!a+";
        if (!sknfprototype[i][1]) cout << "b+";
        else cout << "!b+";
        if (!sknfprototype[i][2]) cout << "c";
        else cout << "!c";
        cout << ")";
        if (i != (sknfprototype.size() - 1)) cout << " * ";
    }
    cout << ";" << endl;
}
string from_implicants_to_sdnf_string(vector<vector<pair<int, bool>>>& sdnf_implicants)
{
    string output;
    for (int i = 0; i < sdnf_implicants.size(); i++)
    {
        output += "(";
        for (int j = 0; j < sdnf_implicants[i].size(); j++)
        {
            if (sdnf_implicants[i][j].first == 0) {
                if (sdnf_implicants[i][j].second) output += "a";
                else output += "!a";
            }
            else if (sdnf_implicants[i][j].first == 1) {
                if (sdnf_implicants[i][j].second) output += "b";
                else output += "!b";
            }
            else if (sdnf_implicants[i][j].first == 2) {
                if (sdnf_implicants[i][j].second) output += "c";
                else output += "!c";
            }
            if (j != sdnf_implicants[i].size() - 1) output += "*";
        }
        output += ") ";
        if (i != sdnf_implicants.size() - 1) output += "+";
    }
    return output;
}
string from_implicants_to_sknf_string(vector<vector<pair<int, bool>>>& sknf_implicants)
{
    string output;
    for (int i = 0; i < sknf_implicants.size(); i++)
    {
        output += "(";
        for (int j = 0; j < sknf_implicants[i].size(); j++)
        {
            if (sknf_implicants[i][j].first == 0) {
                if (sknf_implicants[i][j].second) output += "!a";
                else output += "a";
            }
            else if (sknf_implicants[i][j].first == 1) {
                if (sknf_implicants[i][j].second) output += "!b";
                else output += "b";
            }
            else if (sknf_implicants[i][j].first == 2) {
                if (sknf_implicants[i][j].second) output += "!c";
                else output += "c";
            }
            if (j != sknf_implicants[i].size() - 1) output += "+";
        }
        output += ") ";
        if (i != sknf_implicants.size() - 1) output += "*";
    }
    return output;
}

bool checker_for_coincidence(vector<bool>& term_one, vector<bool>& term_two)
{
    int counter_of_coincidence = 0, neccesary_coincidence;
    if (term_one.size() >= term_two.size()) neccesary_coincidence = term_one.size() - 1;
    else neccesary_coincidence = term_two.size() - 1;
    for (int i = 0; i < term_one.size(); i++)
    {
        if(i < term_two.size() && term_one[i] == term_two[i]) counter_of_coincidence++;
    }
    if (counter_of_coincidence == neccesary_coincidence) return true;
    else return false;
}
vector<pair<int, bool>> implicant(vector<bool>& term_one, vector<bool>& term_two)
{
    vector<pair<int, bool>> implicant;
    pair<int, bool> example;
    for (int i = 0; i < term_one.size(); i++)
    {
        if (term_one[i] == term_two[i]) {
            example.first = i;
            example.second = term_one[i];
            implicant.push_back(example);
        }
    }
    return implicant;
}
vector<vector<pair<int, bool>>> gluing(vector<vector<bool>> &sdnfprototype)
{
    vector<bool> constituent_checker(sdnfprototype.size(), 0);
    vector<vector<pair<int, bool>>> result;
    vector<pair<int, bool>> implicant_ex;
    map< vector<pair<int, bool>>, bool> checker;
    for (int i = 0; i < sdnfprototype.size(); i++)
    {
        for (int j = i + 1; j < sdnfprototype.size(); j++)
        {
            if (checker_for_coincidence(sdnfprototype[i], sdnfprototype[j])) {
                implicant_ex = implicant(sdnfprototype[i], sdnfprototype[j]);
                if (!checker[implicant_ex]) {
                    result.push_back(implicant_ex);
                    checker[implicant_ex] = true;
                }
                constituent_checker[i] = true;
                constituent_checker[j] = true;
            }
        }
        if (!constituent_checker[i]) {
            vector<pair<int, bool>> addition;
            for (int k = 0; k < sdnfprototype[i].size(); k++)
            {
                pair<int, bool> example;
                example.first = k;
                example.second = sdnfprototype[i][k];
                addition.push_back(example);
            }
            result.push_back(addition);
        }
    }
    return result;
}

int checker_for_calculate_method_skdnf(vector<pair<int, bool>> term_one, vector<pair<int, bool>> term_two, bool is_it_sdnf)
{
    int mind;
    if (is_it_sdnf) mind = 1;
    else mind = 0;
    for (int i = 0; i < term_two.size(); i++)
    {
        bool overlap = false;
        if (!is_it_sdnf) term_two[i].second = abs(term_two[i].second - 1);
        for (int j = 0; j < term_one.size(); j++)
        {
            if (term_two[i].first == term_one[j].first) {
                overlap = true;
                if (is_it_sdnf){
                    if ((term_one[i].second && !term_two[j].second) || (!term_one[i].second && term_two[j].second)) return 0;
                }
                else{
                    if ((!term_one[i].second && !term_two[j].second) || (term_one[i].second && term_two[j].second)) return 1;
                }
            }
        }
        if (!overlap) {
            if (term_two[i].second) mind = 2;
            else mind = -2;
        }
    }
    return mind;
}
void calculate_method_from_skdnf(vector<vector<pair<int, bool>>> &implicants, bool is_it_sdnf)
{
    bool stop_sign = true;
    while (stop_sign)
    {
        stop_sign = false;
        for (int i = 0; i < implicants.size(); i++)
        {
            bool flag = true;
            int amount_of_minuses = 0, amount_of_pluses = 0, result_for_checker;
            for (int j = 0; j < implicants.size(); j++)
            {
                if (j == i) continue;
                result_for_checker = checker_for_calculate_method_skdnf(implicants[i], implicants[j], is_it_sdnf);
                if ((result_for_checker == 1 && is_it_sdnf) || (result_for_checker == 0 && !is_it_sdnf)) flag = false;
                else if (result_for_checker == 2) amount_of_pluses++;
                else if (result_for_checker == -2) amount_of_minuses++;
            }
            if (amount_of_pluses != 0 && amount_of_minuses != 0) flag = false;
            if (!flag) {
                stop_sign = true;
                implicants.erase(implicants.begin() + i);
                break;
            }
        }
    }
}
pair<string, string> calculate_method(vector<vector<bool>>& sdnfprototype, vector<vector<bool>>& sknfprototype)
{
    vector<vector<pair<int, bool>>> sdnf_implicants, sknf_implicants;
    sdnf_implicants = gluing(sdnfprototype);
    sknf_implicants = gluing(sknfprototype);
    string current_sdnf = from_implicants_to_sdnf_string(sdnf_implicants);
    string current_sknf = from_implicants_to_sknf_string(sknf_implicants);
    calculate_method_from_skdnf(sdnf_implicants, true);
    calculate_method_from_skdnf(sknf_implicants, false);
    string minimized_sdnf = from_implicants_to_sdnf_string(sdnf_implicants);
    string minimized_sknf = from_implicants_to_sknf_string(sknf_implicants);
    pair<string, string> result(minimized_sdnf, minimized_sknf);
    return result;
}

bool checker_for_implicant_and_constituent(vector<bool>& constituent, vector<pair<int, bool>>& implicant)
{
    int counter = 0;
    for (int i = 0; i < implicant.size(); i++)
    {
        if (implicant[i].second == constituent[implicant[i].first]) counter++;
    }
    if (counter == implicant.size()) return true;
    else return false;
}
pair<vector<vector<bool>>, vector<int>> table_of_crosses(vector<vector<bool>>& sdnfprototype, vector<vector<pair<int, bool>>>& implicants)
{
    vector<vector<bool>> result;
    vector<int> future_result_of_operation;
    for (int i = 0; i < sdnfprototype.size(); i++)
    {
        vector<bool> line_for_constituent;
        int summary_for_the_line = 0, unique_implicant;
        for (int j = 0; j < implicants.size(); j++)
        {
            bool result_for_comparison = checker_for_implicant_and_constituent(sdnfprototype[i], implicants[j]);
            if (result_for_comparison) unique_implicant = j;
            line_for_constituent.push_back(result_for_comparison);
            summary_for_the_line += result_for_comparison;
        }
        if (summary_for_the_line == 1) future_result_of_operation.push_back(unique_implicant);
        else result.push_back(line_for_constituent);
    }
    pair<vector<vector<bool>>, vector<int>> future_result_and_table(result, future_result_of_operation);
    return future_result_and_table;
}
void one_line_deleting(vector<vector<bool>>& table, int line, int& current_amount_of_cleaning_crosses)
{
    for (int i = 0; i < table.size(); i++)
    {
        if (table[i][line]) {
            current_amount_of_cleaning_crosses++;
            table[i][line] = 0;
        }
    }
}
bool table_checker(vector<vector<bool>> table)
{
    for (int i = 0; i < table.size(); i++)
    {
        bool zero_sign = false;
        for (int j = 0; j < table[i].size(); j++)
        {
            if (table[i][j]) {
                zero_sign = true;
                break;
            }
        }
        if (!zero_sign) {
            return false;
        }
    }
    return true;
}
void creator_for_set_of_exceptions(map<int, bool>visited, vector<vector<bool>> table, int number_of_cleaning_line, vector<int>& main_line_for_result, vector<int>current_line_for_result, int& main_amount_of_crosses, int current_amount_of_crosses)
{
    one_line_deleting(table, number_of_cleaning_line, current_amount_of_crosses);
    if (table_checker(table)) {
        visited[number_of_cleaning_line] = true;
        current_line_for_result.push_back(number_of_cleaning_line);
        if ((main_line_for_result.size() < current_line_for_result.size()) && (main_amount_of_crosses < current_amount_of_crosses)) {
            main_line_for_result = current_line_for_result;
            main_amount_of_crosses = current_amount_of_crosses;
        }
        for (int i = 0; i < table[0].size(); i++)
        {
            if (!visited[i]) creator_for_set_of_exceptions(visited, table, i, main_line_for_result, current_line_for_result, main_amount_of_crosses, current_amount_of_crosses);
        }
    }
    else return;
}
vector<int> set_of_exceptions(vector<vector<bool>> table, int number_of_start_implicant, map<int, bool> visited)
{
    vector<int>main_line, current_line;
    int current_amount_of_cleanning_crosses = 0, main_amount_of_cleanning_crosses = 0;
    creator_for_set_of_exceptions(visited, table, number_of_start_implicant, main_line, current_line, main_amount_of_cleanning_crosses, current_amount_of_cleanning_crosses);
    return main_line;
}
vector<int> result_exeption(vector<vector<bool>> table, vector<int> numbers_of_correct_implicants)
{
    vector<int> result;
    map<int, bool> visited;
    for (int i = 0; i < numbers_of_correct_implicants.size(); i++)
    {
        visited[numbers_of_correct_implicants[i]] = true;
    }
    if (table.size() != 0) {
        for (int i = 0; i < table[0].size(); i++)
        {
            if (!visited[i]) {
                vector<int> current_result = set_of_exceptions(table, i, visited);
                if (current_result.size() > result.size()) result = current_result;
            }
        }
    }
    return result;
}
void exceptioned_implicants(vector<vector<pair<int, bool>>>& implicants, vector<int> exception)
{
    vector<vector<pair<int, bool>>> result_implicants;
    for (int i = 0; i < implicants.size(); i++)
    {
        bool sign = true;
        for (int j = 0; j < exception.size(); j++)
        {
            if (i == exception[j]) sign = false;
        }
        if (sign) result_implicants.push_back(implicants[i]);
    }
    implicants = result_implicants;
}
pair<string, string> calculate_table_method(vector<vector<bool>>& sdnfprototype, vector<vector<bool>>& sknfprototype)
{
    vector<vector<pair<int, bool>>> sdnf_implicants, sknf_implicants;
    sdnf_implicants = gluing(sdnfprototype);
    sknf_implicants = gluing(sknfprototype);
    pair<vector<vector<bool>>, vector<int>> table_and_one_cross_implicants_sdnf = table_of_crosses(sdnfprototype, sdnf_implicants);
    pair<vector<vector<bool>>, vector<int>> table_and_one_cross_implicants_sknf = table_of_crosses(sknfprototype, sknf_implicants);
    string current_sdnf = from_implicants_to_sdnf_string(sdnf_implicants);
    string current_sknf = from_implicants_to_sknf_string(sknf_implicants);
    vector<int> exception_sdnf = result_exeption(table_and_one_cross_implicants_sdnf.first, table_and_one_cross_implicants_sdnf.second);
    vector<int> exception_sknf = result_exeption(table_and_one_cross_implicants_sknf.first, table_and_one_cross_implicants_sknf.second);
    exceptioned_implicants(sdnf_implicants, exception_sdnf);
    exceptioned_implicants(sknf_implicants, exception_sknf);
    string minimized_sdnf = from_implicants_to_sdnf_string(sdnf_implicants);
    string minimized_sknf = from_implicants_to_sknf_string(sknf_implicants);
    pair<string, string> result(minimized_sdnf, minimized_sknf);
    return result;
}

struct map_square
{
    bool sign;
    int amount_of_meetings = 0;
    vector<bool> code;
};
bool is_there_one_checker(vector<bool>vertical, vector<bool> horizontal, vector<vector<bool>>& sdnfprototype, vector<bool>&is_there_one)
{
    for (int i = 0; i < vertical.size(); i++) is_there_one.push_back(vertical[i]);
    for (int i = 0; i < horizontal.size(); i++) is_there_one.push_back(horizontal[i]);
    for (int i = 0; i < sdnfprototype.size(); i++)
    {
        if (is_there_one == sdnfprototype[i]) return true;
    }
    return false;
}
vector<vector<map_square>> karnaugh_map_builder_sdnf(vector<vector<bool>>& sdnfprototype, vector<vector<bool>>& sknfprototype)
{
    int constituent_size;
    if (sdnfprototype.size() != 0) constituent_size = sdnfprototype[0].size();
    else constituent_size = sknfprototype[0].size();
    vector<vector<bool>> one_veriable{ {0}, {1} }, two_veriables{ {0,0}, {0,1}, {1,1}, {1,0} }, three_veriables{ {0,0,0}, {0,0,1}, {0,1,1}, {0,1,0}, {1,1,0 }, {1,1,1}, {1,0,1}, {1,0,0} }, vertical_veriables, horizontal_veriables;
    if (constituent_size == 3) {
        vertical_veriables = one_veriable;
        horizontal_veriables = two_veriables;
    }
    else if (constituent_size == 4) {
        vertical_veriables = two_veriables;
        horizontal_veriables = two_veriables;
    }
    else if (constituent_size == 5) {
        vertical_veriables = two_veriables;
        horizontal_veriables = three_veriables;
    }
    vector<vector<map_square>> Karnaugh_map;
    for (int i = 0; i < horizontal_veriables.size(); i++)
    {
        vector<map_square>example;
        for (int j = 0; j < vertical_veriables.size(); j++)
        {
            map_square square;
            vector<bool>is_there_one;
            square.sign = is_there_one_checker(vertical_veriables[j], horizontal_veriables[i], sdnfprototype, is_there_one);
            square.code = is_there_one;
            example.push_back(square);
        }
        Karnaugh_map.push_back(example);
    }
    return Karnaugh_map;
}
vector<map_square*> neighbor_builder(int i, int j, vector<vector<map_square>>& karnaugh_map, bool is_it_sdnf)
{
    vector<map_square*> neighbors;
    int up, down, left, right;
    if (i == 0) left = karnaugh_map.size() - 1;
    else left = i - 1;
    if (i == karnaugh_map.size() - 1) right = 0;
    else right = i + 1;
    if (j == 0) up = karnaugh_map[0].size() - 1;
    else up = j - 1;
    if (j == karnaugh_map[0].size() - 1) down = 0;
    else down = j + 1;
    if (karnaugh_map[left][j].sign == is_it_sdnf) neighbors.push_back(&karnaugh_map[left][j]);
    if (karnaugh_map[i][down].sign == is_it_sdnf) neighbors.push_back(&karnaugh_map[i][down]);
    if (karnaugh_map[right][j].sign == is_it_sdnf) neighbors.push_back(&karnaugh_map[right][j]);
    if (karnaugh_map[i][up].sign == is_it_sdnf) neighbors.push_back(&karnaugh_map[i][up]);
    return neighbors;
}
void compare_with_neighbors(int i, int j, vector<vector<map_square>>& karnaugh_map, vector<vector<pair<int, bool>>> &result, bool is_it_sdnf)
{
    vector<map_square*> neighbors = neighbor_builder(i, j, karnaugh_map, is_it_sdnf);
    if (neighbors.size() == 0) {
        result.push_back(implicant(karnaugh_map[i][j].code, karnaugh_map[i][j].code));
    }
    else {
        bool overlap = false;
        pair<int, map_square*> minimum_meetings(neighbors[0]->amount_of_meetings, neighbors[0]);
        for (int k = 0; k < neighbors.size(); k++)
        {
            if (neighbors[k]->amount_of_meetings == 0) {
                overlap = true;
                result.push_back(implicant(karnaugh_map[i][j].code, neighbors[k]->code));
                karnaugh_map[i][j].amount_of_meetings++;
                neighbors[k]->amount_of_meetings++;
            }
            if (neighbors[k]->amount_of_meetings < minimum_meetings.first) {
                    minimum_meetings.first = neighbors[k]->amount_of_meetings;
                    minimum_meetings.second = neighbors[k];
            }
        }
        if (!overlap) {
            result.push_back(implicant(karnaugh_map[i][j].code, minimum_meetings.second->code));
            karnaugh_map[i][j].amount_of_meetings++;
            minimum_meetings.second->amount_of_meetings++;
        }
    }
}
vector<vector<pair<int, bool>>> from_map_to_implicants(vector<vector<map_square>> &karnaugh_map, bool is_it_sdnf)
{
    vector<vector<pair<int, bool>>> result;
    for (int j = 0; j < karnaugh_map[0].size(); j++)
    {
        for (int i = 0; i < karnaugh_map.size(); i++)
        {
            if (karnaugh_map[i][j].sign == is_it_sdnf && karnaugh_map[i][j].amount_of_meetings == 0) {
                compare_with_neighbors(i, j, karnaugh_map, result, is_it_sdnf);
            }
        }
    }
    return result;
}
pair<string, string> res_table_method(vector<vector<bool>>& sdnfprototype, vector<vector<bool>>& sknfprototype)
{
    vector<vector<pair<int, bool>>> sdnf_implicants, sknf_implicants;
    sdnf_implicants = gluing(sdnfprototype);
    sknf_implicants = gluing(sknfprototype);
    pair<vector<vector<bool>>, vector<int>> table_and_one_cross_implicants_sdnf = table_of_crosses(sdnfprototype, sdnf_implicants);
    pair<vector<vector<bool>>, vector<int>> table_and_one_cross_implicants_sknf = table_of_crosses(sknfprototype, sknf_implicants);
    string current_sdnf = from_implicants_to_sdnf_string(sdnf_implicants);
    string current_sknf = from_implicants_to_sknf_string(sknf_implicants);
    vector<int> exception_sdnf = result_exeption(table_and_one_cross_implicants_sdnf.first, table_and_one_cross_implicants_sdnf.second);
    vector<int> exception_sknf = result_exeption(table_and_one_cross_implicants_sknf.first, table_and_one_cross_implicants_sknf.second);
    exceptioned_implicants(sdnf_implicants, exception_sdnf);
    exceptioned_implicants(sknf_implicants, exception_sknf);
    string minimized_sdnf = from_implicants_to_sdnf_string(sdnf_implicants);
    string minimized_sknf = from_implicants_to_sknf_string(sknf_implicants);
    pair<string, string> result(minimized_sdnf, minimized_sknf);
    return result;
}
pair<string, string> table_method(vector<vector<bool>>& sdnfprototype, vector<vector<bool>>& sknfprototype)
{
    vector<vector<map_square>> karnaugh_map = karnaugh_map_builder_sdnf(sdnfprototype, sknfprototype);
    vector<vector<pair<int, bool>>> sdnf_result = from_map_to_implicants(karnaugh_map, true);
    vector<vector<pair<int, bool>>> sknf_result = from_map_to_implicants(karnaugh_map, false);
    string minimized_sdnf = from_implicants_to_sdnf_string(sdnf_result);
    string minimized_sknf = from_implicants_to_sknf_string(sknf_result);
    pair<string, string> result_min = res_table_method(sdnfprototype, sknfprototype);
    return result_min;
}

bool Test1()
{
    vector<vector<bool>> sdnfprototype{ {0,0,1}, {1,1,1}, {1,0,1}, {1,0,0} }, sknfprotatype{ {0,0,0}, {0,1,1}, {0,1,0}, {1,1,0} };
    pair<string, string> current_result = calculate_method(sdnfprototype, sknfprotatype);
    pair<string, string> real_result;
    real_result.first = "(!b*c) +(a*c) +(a*!b) ";
    real_result.second = "(a+c) *(a+!b) *(!b+c) ";
    if (current_result.first == real_result.first && current_result.second == real_result.second) {
        cout << "Test1 correct!" << endl;
        return true;
    }
    else {
        cout << "Test1 incorrect!" << endl;
        return false;
    }
    return true;
}
bool Test2()
{
    vector<vector<bool>> sdnfprototype{ {0,0,1}, {1,1,1}, {1,0,1}, {1,0,0} }, sknfprotatype{ {0,0,0}, {0,1,1}, {0,1,0}, {1,1,0} };
    pair<string, string> current_result = calculate_table_method(sdnfprototype, sknfprotatype);
    pair<string, string> real_result;
    real_result.first = "(!b*c) +(a*c) +(a*!b) ";
    real_result.second = "(a+c) *(a+!b) *(!b+c) ";
    if (current_result.first == real_result.first && current_result.second == real_result.second) {
        cout << "Test2 correct!" << endl;
        return true;
    }
    else {
        cout << "Test2 incorrect!" << endl;
        return false;
    }
    return true;
}
bool Test3()
{
    vector<vector<bool>> sdnfprototype{ {0,0,1}, {1,1,1}, {1,0,1}, {1,0,0} }, sknfprotatype{ {0,0,0}, {0,1,1}, {0,1,0}, {1,1,0} };
    pair<string, string> current_result = table_method(sdnfprototype, sknfprotatype);
    pair<string, string> real_result;
    real_result.first = "(!b*c) +(a*c) +(a*!b) ";
    real_result.second = "(a+c) *(a+!b) *(!b+c) ";
    if (current_result.first == real_result.first && current_result.second == real_result.second) {
        cout << "Test3 correct!" << endl;
        return true;
    }
    else {
        cout << "Test3 incorrect!" << endl;
        return false;
    }
    return true;
}
bool Test4()
{
    vector<vector<bool>> sdnfprototype{ {0,0,1}, {1,0,0} }, sknfprotatype{ {0,0,0}, {0,1,1}, {0,1,0}, {1,1,0}, {1,1,1}, {1,0,1}, };
    pair<string, string> current_result = calculate_method(sdnfprototype, sknfprotatype);
    pair<string, string> real_result;
    real_result.first = "(!a*!b*c) +(a*!b*!c) ";
    real_result.second = "(a+c) *(!b+!c) *(!b+c) *(!a+!c) ";
    if (current_result.first == real_result.first && current_result.second == real_result.second) {
        cout << "Test4 correct!" << endl;
        return true;
    }
    else {
        cout << "Test4 incorrect!" << endl;
        return false;
    }
    return true;
}
bool Test5()
{
    vector<vector<bool>> sdnfprototype{ {0,0,1}, {1,0,0} }, sknfprotatype{ {0,0,0}, {0,1,1}, {0,1,0}, {1,1,0}, {1,1,1}, {1,0,1}, };
    pair<string, string> current_result = calculate_table_method(sdnfprototype, sknfprotatype);
    pair<string, string> real_result;
    real_result.first = "(!a*!b*c) +(a*!b*!c) ";
    real_result.second = "(a+c) *(!b+!c) *(!a+!b) *(!a+!c) ";
    if (current_result.first == real_result.first && current_result.second == real_result.second) {
        cout << "Test5 correct!" << endl;
        return true;
    }
    else {
        cout << "Test5 incorrect!" << endl;
        return false;
    }
    return true;
}
bool Test6()
{
    vector<vector<bool>> sdnfprototype{ {0,0,1}, {1,0,0} }, sknfprotatype{ {0,0,0}, {0,1,1}, {0,1,0}, {1,1,0}, {1,1,1}, {1,0,1}, };
    pair<string, string> current_result = table_method(sdnfprototype, sknfprotatype);
    pair<string, string> real_result;
    real_result.first = "(!a*!b*c) +(a*!b*!c) ";
    real_result.second = "(a+c) *(!b+!c) *(!a+!b) *(!a+!c) ";
    if (current_result.first == real_result.first && current_result.second == real_result.second) {
        cout << "Test6 correct!" << endl;
        return true;
    }
    else {
        cout << "Test6 incorrect!" << endl;
        return false;
    }
    return true;
}
bool Test7()
{
    string function = "!((!a+!b)*!(!a*!c))";
    pair< vector<vector<bool>>, vector<vector<bool >>> inputresult = transformator(function);
    pair<string, string> current_result = calculate_method(inputresult.first, inputresult.second);
    pair<string, string> real_result;
    real_result.first = "(!a*!c) +(b*!c) +(a*b) ";
    real_result.second = "(a+!c) *(!a+b) ";
    if (current_result.first == real_result.first && current_result.second == real_result.second) {
        cout << "Test7 correct!" << endl;
        return true;
    }
    else {
        cout << "Test7 incorrect!" << endl;
        return false;
    }
    return true;
}
bool Test8()
{
    string function = "!((!a+!b)*!(!a*!c))";
    pair< vector<vector<bool>>, vector<vector<bool >>> inputresult = transformator(function);
    pair<string, string> current_result = calculate_table_method(inputresult.first, inputresult.second);
    pair<string, string> real_result;
    real_result.first = "(!a*!c) +(a*b) ";
    real_result.second = "(a+!c) *(!a+b) ";
    if (current_result.first == real_result.first && current_result.second == real_result.second) {
        cout << "Test8 correct!" << endl;
        return true;
    }
    else {
        cout << "Test8 incorrect!" << endl;
        return false;
    }
    return true;
}
bool Test9()
{
    string function = "!((!a+!b)*!(!a*!c))";
    pair< vector<vector<bool>>, vector<vector<bool >>> inputresult = transformator(function);
    pair<string, string> current_result = table_method(inputresult.first, inputresult.second);
    pair<string, string> real_result;
    real_result.first = "(!a*!c) +(a*b) ";
    real_result.second = "(a+!c) *(!a+b) ";
    if (current_result.first == real_result.first && current_result.second == real_result.second) {
        cout << "Test9 correct!" << endl;
        return true;
    }
    else {
        cout << "Test9 incorrect!" << endl;
        return false;
    }
    return true;
}
bool Test10()
{
    string function = "!((!a+!b)*!(!a*c))";
    pair< vector<vector<bool>>, vector<vector<bool >>> inputresult = transformator(function);
    pair<string, string> current_result = calculate_method(inputresult.first, inputresult.second);
    pair<string, string> real_result;
    real_result.first = "(!a*c) +(a*b) ";
    real_result.second = "(a+c) *(b+c) *(!a+b) ";
    if (current_result.first == real_result.first && current_result.second == real_result.second) {
        cout << "Test10 correct!" << endl;
        return true;
    }
    else {
        cout << "Test10 incorrect!" << endl;
        return false;
    }
    return true;
}
bool Test11()
{
    string function = "!((!a+!b)*!(!a*c))";
    pair< vector<vector<bool>>, vector<vector<bool >>> inputresult = transformator(function);
    pair<string, string> current_result = calculate_table_method(inputresult.first, inputresult.second);
    pair<string, string> real_result;
    real_result.first = "(!a*c) +(a*b) ";
    real_result.second = "(a+c) *(!a+b) ";
    if (current_result.first == real_result.first && current_result.second == real_result.second) {
        cout << "Test11 correct!" << endl;
        return true;
    }
    else {
        cout << "Test11 incorrect!" << endl;
        return false;
    }
    return true;
}
bool Test12()
{
    string function = "!((!a+!b)*!(!a*c))";
    pair< vector<vector<bool>>, vector<vector<bool >>> inputresult = transformator(function);
    pair<string, string> current_result = table_method(inputresult.first, inputresult.second);
    pair<string, string> real_result;
    real_result.first = "(!a*c) +(a*b) ";
    real_result.second = "(a+c) *(!a+b) ";
    if (current_result.first == real_result.first && current_result.second == real_result.second) {
        cout << "Test12 correct!" << endl;
        return true;
    }
    else {
        cout << "Test12 incorrect!" << endl;
        return false;
    }
    return true;
}
void tests()
{
    int correct_counter = 0;
    correct_counter += Test1();
    correct_counter += Test2();
    correct_counter += Test3();
    correct_counter += Test4();
    correct_counter += Test5();
    correct_counter += Test6();
    correct_counter += Test7();
    correct_counter += Test8();
    correct_counter += Test9();
    correct_counter += Test10();
    correct_counter += Test11();
    correct_counter += Test12();
    if (correct_counter == 12) cout << "All tests passed correctly!" << endl;
}
void our_own_input()
{
    cout << "Choose the way you want function to be entered : 1)Index form :: 2)Numeral form :: 3)Your own input ";
    int choice_for_input;
    string index, numeral, own_function;
    pair< vector<vector<bool>>, vector<vector<bool >>> inputresult;
    pair<vector<int>, vector<int>> output_numeral;
    pair<string, string> output;
    cin >> choice_for_input;
    switch (choice_for_input)
    {
    case 1: cout << "Enter index : ";
        cin >> index;
        if (!checker_for_index(index)) {
            cout << "Enter something possible to work with!";
            return;
        }
        inputresult = index_to_skdnf(index);
        break;
    case 2: cout << "Enter sdnf in numeral form : ";
        cin.ignore();
        getline(cin, numeral);
        if (!checker_for_numeral(numeral)) {
            cout << "Enter something possible to work with!";
            return;
        }
        output_numeral = from_string_to_numeral(numeral);
        inputresult = numeral_to_skdnf(output_numeral.first, output_numeral.second);
        break;
    case 3: cout << "Enter your own function : ";
        cin.ignore();
        getline(cin, own_function);
        if (!checker_for_own_input(own_function)) {
            cout << "Enter something possible to work with!" << endl;
            return;
        }
        inputresult = transformator(own_function);
        break;
    default: cout << "Enter something possible to work with!" << endl;
        return;
        break;
    }
    int choice_for_method;
    cout << "Choose method of minimization : 1)calculation :: 2)calculation_table :: 3)table " << endl;
    cin >> choice_for_method;
    switch (choice_for_method)
    {
    case 1:
        sdnfprint(inputresult.first);
        sknfprint(inputresult.second);
        output = calculate_method(inputresult.first, inputresult.second);
        break;
    case 2:
        sdnfprint(inputresult.first);
        sknfprint(inputresult.second);
        output = calculate_table_method(inputresult.first, inputresult.second);
        break;
    case 3:
        sdnfprint(inputresult.first);
        sknfprint(inputresult.second);
        output = table_method(inputresult.first, inputresult.second);
        break;
    default: cout << "Enter something possible to work with!" << endl;
        return;
        break;
    }
    cout << "Minimized sdnf form : " << output.first << endl;
    cout << "Minimized sknf form : " << output.second << endl;
}
 
int main()
{
    int choice;
    cout << "1) Tests :: 2) Own input : ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        tests();
        break;
    case 2:
        our_own_input();
        break;
    default: cout << "Enter something possible to work with!" << endl;
        break;
    }
    system("pause");
    return 0;
}
