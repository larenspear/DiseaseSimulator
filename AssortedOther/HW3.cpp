#include <vector>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

float random_vector(int length){}
float sort_it(float x){}


int main()
{
 int length = 10;
 vector<float> values = random_vector(length);
 sort_it(values);
 display_vector(values);
}

float random_vector(int length)
{
    vector<float> x(length);
    for (int i = 0; i <= length; i++){
        x.push_back(srand (time(NULL)))
    return x
}

float sort_it(x){
    vector<float> sorted;
    int largest_element;
    for(int i; i < x.size();i++){
    for(int i; i < x.size();i++){
        if(i > largest_element){
            largest_element = i
        }
    sorted.push_back(largest_element);
    }
    }
    return sorted;
}

float display_vector(x){
    cout << x << endl;
}


