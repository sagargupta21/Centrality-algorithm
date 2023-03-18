#include <iostream>
#include <dirent.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <regex>

using namespace std;

bool sortcol(const vector<string>&v1,const vector<string>&v2){
    return v1[1]<v2[1];
}

bool longtitude(string k){
    if(stof(k)>=115 && stof(k)<=117)
        return true;
    else return false;
}

bool latitude(string k){
    if(stof(k)>=38 && stof(k)<=40)
        return true;
    else return false;
}

bool isTimestampFormat(std::string timestamp) {
    // Define regular expression to match timestamp format
    std::regex timestampRegex("^\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}$");
    
    // Test whether timestamp matches regular expression
    return std::regex_match(timestamp, timestampRegex);
}

bool check(string t){
    try{
        float f=stof(t);
    }
    catch(invalid_argument&){
        return false;
    }
    return true;
}

bool checkno(string t){
    try{
        int n=stoi(t);
    }
    catch(invalid_argument&){
        return false;
    }
    return true;
}



int main() {
    string path = "C:/Users/Sagar/Documents/release/taxi_log_2008_by_id"; 
    string output_folder = "C:/Users/Sagar/Documents/release/cleaned";
    DIR *dir = opendir(path.c_str());

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr){
        string filename = entry->d_name;
        string filepath = path + "/" + filename;
        string output_file = output_folder + "/" + filename;
        vector<vector<string>>z;

        ifstream infile(filepath);
        string line;
        while (getline(infile, line)) {
            istringstream iss(line);  // Create a stringstream from the input line
            string field;  // String to hold each field in the line
            
            vector<string>data;
            // Parse the line by splitting it into fields using commas as delimiters
            while (getline(iss, field, ',')) {
                data.push_back(field);  // Add the field to the data vector
            }
            z.push_back(data);
            data.clear();
        }
        infile.close();

        //counting the frequency of taxi id
        map<int,int>count;
        for(int i=0;i<z.size();i++){
            int b=stoi(z[i][0]);
            count[b]++;
        }
        int max_count=0,value;
        for(auto i:count){
            if(i.second>max_count){
                max_count=i.second;
                value=i.first;
            }
        }
        count.clear();

        //deleting duplicate data
        sort(z.begin(),z.end(),sortcol);
        for(int i=1;i<z.size();i++){
            if(z[i][1]==z[i-1][1]){
                z.erase(z.begin()+i);
                i--;
            }
        }

        //removing other taxi id of less frquency
        for(int i=0;i<z.size();i++){
            if(stoi(z[i][0])!=value){
                z.erase(z.begin()+i);
                i--;
            }            
        }   

        //deleting coordinates whose value does not fit according to bejing city corrdinates
        for(int i=0;i<z.size();i++){
            if(!longtitude(z[i][2]) || !latitude(z[i][3])){
                z.erase(z.begin()+i);
                i--;
            }
        }

        //remove other data other than the time 
        for(int i=0;i<z.size();i++){
            if(!isTimestampFormat(z[i][1])){
                z.erase(z.begin()+i);
                i--;
            }
        }

        //removing every values which are not integer value or float value
        for(int i=0;i<z.size();i++){
            if(!check(z[i][2])){
                if(!checkno(z[i][3])){
                    z.erase(z.begin()+i);
                    i--;
                }
            }
        }

        ofstream outfile(output_file);
        for (int i = 0; i < z.size(); i++) {
            for (int j = 0; j < z[i].size(); j++) {
                outfile << z[i][j];
                if (j < z[i].size() - 1) {
                    outfile << ",";
                }
            }
            outfile << endl;
        }
        outfile.close();  
        z.clear();    
    }
    closedir(dir);
    return 0;
}



