#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>

using std::cout, std::endl, std::string;

double computeMean(const std::vector<double> &data) {
	double data_sum = 0.0;
	for (const auto &x : data)
		data_sum += x;
	
	return data_sum / data.size();
}

double computeMedian(const std::vector<double> &data) {
	std::vector<double> copied_data = data;
	std::sort(copied_data.begin(), copied_data.end());

	if (data.size() % 2 == 0) {  
		return ( ((copied_data.size() / 2) + ((copied_data.size() + 1) / 2) / 2 ));
	} else {
		return ((copied_data.size() + 1) / 2);
	}
}

double find_min_value(const std::vector<double> &data) {
	double min = data.at(0);

	for (const auto &x : data) {
		if (x < min)
			min = x;	
	}

	return min;	
}

double find_max_value(const std::vector<double> &data) {
	double max = data.at(0);

	for (const auto &x : data) {
		if (x > max)
			max = x;
	}

	return max;
}

std::pair<double, double> computeMinMax(const std::vector<double> &data) {
	double data_min = find_min_value(data);
    double data_max = find_max_value(data);

	std::pair<double, double> min_max_pair(data_min, data_max);

	return min_max_pair;	
}

int main() {
	std::vector<double> my_vec{ 1.2, 4.2, 6.1, 9.2, 2.9, 7.3 };
	cout << "my_vec:" << endl;
	for (const auto &x : my_vec)
		cout << "[" << x << "]\t";
   cout << endl;
	
   cout << "compute mean: " << computeMean(my_vec) << endl;
   cout << "compute median: " << computeMedian(my_vec) << endl;

	std::pair<double, double> MinMax = computeMinMax(my_vec);

	cout << "minmax first /second: " << MinMax.first << ", " << MinMax.second << endl;	

	return 0;
}
