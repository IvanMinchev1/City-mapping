#include <iostream>
#include <filesystem>
#include <fstream>
#include <memory>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cctype>


namespace ivan
{
namespace ivanSTL
{
class City_builder
{
public:
    City_builder(const std::string& name) : name(name) {}

    std::string getValue() const 
    {
        return name;
    }

private:
    std::string name;
};

class Distance_maker 
{
public:
    Distance_maker(std::shared_ptr<City_builder> start, std::shared_ptr<City_builder> end, int _KM = 1)
        : start(start), end(end), KM(_KM) {}

    std::shared_ptr<City_builder> getStart() const 
    {
        return start;
    }

    std::shared_ptr<City_builder> getEnd() const
    {
        return end;
    }

    int getWeight() const 
    {
        return KM;
    }

private:
    std::shared_ptr<City_builder> start;
    std::shared_ptr<City_builder> end;
    int KM;
};

class Map 
{
public:
    void addCity(const std::string& name) 
    {
        auto city = std::make_shared<City_builder>(name);
        Cities[name] = city;
        Cities_adjacencyList[city] = std::vector<std::shared_ptr<Distance_maker>>();
    }

    void addDistance(const std::string& startValue, const std::string& endValue, int KM = 1) 
    {
        auto startVertex = Cities[startValue];
        auto endVertex = Cities[endValue];

        auto distance = std::make_shared<Distance_maker>(startVertex, endVertex, KM);
        Cities_adjacencyList[startVertex].push_back(distance);
    }

    void printMap() const 
    {
        for (const auto& entry : Cities_adjacencyList) {
            auto city = entry.first;
            std::cout << "City: " << city->getValue() << " is connected to: ";

            for (const auto& discanse : entry.second) {
                std::cout << discanse->getEnd()->getValue() << "(" << discanse->getWeight() << ") ";
            }
            std::cout << std::endl;
        }
    }

private:
    std::unordered_map<std::string, std::shared_ptr<City_builder>> Cities;
    std::unordered_map<std::shared_ptr<City_builder>, std::vector<std::shared_ptr<Distance_maker>>> Cities_adjacencyList;
};
}
std::vector<std::string> extractWords(const std::string& input) 
{
    std::vector<std::string> words{};
    auto isWhitespace = [](char c) { return std::isspace(static_cast<unsigned char>(c)); };
    auto start = std::find_if_not(input.begin(), input.end(), isWhitespace);

    while (start != input.end()) 
    {
        auto end = std::find_if(start, input.end(), isWhitespace);
        words.emplace_back(start, end);
        start = std::find_if_not(end, input.end(), isWhitespace);
    }
    return words;
}
std::vector<int> stringTOvector(const std::string& input)
{
    std::vector<int> result{};

    auto isWhitespace = [](char c) { return std::isspace(static_cast<unsigned char>(c)); };
    auto start = std::find_if_not(input.begin(), input.end(), isWhitespace);

    while (start != input.end()) 
    {
        auto end = std::find_if(start, input.end(), isWhitespace);
        result.push_back(std::stoi(std::string(start, end)));
        start = std::find_if_not(end, input.end(), isWhitespace);
    }
    return result;
}

void fillCities(ivanSTL::Map& Map, const std::vector<std::string>& CitiesName)
{
    for(const auto& word : CitiesName)
    {
        Map.addCity(word);
    }
}

void fillDistance(ivanSTL::Map& Map, const std::vector<std::string>& CitiesName, const std::vector<int>& distance)
{
    std::vector<std::string>::const_iterator itr = CitiesName.begin();
    std::vector<int>::const_iterator itrr = distance.begin();
    while(itr != CitiesName.end() - 1)
    {
        Map.addDistance(*itr, *(itr + 1), *itrr);
        itr++;
        itrr++;
    }
}
}
int main()
{
    ivan::ivanSTL::Map map{};
   
    std::string names_of_cities{};
    std::string distance_between_cities{};
    
//    std::string names_of_cities = {"Sofia Plovdiv Burgas"};
//    std::string distance_between_cities= {"150 250"};
    std::string filename{};
    std::string fileDirectory{};
    std::cin>>filename;
    std::cin>>fileDirectory;
    
    
    std::filesystem::path dir {fileDirectory};
    if (std::filesystem::exists(dir) != 0)
    {
        if (std::filesystem::is_directory(dir))
        {
            for (const auto& iter : std::filesystem::directory_iterator(dir))
            {
                std::cout<<iter.path().filename().string();
                std::cout<<std::endl;
                if(iter.path().filename().string() ==  filename)
                {
                    std::fstream file(iter.path());
                    if(file.is_open())
                    {
                        std::getline(file, names_of_cities);
                        std::vector<std::string> words = ivan::extractWords(names_of_cities);
                        std::getline(file, distance_between_cities);
                        std::vector<int> distances = ivan::stringTOvector(distance_between_cities);
                        ivan::fillCities(map, words);
                        ivan::fillDistance(map, words, distances);
                    }
                    else
                    {
                        std::cerr<<"File can not be open!!!"<<std::endl;
                        std::exit(EXIT_FAILURE);
                    }
                    file.close();
                    break;
                }
            }
        }
    }
    else
    {
        std::cout << "path " << dir << " does not exist\n";
    }
    map.printMap();
    return 0;
}
