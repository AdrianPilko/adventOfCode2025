#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

typedef struct s_data
{
    char lr;
    int num;
} t_data;

bool readFile(string filename, vector<t_data> & data)
{

    ifstream fs(filename);

    if (fs.is_open() != true)
    {
        return false;
    }

    t_data temp;

    while (fs >> temp.lr >> temp.num)
    {
        data.push_back(temp);
    }
#ifdef DEBUG
    cout << "read in:" << endl;
    for (auto& elem : data)
    {
        cout << elem.lr << " " << elem.num << endl;
    }
#endif    
    return true;
}


int main(int argc, char *argv[])
{
    const int start = 50;
    const int max = 100;
    int current = start;
    int zeros = 0;

    const int numberIterTodo = 20000;
    int iterDone = 0;

    if (argc != 2)
    {
        cerr << "Error must have data filename" << endl;
        return EXIT_FAILURE;
    }

    vector<t_data> data;
    string filename = argv[1];
        
    if (readFile(filename, data))
    {
        cout << " current= " << current << " zeros=" << zeros << endl;
        for (auto& d : data)
        {
            iterDone++;
            if (iterDone > numberIterTodo) break;

            cout << d.lr << " " << d.num << " ";           

            int completeRot = d.num / 100;
            int leftOverRot = d.num % 100;


            if (d.lr == 'L')            
            {               
                //if (current - d.num < 0)
                if (current - leftOverRot < 0) // this means it's gone past zero
                {                             
                    // we already counted the zero in last iteration  
                    if (current!= 0) zeros++; 
                    current = (current - leftOverRot) + max;                     
                    cout << "L wrap zero " << leftOverRot;                    
                }
                else if (current - leftOverRot == 0)
                {
                    zeros++;
                    current = 0;
                    cout << "L count zero";
                }
                else
                {
                    current = (current - leftOverRot); 
                    cout << "L normal";
                }                
                zeros += completeRot;
                if (completeRot != 0) cout << " added an extra " << completeRot << " zeros now=" <<zeros << endl;
            }
            else if (d.lr == 'R')
            {
                //if (current + d.num >= max)
                if (current + leftOverRot >= max)                
                {
                    if (current != 0) zeros++;
                    current = (current + leftOverRot) - max;                                
                    cout << "R wrap max";
                }
                else if (current + leftOverRot == 0)
                {
                    zeros++;
                    current = 0;
                    cout << "R count zero";
                }
                else
                {
                    current = (current + leftOverRot); 
                    cout << "R normal";
                }                
                zeros += completeRot;
                if (completeRot != 0) cout << " added an extra " << completeRot << " zeros now=" <<zeros << endl;
            }
            else
            {
                cerr << "unrecognised code" << endl;
            }
            cout << " current= " << current << " zeros=" << zeros << endl;
            
            if (current < 0)
            {
                cerr << "some kind of erorr has happend now current < 0" << endl;
                exit(EXIT_FAILURE);
            }
        }

        cout << "Answer is " << zeros << endl;
    }
    else
    {
        cerr << "error reading file " << filename << endl;
    }
}