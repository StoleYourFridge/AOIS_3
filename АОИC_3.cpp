#include <iostream>
#include "../АОИС_2/АОИС_2.h"

using namespace std;

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
void vec_print(vector<bool>term)
{
    for (int i = 0; i < term.size(); i++)
    {
        cout << term[i];
    }
}

Result index_to_skdnf(int index)
{
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
    Result output(sdnfprototype, sknfprototype);
    return output;
}
Result numeral_to_skdnf(vector<int>numeralsdnf, vector<int>numeralsknf)
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
    Result output(sdnfprototype, sknfprototype);
    return output;
}




int main()
{
    return 0;
}