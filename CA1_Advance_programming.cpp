#include <vector>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
// define contact 
struct contact {
    string name;
    string phonenumber;
    string email;
    bool exist;
};
int size_vector(vector<contact>& arr){
    int cnt = 0;
    for(auto& item : arr){
        if(item.exist == true){
            cnt++;
        }
    }
    return cnt;
}
void print_vector_struct(vector<contact>& list){
    int size = list.size();
    int itr = 0;
    for(auto& item : list){
        if(itr < size)
            cout<<itr<<" "<<item.name<<" "<<item.phonenumber<<" "<<item.email<<endl;
        else
            break;
        itr++;
    }

}
bool find_in_list(vector<contact>& list,string item){ // if find_in_list() == false , must add item to list
    for(auto& elmnt : list){//elmnt : element
        if(elmnt.email == item || elmnt.name == item || elmnt.phonenumber == item)
            return true;
        else
            return false;
    }
}
int find_index_vector(vector<string>& arr,string item){
    for(int i = 0;i < (int)arr.size();i++){
        if(arr[i] == item)
            return i;
    }
    return -1;
}
string filter_and_add(vector<string>& arr, string params){
    int index = find_index_vector(arr, params);
    if(index != -1)
        return arr[index + 1];
}
int find_index_of_char(string sentence, char item){ // it return first char that it's similar with item and return first Occure.
    for(int i = 0;i < sentence.length();i++){
        if(sentence[i] == item){
            return i;
        }
    }
    return 0; // couldn't find the item in sentence
}
int find_index(vector<string>& arr, string thing){ // find index of string thing in vector
    for(int index = 0;index < (int)arr.size();index++){
        if(thing == arr[index])
            return index;
    }
    return 0; // couldn't find thing in array
}

bool inclusive_str(string base, string query){ // Is query included in base?
    int index = find_index_of_char(base, query[0]);
    //cout<<" ** index  :"<<index<<endl; // test and debugging code+
    int cnt = 0; // counter for checking be linked q[i]s
    for(int i = index;i < (index + query.length());i++){
        if(base[i] == query[i - index]){
            cnt++;
            //cout<<i<<" "<<base[i]<<" --> "<<cnt<<endl; // test and debugging code 
        }
    }
    if(cnt == query.length())
        return true;
    else
        return false;
}
vector<contact> match(vector<contact>& list, string query){
    vector<contact> match_list;
    for(auto& item : list){
        if(inclusive_str(item.email, query)){
            match_list.push_back(item);
        }
        else if(inclusive_str(item.name, query)){
            match_list.push_back(item);
        }
        else if(inclusive_str(item.phonenumber, query)){
            match_list.push_back(item);
        }
    }
    return match_list;
}
void print_vector(vector<string>& arr){
    int cnt = 0;
    for(auto& item : arr){
        cout<<"arr["<<cnt<<"]  --->"<<item<<endl;
        cnt++;
    }
    cout<<endl;
}
vector<string> split(string input){
    stringstream ss_split(input);
    string s;
    vector<string> a;
    while(ss_split >> s){
        a.push_back(s);
    }
    return a;
}
// validation of email and phone-number
bool valid_phone_number(string phone_number){
    int cnt = 0; // simple counter as we get phonenumber as string we should check all item of it is number like '0','9'
    // for this we use ascii
    for(int i = 0;i < phone_number.length();i++){
        if((int)phone_number[i] >= 48 && (int)phone_number[i] <= 57){
            cnt++;
            //cout<<phone_number[i]<<"   "<<cnt<<endl;     // test query for this function
        }
    }
    if(phone_number[0] == '0' && phone_number[1] == '9' && phone_number.length() == 11 && cnt == 11)
        return true;
    else
        return false;
    //cout<<"\n\n";
}
bool valid_email(string email){
    int index;int len = email.length();
    index = find_index_of_char(email, '@');
    int dot = find_index_of_char(email , '.');
    char Unappropriate_chars[] = {
	' ', '!', '"', '#', '$', '%', '&', '(', ')', '*', '+', ',',
    '-', '.', '/', ':', ';', '<', '=', '>', '?', '@', '[', '\\',
    ']', '^', '_', '`', '{', '|', '}', '~' ,'\''
    };
    //cout<<"index of @ :  "<<index<<"  length of email :  "<<len<<endl;   // test query for function
    if(index == 0)
        return false;
    else{
        for(int i = 0;i < index;i++){
            for(int j = 0;j < sizeof(Unappropriate_chars);j++){
                if(Unappropriate_chars[j] == email[i])
                    return false;
            }
        }
        for (int i = index + 1; i < email.length(); i++)
        {
            for(int j = 0;j < sizeof(Unappropriate_chars);j++){
                if(Unappropriate_chars[j] == email[i] && Unappropriate_chars[j] != '.')
                    return false;
            }
        }
    }
    if(email[index + 1] == '.' || email[len - 1] == '.')
        return false;
    if(dot == 0)
        return false;
    return true;
}
// end of validations
// operation's function

int main()
{
    vector<contact> contact_list;
    contact sample;
    vector<string> used_vector; // used duiring code running
    string input;
    string name = "";string phone_number;string email;
    vector<contact> match_list;
    int id;
    bool res = true;
    
    while(getline(cin, input)){
        //cout<<contact_list.size()<<endl; // test and debugging codes
        used_vector = split(input);
        //print_vector(used_vector);
        if(used_vector[0] == "add"){
            if(find_index_vector(used_vector,"-f") != -1 && find_index_vector(used_vector,"-l") != -1 && find_index_vector(used_vector,"-p") != -1 && find_index_vector(used_vector,"-e") != -1){
                name += (filter_and_add(used_vector, "-f") +" "+ filter_and_add(used_vector, "-l"));
                phone_number = filter_and_add(used_vector, "-p");
                email = filter_and_add(used_vector, "-e");
                if(find_in_list(contact_list , name) == false)
                    sample.name = name;
                else{
                    res = false;
                    name ="";
                }
                if(find_in_list(contact_list, phone_number) == false && valid_phone_number(phone_number))
                    sample.phonenumber = phone_number;
                else
                    res = false;
                if(find_in_list(contact_list, email) == false && valid_email(email))
                    sample.email = email;
                else    
                    res = false;
                if(res == true){
                    sample.exist = true;
                    contact_list.push_back(sample);
                    cout<<"Command OK"<<endl;
                    cout<<"Contact list :"<<endl;
                    print_vector_struct(contact_list);  // test and debugging codes
                    cout<<"**len of list  :"<<size_vector(contact_list)<<endl;
                    name = "";
                }
                else{
                    cout<<"Command Failed"<<endl;
                    cout<<"Contact list :"<<endl;
                    print_vector_struct(contact_list); // test and debugging codes
                    name = "";
                    res = true;
                }
            }
            else{
                cout<<"Command Failed"<<endl;
                name = "";
                res = true;
            }
        }
        else if(used_vector[0] == "search"){
            //cout<<"search query : "<<used_vector[1]<<endl; // test and debugging codes
            match_list = match(contact_list, used_vector[1]);
            print_vector_struct(match_list);
        }else if(used_vector[0] == "delete"){
            id = stoi(used_vector[1]); // function for converting string to int
            if(id <= size_vector(contact_list)){
                if(contact_list[id].exist == true){
                    contact_list[id].exist =false;
                    cout<<"Command OK"<<endl;
                    print_vector_struct(contact_list);
                    cout<<size_vector(contact_list)<<endl;
                }
                else{
                    cout<<"Command Failed"<<endl;
                }
            }
            else{
                cout<<"Command Failed"<<endl;
            }
        }
    }
}
