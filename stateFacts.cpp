#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include "stateFacts.h"

using namespace std;

bool is_valid_dimensions(char *argv[],int argc) {
        /*******************
         * Function: is_valid_dimensions
         * Description: Error checks the user input
         * Pre-Conditions: None
         * Post-Conditions: None
         * Return: true or false
         *******************/
        if(argc != 5 || !strcmp(argv[1], argv[3]) || ((strcmp(argv[1], "-s") && strcmp(argv[3], "-f")) && (strcmp(argv[1], "-f") && strcmp(argv[3], "-s")))) {
                cout << "Invalid argument." << endl;
                return false;
        }
        else {
                if(!strcmp(argv[1], "-s")) {
                        for(int i = 0; i < strlen(argv[2]); i++) {
                                while(atoi(argv[2]) > 9 || atoi(argv[2]) < 1) {
                                        cout << "Number of states: ";
                                        cin >> argv[2];
                                }
                        }
                }
                if(!strcmp(argv[3], "-s")) {
                        for(int i = 0; i < strlen(argv[4]); i++) {
                                while(atoi(argv[4]) > 9 || atoi(argv[4]) < 1) {
                                        cout << "Number of states: ";
                                        cin >> argv[4];
                                }
                        }
                }
                return true;
        }
}

void bubble_sort2(state* s, int state_num, int income_line, ofstream &output) {
        /*******************
         * Function: bubble_sort
         * Description: Sorts the data required
         * Pre-Conditions: None
         * Post-Conditions: None
         * Return: None
         *******************/
        int high_state_pop = 0;
        int high_county_pop = 0;
        float state_avg_house = 0.0;
        string county_income;
        string state_name;
        string county_name;

        for (int i = 0; i < state_num; i++) {
                int county_house = 0;
                if(s[i].population > high_state_pop) {
                        high_state_pop = s[i].population;
                        state_name = s[i].name;
                        for(int j = 0; j < s[i].counties; j++) {
                                county_house = county_house + s[i].c[j].avg_house;
                                if(s[i].c[j].population > high_county_pop) {
                                        high_county_pop = s[i].c[j].population;
                                        county_name = s[i].c[j].name;
                                }
                                if(s[i].c[j].avg_income > income_line) {
                                        county_income = s[i].c[j].name;
                                        output << "County with income above $"
                                                << income_line << ": " << county_income << endl;
                                }
                        }
                }
                state_avg_house = county_house / s[i].counties;
                output << "The average household cost in " << state_name
                        << " is " << state_avg_house << "." << endl;
        }
        output << "The state with the highest population is "
                << state_name << "." << endl;
        output << "The county with the highest population is "
                << county_name << "." << endl;
}

void bubble_sort(state* s, int state_num, int income_line) {
        /*******************
         * Function: bubble_sort
         * Description: Sorts the data required
         * Pre-Conditions: None
         * Post-Conditions: None
         * Return: None
         *******************/
        int high_state_pop = 0;
        int high_county_pop = 0;
        float state_avg_house = 0.0;
        string county_income;
        string state_name;
        string county_name;

        for (int i = 0; i < state_num; i++) {
                int county_house = 0;
                if(s[i].population > high_state_pop) {
                        high_state_pop = s[i].population;
                        state_name = s[i].name;
                        for(int j = 0; j < s[i].counties; j++) {
                                county_house = county_house + s[i].c[j].avg_house;
                                if(s[i].c[j].population > high_county_pop) {
                                        high_county_pop = s[i].c[j].population;
                                        county_name = s[i].c[j].name;
                                }
                                if(s[i].c[j].avg_income > income_line) {
                                        county_income = s[i].c[j].name;
                                        cout << "County with income above $"
                                                << income_line << ": " << county_income << endl;
                                }
                        }
                }
                state_avg_house = county_house / s[i].counties;
                cout << "The average household cost in " << state_name
                        << " is " << state_avg_house << "." << endl;
        }
        cout << "The state with the highest population is "
                << state_name << "." << endl;
        cout << "The county with the highest population is "
                << county_name << "." << endl;
}

county* create_county(int county_num) {
        /*******************
         * Function: create_county
         * Description: Dynamically creates the county array
         * Pre-Conditions: None
         * Post-Conditions: None
         * Return: county_array
         *******************/
        struct county* county_array = new struct county[county_num];
        return county_array;
}

void get_county_data(county* c, int county_num, ifstream &file) {
        /*******************
         * Function:get_county_data
         * Description: Gets the information from the file for the county
         * Pre-Conditions: None
         * Post-Conditions: None
         * Return: None
         *******************/
        string in;
        for(int i = 0; i < county_num; i++) {
                file >> c[i].name;
                file >> c[i].population;
                file >> c[i].avg_income;
                file >> c[i].avg_house;
                file >> c[i].cities;
                c[i].city = new string[c[i].cities];
                for(int j = 0; j < c[i].cities; j++) {
                        file >> c[i].city[j];
                }
        }
}

state* create_state(int state_num) {
        /*******************
         * Function: create_state
         * Description: Dynamically creates the state array
         * Pre-Conditions: None
         * Post-Conditions: None
         * Return: state_array
         *******************/
        struct state* state_array = new struct state[state_num];
        return state_array;
}

void get_state_data(state* s, int state_num, ifstream &file) {
        /*******************
         * Function: get_state_data
         * Description: Gets the information from the file for the state
         * Pre-Conditions: None
         * Post-Conditions: None
         * Return: None
         *******************/string in;
        int county_num = 0;
        for(int i = 0; i < state_num; i++) {
                file >> s[i].name;
                file >> s[i].population;
                file >> s[i].counties;
                county_num = s[i].counties;
                s[i].c = create_county(county_num);
                get_county_data(s[i].c, county_num, file);
        }
}

void delete_info(state* &s, int state_num) {
        /*******************
         * Function: delete_info
         * Description: Deletes the dynamic arrays to avoid memory leaks
         * Pre-Conditions: None
         * Post-Conditions: None
         * Return: None
         *******************/
        for(int i = 0; i < state_num; i++) {
                for(int j = 0; j < s[i].counties; j++) {
                        delete [] s[i].c[j].city;
                        s[i].c[j].city = NULL;
                }
                delete [] s[i].c;
                s[i].c = NULL;
        }
        delete [] s;
        s = NULL;
}
