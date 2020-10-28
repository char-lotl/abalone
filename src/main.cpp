#include <fstream>
#include <array>
#include <string>

enum abalone_sex {
	MALE = 0,
	FEMALE = 1,
	INFANT = 2
};

int const NUM_ABALONE_FEATURES = 8;
// one class, one categorical feature, seven numerical features;

struct abalone {
	abalone_sex ab_sex;
	std::array<std::string,NUM_ABALONE_FEATURES - 1> abalone_feature_strings;
	int ab_rings;
};

std::string fetch_line(std::ifstream& infile);
std::string correct_format(abalone& a);
abalone extract_features(std::string dat);

std::string const DELIM = ",";

int main() {
	
	std::ifstream infile;
	std::ofstream outfile_training;
	std::ofstream outfile_testing;
	std::string data_in;
	abalone data_a;
	std::string data_out;
	
	infile.open("abalone.data");
	
	int const NUM_TRAINING_LINES = 3133;
	int const NUM_TESTING_LINES = 1044;
	
	outfile_training.open("abalone_training");
	
	for (int i = 0; i < NUM_TRAINING_LINES; i++) {
		data_in = fetch_line(infile);
		data_a = extract_features(data_in);
		data_out = correct_format(data_a);
		outfile_training << data_out;
	}
	
	outfile_training.close();
	outfile_testing.open("abalone_testing");
	
	for (int i = 0; i < NUM_TESTING_LINES; i++) {
		data_in = fetch_line(infile);
		data_a = extract_features(data_in);
		data_out = correct_format(data_a);
		outfile_testing << data_out;
	}
	
	outfile_testing.close();
	
	infile.close();
	
	return 0;
	
}

std::string fetch_line(std::ifstream& infile) {
	std::string data_in;
	getline(infile, data_in);
	return data_in;
}

abalone extract_features(std::string dat) {
	abalone a;
	for (int i = 0; i < NUM_ABALONE_FEATURES; i++) {
		std::size_t delim_index = dat.find(DELIM);
		std::string fs = dat.substr(0, delim_index);
		dat.erase(0, delim_index + 1);
		if (i == 0) {
			abalone_sex as;
			switch (fs[0]) {
				case 'M':
					as = MALE; break;
				case 'F':
					as = FEMALE; break;
				case 'I':
				default:
					as = INFANT; break;
					break;
			}
			a.ab_sex = as;
		} else {
			a.abalone_feature_strings[i-1] = fs;
		}
	}
	
	a.ab_rings = dat.length();
	
	return a;
}

std::string correct_format(abalone& a) {
	std::string formatted_output;
	
	formatted_output += std::to_string(a.ab_rings) + " ";
	
	for (int i = 0; i < NUM_ABALONE_FEATURES - 1; i++) {
		formatted_output += std::to_string(i + 1) + ":";
		formatted_output += a.abalone_feature_strings[i] + " ";
	}
	
	switch (a.ab_sex) {
		case MALE:
			formatted_output += "8:1 9:0 10:0\n";
			break;
		case FEMALE:
			formatted_output += "8:0 9:1 10:0\n";
			break;
		case INFANT:
			formatted_output += "8:0 9:0 10:1\n";
			break;
		default:
			break;
	}
	
	return formatted_output;
}
