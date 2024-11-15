#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>
#include <cctype>

bool in_set(const std::set<std::string> &set, const std::string &key) {
    return set.find(key) != set.end();
}

int in_map(const std::map<std::string, std::map<std::string, int>> &map, const std::string &country, const std::string &state = "") {
    auto country_it = map.find(country);
    if (country_it != map.end()) {
        if (state.empty()) {
            int total_confirmed = 0;
            for (const auto &state_entry : country_it->second) {
                total_confirmed += state_entry.second;
            }
            return total_confirmed;
        } else {
            auto state_it = country_it->second.find(state);
            if (state_it != country_it->second.end()) {
                return state_it->second;
            }
        }
    }
    return -1;
}

std::string read_field(std::istream &input) {
    std::string result;
    if (input.peek() == '"') {
        input.get();
        std::getline(input, result, '"');
        input.get();
    } else {
        std::getline(input, result, ',');
    }

    result.erase(result.begin(), std::find_if(result.begin(), result.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    result.erase(std::find_if(result.rbegin(), result.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), result.end());

    return result;
}

int main(int argc, char *argv[]) {
    std::string inputFile = argv[1];
    std::string commandFile = argv[2];

    std::set<std::string> countrySet;
    std::map<std::string, std::map<std::string, int>> countryStateMap;

    std::ifstream input(inputFile);
    std::ifstream command(commandFile);

    std::string line;
    std::getline(input, line);
    while (std::getline(input, line)) {
        std::stringstream ss(line);
        std::string fips = read_field(ss);
        std::string admin2 = read_field(ss);
        std::string province_state = read_field(ss);
        std::string country_region = read_field(ss);
        std::string last_update = read_field(ss);
        std::string lat = read_field(ss);
        std::string long_ = read_field(ss);
        std::string confirmed = read_field(ss);
        std::string deaths = read_field(ss);
        std::string recovered = read_field(ss);
        std::string active = read_field(ss);
        std::string combined_key = read_field(ss);
        std::string incidence_rate = read_field(ss);
        std::string case_fatality_ratio = read_field(ss);

        if (!country_region.empty()) {
            countrySet.insert(country_region);
            int confirmed_cases = confirmed.empty() ? 0 : std::stoi(confirmed);
            if (province_state.empty()) {
                countryStateMap[country_region][country_region] += confirmed_cases;
            } else {
                countryStateMap[country_region][province_state] += confirmed_cases;
            }
        }
    }

    std::string most_confirmed_country;
    int most_confirmed_cases = 0;
    for (const auto &country_entry : countryStateMap) {
        int total_confirmed = 0;
        for (const auto &state_entry : country_entry.second) {
            total_confirmed += state_entry.second;
        }
        if (total_confirmed > most_confirmed_cases) {
            most_confirmed_cases = total_confirmed;
            most_confirmed_country = country_entry.first;
        }
    }
    std::cout << most_confirmed_country << std::endl;

    while (std::getline(command, line)) {
        std::stringstream ss(line);
        std::string cmd, key;
        ss >> cmd;
        std::getline(ss, key);
        key = key.substr(1); 
        if (cmd == "set") {
            std::cout << in_set(countrySet, key) << std::endl;
        } else if (cmd == "map") {
            std::string country, state;
            size_t pos = key.find(';');
            if (pos != std::string::npos) {
                country = key.substr(0, pos);
                state = key.substr(pos + 1);
            } else {
                country = key;
            }
            std::cout << in_map(countryStateMap, country, state) << std::endl;
        }
    }

    return 0;
}