#ifndef STATE_FACTS_H
#define STATE_FACTS_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>

using namespace std;

struct county {
        /*******************
         * Function: county
         * Description: Struct used to store values for the county stats
         * Pre-Conditions: None
         * Post-Conditions: None
         * Return: None
         *******************/
        string name;
        string *city;
        int cities;
        int population;
        float avg_income;
        float avg_house;
};

struct state {
        /*******************
         * Function: state
         * Description: Struct used to store values for the state stats
         * Pre-Conditions: None
         * Post-Conditions: None
         * Return: None
         *******************/
        string name;
        struct county *c;
        int counties;
        int population;
};
bool is_valid_dimensions(char *argv[],int argc);
void bubble_sort2(state* s, int state_num, int income_line, ofstream &output);
void bubble_sort(state* s, int state_num, int income_line);
county* create_county(int county_num);
void get_county_data(county* c, int county_num, ifstream &file);
state* create_state(int state_num);
void get_state_data(state* s, int state_num, ifstream &file);
void delete_info(state* &s, int state_num);

#endif
