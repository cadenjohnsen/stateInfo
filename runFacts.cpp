/*******************
 * Program: run_facts.cpp
 * Author: Caden Johnsen
 * Date: 4/16/17
 * Description: Program to take in state and county information and sort it
 * Input: stateFacts.cpp, stateFacts.h, "statesInfo.txt"(form of text file)
 * Output: List of information based on input given
 ******************/
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include "stateFacts.h"

using namespace std;

int main(int argc, char *argv[]) {
	/*******************
	 * Function: main
	 * Description: Calls functions and initializes variables
	 * Pre-Conditions: argc, argv
	 * Post-Conditions: None
	 * Return: 0
	 *******************/
	int state_num = 0;
	int income_line = 0;
	char *str;
	int pop_state[50];
	int pop_county[50];
	int total_counties = 0;
	int temp = 0;
	int text = 0;
	string temp_string;
	char file_name[20];
	ifstream input;
	ofstream output;

	if(is_valid_dimensions(argv, argc) == false) {
		return 0;
	}
	if(!strcmp(argv[1], "-s")) {
		state_num = atoi(argv[2]);
		input.open(argv[4]);
	}
	else if(!strcmp(argv[3], "-s")) {
		state_num = atoi(argv[4]);
		input.open(argv[2]);
	}
	while(input.fail()) {
		if(!strcmp(argv[1], "-s")) {
			cout << "Enter in a new file name." << endl;
			cin >> argv[2];
			input.open(argv[2]);
		}
		else if(!strcmp(argv[3], "-s")) {
			cout << "Enter in a new file name." << endl;
			cin >> argv[4];
			input.open(argv[4]);
		}
	}
	cout << "Test for counties with income levels over: $";
	cin >> income_line;
	struct state* s = create_state(state_num);
	get_state_data(s, state_num, input);
	cout << "Do you want to print to console(1) or output to file(2)?" << endl;
	cin >> text;

	if(text == 1) {
		bubble_sort(s, state_num, income_line);
		for(int i = 0; i < state_num; i++) {
			total_counties = s[i].counties + total_counties;
		}
		for(int i = 0; i < state_num; i++) {
			pop_state[i] = s[i].population;
		}
		temp = 0;
		for(int i = 0; i < state_num; i++) {
			for(int j = 0; j < s[i].counties; j++) {
				pop_county[temp] = s[i].c[j].population;
				temp++;
			}
		}

		cout << "States sorted by population:" << endl;
		for(int i = 0; i < state_num; i++) {
			for(int j = 0; j < state_num - 1; j++) {
				if(pop_state[j+1] > pop_state[j]) {
					temp = pop_state[j];
					pop_state[j] = pop_state[j+1];
					pop_state[j+1] = temp;
				}
			}
		}
		for(int i = 0; i < state_num; i++) {
			for(int j = 0; j < state_num; j++) {
				if(s[j].population == pop_state[i]) {
					cout << s[j].name << endl;
				}
			}
		}

		cout << "Counties sorted by population:" << endl;
		for(int i = 0; i < total_counties; i++) {
			for(int j = 0; j < total_counties - 1; j++) {
				if(pop_county[j+1] > pop_county[j]) {
					temp = pop_county[j];
					pop_county[j] = pop_county[j+1];
					pop_county[j+1] = temp;
				}
			}
		}
		for(int i = 0; i < total_counties; i++) {
			for(int j = 0; j < state_num; j++) {
				for(int k = 0; k < total_counties; k++) {
					if(s[j].c[k].population == pop_county[i]) {
						cout << s[j].c[k].name << endl;
					}
				}
			}
		}

		string state_name_sort[state_num];
		string county_name_sort[total_counties];

		cout << "States sorted by name:" << endl;
		for(int i = 0; i < state_num; i++) {
			state_name_sort[i] = s[i].name;
		}
		for(int i = 0; i < state_num; i++) {
			for(int j = 0; j < state_num - 1; j++) {
				if(state_name_sort[j+1] < state_name_sort[j]) {
					temp_string = state_name_sort[j];
					state_name_sort[j] = state_name_sort[j+1];
					state_name_sort[j+1] = temp_string;
				}
			}
		}
		for(int i = 0; i < state_num; i++) {
			for(int j = 0; j < state_num; j++) {
				if(s[j].name == state_name_sort[i]) {
					cout << s[j].name << endl;
				}
			}
		}

		cout << "Counties sorted by name:" << endl;
		temp = 0;
		for(int i = 0; i < state_num; i++) {
			for(int j = 0; j < s[i].counties; j++) {
				county_name_sort[temp] = s[i].c[j].name;
				temp++;
			}
		}
		for(int i = 0; i < total_counties; i++) {
			for(int j = 0; j < total_counties - 1; j++) {
				if(county_name_sort[j+1] < county_name_sort[j]) {
					temp_string = county_name_sort[j];
					county_name_sort[j] = county_name_sort[j+1];
					county_name_sort[j+1] = temp_string;
				}
			}
		}
		for(int i = 0; i < total_counties; i++) {
			cout << county_name_sort[i] << endl;
		}

	}
	if(text == 2) {
		cout << "File name?" << endl;
		cin >> file_name;
		output.open(file_name);
		bubble_sort2(s, state_num, income_line, output);
		for(int i = 0; i < state_num; i++) {
			total_counties = s[i].counties + total_counties;
		}

		for(int i = 0; i < state_num; i++) {
			pop_state[i] = s[i].population;
		}

		temp = 0;
		for(int i = 0; i < state_num; i++) {
			for(int j = 0; j < s[i].counties; j++) {
				pop_county[temp] = s[i].c[j].population;
				temp++;
			}
		}

		output << "States sorted by population:" << endl;
		for(int i = 0; i < state_num; i++) {
			for(int j = 0; j < state_num - 1; j++) {
				if(pop_state[j+1] > pop_state[j]) {
					temp = pop_state[j];
					pop_state[j] = pop_state[j+1];
					pop_state[j+1] = temp;
				}
			}
		}
		for(int i = 0; i < state_num; i++) {
			for(int j = 0; j < state_num; j++) {
				if(s[j].population == pop_state[i]) {
					output << s[j].name << endl;
				}
			}
		}

		output << "Counties sorted by population:" << endl;
		for(int i = 0; i < total_counties; i++) {
			for(int j = 0; j < total_counties - 1; j++) {
				if(pop_county[j+1] > pop_county[j]) {
					temp = pop_county[j];
					pop_county[j] = pop_county[j+1];
					pop_county[j+1] = temp;
				}
			}
		}
		for(int i = 0; i < total_counties; i++) {
			for(int j = 0; j < state_num; j++) {
				for(int k = 0; k < total_counties; k++) {
					if(s[j].c[k].population == pop_county[i]) {
						output << s[j].c[k].name << endl;
					}
				}
			}
		}
		string state_name_sort[state_num];
		string county_name_sort[total_counties];

		output << "States sorted by name:" << endl;
		for(int i = 0; i < state_num; i++) {
			state_name_sort[i] = s[i].name;
		}
		for(int i = 0; i < state_num; i++) {
			for(int j = 0; j < state_num - 1; j++) {
				if(state_name_sort[j+1] < state_name_sort[j]) {
					temp_string = state_name_sort[j];
					state_name_sort[j] = state_name_sort[j+1];
					state_name_sort[j+1] = temp_string;
				}
			}
		}
		for(int i = 0; i < state_num; i++) {
			for(int j = 0; j < state_num; j++) {
				if(s[j].name == state_name_sort[i]) {
					output << s[j].name << endl;
				}
			}
		}

		output << "Counties sorted by name:" << endl;
		temp = 0;
		for(int i = 0; i < state_num; i++) {
			for(int j = 0; j < s[i].counties; j++) {
				county_name_sort[temp] = s[i].c[j].name;
				temp++;
			}
		}
		for(int i = 0; i < total_counties; i++) {
			for(int j = 0; j < total_counties - 1; j++) {
				if(county_name_sort[j+1] < county_name_sort[j]) {
					temp_string = county_name_sort[j];
					county_name_sort[j] = county_name_sort[j+1];
					county_name_sort[j+1] = temp_string;
				}
			}
		}
		for(int i = 0; i < total_counties; i++) {
			output << county_name_sort[i] << endl;
		}
	}
	delete_info(s, state_num);
	input.close();
	return 0; //this is the end
}
