//DCPE/FT/2A/24
//Topic 1 - Storage Rack Management System
//Stanley Lin Sheng Yang (P2120795) and Chia Weng Chin (P2120836)

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using std::cout;



/*--------------below is STANLEY LIN SHENG YANG's contribution--------------------------*/

//input from txt file, using passing by reference
void fileIO(int& number_of_racks, double package_weight_amount_rack_limit_cost[][2]) {
	
	ifstream textfile("Input.txt");

	while (!textfile.eof()) {
		textfile >> number_of_racks;
		
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 2; j++)
				textfile >> package_weight_amount_rack_limit_cost[i][j];
	}
	textfile.close();
}

/*--------------above is STANLEY LIN SHENG YANG's contribution--------------------------*/



/*--------------below is CHIA WENG CHIN's contribution--------------------------*/

//global variable min_cost to compare with every other possible cost_amount;LLONG_MAX
double min_cost = LLONG_MAX;
int total_weight_of_racks = LLONG_MAX;
//global variable min_cost_rack_combination to display to the vector of vector of the lowest cost combination
vector<vector<int>> min_cost_rack_combination{ { },{ },{ },{ } };

//permutations functions that has parameters that take in a vector of input, a vector of vector which will represent the present state of the rack arrangement, and the index variable representing which input variable is actually being placed in right now
void permutations(vector<int>& elements, vector<vector<int>>& current, int index, int number_of_racks, vector<double> vec_for_weight_of_individual_rack, vector<double> vec_for_cost_of_individual_rack) {
	if (index == elements.size()) {
		// if we have processed all input elements
		double total_current_cost = 0;
		//we need to set a variable as current cost for everytime we add an item
		for (int rack_number = 0; rack_number < number_of_racks; rack_number++) {
			//for every rack, if there is more than 1 item
			if (current[rack_number].size() > 0) {
				//we will add the cost of that rack to the total current cost
				total_current_cost += vec_for_cost_of_individual_rack[rack_number];
			}
		}
		// if the total current cost more than the more than the current min_cost(global variable) 
		if (total_current_cost < min_cost) {
			//replace the global min_cost variable with the current cost
			min_cost = min(total_current_cost, min_cost);
			// replace the global variable min_cost_rack_combination with the current rack combination
			min_cost_rack_combination = current;
		}
		return;
	}
	//start of permutation, loop through the racks
	for (int rack_number = 0; rack_number < number_of_racks; rack_number++) {
		//create a variable to enter the current weight of the rack
		int current_weight = 0;
		//loop thru the packages inside each rack
		for (int current_package_no = 0; current_package_no < current[rack_number].size(); current_package_no++) {
			//add up all the package weight that is inside each rack
			current_weight += current[rack_number][current_package_no];
		}
		//if the current weight + next input elements is <= to the weight of the rack
		if (current_weight + elements[index] <= vec_for_weight_of_individual_rack[rack_number]) {
			//push in the next input element into the CURRENT vector of vector
			current[rack_number].push_back(elements[index]);
			//recursively use the next input element to carry out the next permutation
			permutations(elements, current, index + 1, number_of_racks, vec_for_weight_of_individual_rack, vec_for_cost_of_individual_rack);
			// remove the current element from the current permutation
			current[rack_number].pop_back();
		}
	}
}

/*--------------above is CHIA WENG CHIN's contribution--------------------------*/



/*--------------below is CHIA WENG CHIN's contribution--------------------------*/

void compute_racks(int total_weight_of_all_racks, int total_weight_of_input, int number_of_racks, vector<int> concatenated_elements, vector<vector<int>>&racks_vec, vector<double>&vec_for_weight_of_individual_rack, vector<double>&vec_for_cost_of_individual_rack) {

/*--------------above is CHIA WENG CHIN's contribution--------------------------*/



/*--------------below is STANLEY LIN SHENG YANG's contribution--------------------------*/

		//Lets say the total_weight_of_all_racks is 32 and total_weight_of_input is 50, we would not allow the user to display and prompt with a user frendly error.
		if (total_weight_of_all_racks < total_weight_of_input) {
			cout << "Sorry, the total weight of all packs exceed total weight of all racks. Please enter again, thank you.";
			cout << endl;

/*--------------above is STANLEY LIN SHENG YANG's contribution--------------------------*/



/*--------------below is CHIA WENG CHIN'S contribution--------------------------*/

			//permutations_overflow(concatenated_elements, racks_vec, 0, number_of_racks, vec_for_weight_of_individual_rack, vec_for_cost_of_individual_rack);
		}
		else {
			// send into the permutation function the input elememts vector, a empty racks_vec that represent current vector, starting index for input element, 
			//number of racks, vector of all the rack weights, vector of all the rack cost.
			permutations(concatenated_elements, racks_vec, 0, number_of_racks, vec_for_weight_of_individual_rack, vec_for_cost_of_individual_rack);
			cout << "Number of Racks: " << number_of_racks;
			cout << endl << endl;

			int wastage_total = 0;
			int Sum = 0;
			int number_of_racks_used = 0;
			//loop thru the number of roles for my vector
			for (int i = 0; i < min_cost_rack_combination.size(); i++) {
				cout << "Rack" << i + 1;
				cout << endl;

				for (int j = 0; j < min_cost_rack_combination[i].size(); j++) {
					cout << min_cost_rack_combination[i][j] << " ";
					Sum += min_cost_rack_combination[i][j];

				}

				//When there is a wastage on any particular rack, we would store that ammount into variable wastage.
				//For example at rack 1, weight limit is 5. But there is only one 4kg pack on it, we will store 1kg into wastage.
				if (Sum < vec_for_weight_of_individual_rack[i] && Sum > 0) {
					int wastage = vec_for_weight_of_individual_rack[i] - Sum;

					//wastage_total stores the total ammount of wastage from all racks
					wastage_total += wastage;
					cout << "\t Wastage: " << wastage << "kg";
				}
				if (Sum > 0) {
					number_of_racks_used++;
				}

/*--------------above is CHIA WENG CHIN'S contribution--------------------------*/



/*--------------below is STANLEY LIN SHENG YANG's contribution--------------------------*/

					cout << endl;
				cout << "============================================================";
				cout << endl;
			}
			cout << "Minimum Total cost: $ " << min_cost;
			cout << endl;
			cout << "Total number of racks used: " << number_of_racks_used << endl;
			cout << "Total Wastage Storage: " << wastage_total << "kg";
			cout << endl;
		}
}

/*--------------above is STANLEY LIN SHENG YANG's contribution--------------------------*/



/*--------------below is STANLEY LIN SHENG YANG's contribution--------------------------*/

int main()
{
	//int heavier_pack_amount = 0, lighter_pack_amount = 0;
	//int heavier_pack_weight = 0, lighter_pack_weight = 0;

	int number_of_racks = 0;

	//This array variable stores the array index of package weight ammount. The individual weight limit of racks and the cost of that specific rack
	double package_weight_amount_rack_limit_cost[6][2];

	//input from txt file, using passing by reference
	fileIO(number_of_racks, package_weight_amount_rack_limit_cost);

	//package_weight_amount_rack_limit_cost[0][0] stores the value of one of the package weight.
	//package_weight_amount_rack_limit_cost[0][1] stores the ammount of packages with the weight of package_weight_amount_rack_limit_cost[0][0]
	cout << "Amount of " << package_weight_amount_rack_limit_cost[0][0] << " KG packs is " << package_weight_amount_rack_limit_cost[0][1] << endl;

	//similarily for this, package_weight_amount_rack_limit_cost[1][0] stores the value of another package weight.
	//package_weight_amount_rack_limit_cost[1][1] stores the ammount of packages with the weight of package_weight_amount_rack_limit_cost[1][0]
	cout << "Amount of " << package_weight_amount_rack_limit_cost[1][0] << " KG packs is " << package_weight_amount_rack_limit_cost[1][1] << endl;

	//this vector<int> stores both weighted packs (eg. 2 and 3) with their amount of it (eg. 3 and 4) together, for example 2 2 2 3 3 3 3.
	vector<int> concatenated_elements;

	//with the above example package_weight_amount_rack_limit_cost[0][1] will be 4 
	for (int i = 0; i < package_weight_amount_rack_limit_cost[0][1]; ++i) {
		//this will push in 2 each time it loops here.
		concatenated_elements.push_back(package_weight_amount_rack_limit_cost[0][0]);
	}

	for (int i = 0; i < package_weight_amount_rack_limit_cost[1][1]; ++i) {
		concatenated_elements.push_back(package_weight_amount_rack_limit_cost[1][0]);
	}
	/*vector<int> ::iterator it;
	for (it = concatenated_elements.begin(); it != concatenated_elements.end(); it++) {
		cout << *it << " ";
	}*/

	//this vector<double> stores the cost of individual rack starting from lightest rack with least cost, for example 5.6 6.9 9.9 11.5
	vector<double> vec_for_cost_of_individual_rack;
	for (int i = 2; i < 6; i++) {
		vec_for_cost_of_individual_rack.push_back(package_weight_amount_rack_limit_cost[i][1]);
	}

	//this vector<double> stores the weight limit of individual rack starting from lightest rack with least limit, for example 5 7 9 11
	vector<double> vec_for_weight_of_individual_rack;
	for (int i = 2; i < 6; i++) {
		vec_for_weight_of_individual_rack.push_back(package_weight_amount_rack_limit_cost[i][0]);
	}

	vector<vector<int> > racks_vec{ { },{ },{ },{ } };

	//This for loop helps to sum the total weight of all packs, with the earlier example 2 2 2 3 3 3 3. Total_weight_of_input will store 18
	int total_weight_of_input = 0;
	for (int no_of_input_element = 0; no_of_input_element < concatenated_elements.size(); no_of_input_element++) {
		total_weight_of_input += concatenated_elements[no_of_input_element];
	}

	//This for loop helps to sum the limit of all racks, with the earlier example 5 7 9 11. total_weight_of_all_racks will be 32
	double total_weight_of_all_racks = 0;
	for (int i = 0; i < vec_for_weight_of_individual_rack.size(); i++) {
		total_weight_of_all_racks += vec_for_weight_of_individual_rack[i];
	}

	//instant enter racks if total weight of packs less than total limit of all racks
	for (int i = 0; i < number_of_racks; i++) {
		if (total_weight_of_input <= vec_for_weight_of_individual_rack[i]) {
			min_cost_rack_combination[i] = concatenated_elements;
		}
	}

	//this will call compute_racks() function
	compute_racks(total_weight_of_all_racks, total_weight_of_input, number_of_racks, concatenated_elements, racks_vec, vec_for_weight_of_individual_rack, vec_for_cost_of_individual_rack);

	return 0;
}

/* --------------above is STANLEY LIN SHENG YANG's contribution--------------------------*/