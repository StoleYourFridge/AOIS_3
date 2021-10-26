#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>

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
void our_own_input()
{
    cout << "Choose the way you want function to be entered : 1)Index form :: 2)Numeral form :: 3)Your own input ";
    int choise;
    string index, numeral, own_input;
    pair< vector<vector<bool>>, vector<vector<bool >>> inputresult;
    pair<vector<int>, vector<int>> output_numeral;
    cin >> choise;
    switch (choise)
    {
    case 1: cout << "Enter index : ";
        cin >> index;
        if (!checker_for_index(index)) {
            cout << "Enter something possible to work with!";
            return;
        }
        inputresult = index_to_skdnf(index);
        sdnfprint(inputresult.first);
        sknfprint(inputresult.second);
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
        sdnfprint(inputresult.first);
        sknfprint(inputresult.second);
        break;
    case 3: cout << "Enter your own function : ";
        cin.ignore();
        getline(cin, own_input);
        if (!checker_for_own_input(own_input)) {
            cout << "Enter something possible to work with!" << endl;
            return;
        }
        inputresult = transformator(own_input);
        sdnfprint(inputresult.first);
        sknfprint(inputresult.second);
        break;
    default: cout << "Enter something possible to work with!" << endl;
        break;
    }
}

bool checker_for_coincidence(vector<bool>& term_one, vector<bool>& term_two)
{
    int counter_of_coincidence = 0;
    if (term_one[0] == term_two[0]) counter_of_coincidence++;
    if (term_one[1] == term_two[1]) counter_of_coincidence++;
    if (term_one[2] == term_two[2]) counter_of_coincidence++;
    if (counter_of_coincidence == 2) return true;
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

int main()
{
    vector<vector<bool>> sdnfprototype{ {0,1,0}, {1,0,1}, {1,1,0}, {1,1,1} };
    vector<vector<pair<int, bool>>> implicants = gluing(sdnfprototype);
    for (int i = 0; i < implicants.size(); i++)
    {
        cout << "(";
        for (int j = 0; j < implicants[i].size(); j++)
        {
            //cout << implicants[i][j].second << " <- " << implicants[i][j].first << " , ";
            if (implicants[i][j].first == 0) {
                if (implicants[i][j].second) cout << "!a";
                else cout << "a";
            }
            else if (implicants[i][j].first == 1) {
                if (implicants[i][j].second) cout << "!b";
                else cout << "b";
            }
            else if (implicants[i][j].first == 2) {
                if (implicants[i][j].second) cout << "!c";
                else cout << "c";
            }
            if (j != implicants[i].size() - 1) cout << ",";
        }
        cout << ") ";
    }
    cout << endl << endl;
    calculate_method_from_skdnf(implicants, false);
    for (int i = 0; i < implicants.size(); i++)
    {
        cout << "(";
        for (int j = 0; j < implicants[i].size(); j++)
        {   
            if (implicants[i][j].first == 0) {
                if (implicants[i][j].second) cout << "!a";
                else cout << "a";
            }
            else if (implicants[i][j].first == 1) {
                if (implicants[i][j].second) cout << "!b";
                else cout << "b";
            }
            else if (implicants[i][j].first == 2) {
                if (implicants[i][j].second) cout << "!c";
                else cout << "c";
            }
            if (j != implicants[i].size() - 1) cout << ",";
        }
        cout << ") ";
    }
    /*for (int i = 0; i < term.size(); i++)
    {
        for (int j = 0; j < term[i].size(); j++)
        {
            cout << term[i][j].second << ",";
        }
        cout << endl << endl;
    }*/
    //our_own_input();
    return 0;
}