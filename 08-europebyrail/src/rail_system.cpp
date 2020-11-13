#pragma warning (disable:4786)
#pragma warning (disable:4503)

#include "rail_system.h"
#include <iostream>
#include <fstream>
#include <string>
#include "city.h"
#include <climits>
// TODO: Implement all methods
void RailSystem::load_services(const std::string &filename)
{
    // loading outgoing_services map and city map.
    std::string streamLine;
    std::ifstream in(filename);
    if(in.is_open())
    {
        while(getline(in, streamLine))
        {
            std::vector<std::string> vec; // need to store each word in a line
            std::string str = "";
            for (int i = 0; i < streamLine.length(); ++i)
            {
                // store line in a vector
                char cur = streamLine[i];
                if(cur != ' ' && cur != '\r')
                    str += cur;
                else
                {
                    vec.push_back(str);
                    str = "";
                }
            }
            std::map<std::string, std::list<Service*>>::iterator it = outgoing_services.find(vec[0]);
            City* city = new City(vec[0]); // this is used for cities map
            cities.insert(std::pair<std::string, City*>(vec[0],city));
            if(it != outgoing_services.end())
            {
                // if we don't have current city in our map, we create it and store an edge.
                // Otherwise we just store another edge for a city.
                std::list<Service*>* servList = &it->second;
                Service* service = new Service(vec[1], stoi(vec[2]), stoi(vec[3]));
                servList->push_back(service);
            } else
            {
                Service* service = new Service(vec[1], stoi(vec[2]), stoi(vec[3]));
                std::list<Service*> list;
                list.push_back(service);
                outgoing_services.insert(std::pair<std::string, std::list<Service*>>(vec[0], list));
            }
        }
    } else
        throw std::logic_error("Incorrect file input");
    in.close();
}

void RailSystem::reset()
{
    // resetting info of each city
    std::map<std::string, City*>::iterator it = cities.begin();
    while(it != cities.end())
    {
        City* city = it->second;
        city->total_distance = 0;
        city->total_fee = 0;
        city->visited = false;
        city->from_city="";
        it++;
    }
}

std::vector<std::string> RailSystem::recover_route(const std::string &city)
{
    // recovering route, going from the last city. Each city has an information of the city we came from.
    std::vector<std::string> path; // need to store cities
    City* last = cities.find(city)->second;
    if(last->from_city == "")
        // in case we haven't reach the city
        return std::vector<std::string>();
    while(last->from_city != "")
    {
        // storing city names in vector
        path.push_back(last->name);
        last = cities.find(last->from_city)->second;
    }
    path.push_back(last->name);
    std::vector<std::string> reverse_path; // need this vector to reverse the previous one
    for (int i = path.size() - 1; i >= 0; --i)
    {
        // reverse path vector
        reverse_path.push_back(path[i]);
    }
    return reverse_path;
}

std::pair<int, int> RailSystem::calc_route(std::string from, std::string to)
{
    reset();
    //checking if cities are "valid"
    if(cities.find(from) == cities.end())
        throw std::invalid_argument("Invalid city");
    if(cities.find(to) == cities.end())
        throw std::invalid_argument("Invalid city");
    std::list<Service*> services; // edges of our graph. Used to represent edges of city.
    City* curCity = cities.find(from)->second; // current city which we are iterating through
    while(true)
    {
        // Dijkstra algorithm, pretending total_fee as a weight of an edge
        services = outgoing_services.find(curCity->name)->second; // roads to other cities
        std::list<Service*>::iterator it = services.begin();
        for (int i = 0; i < services.size(); ++i)
        {
            // here we are going through not visited cities and writing down fee, distance and the city we came from
            Service* edge = *std::next(it,i);
            City* city = cities.find(edge->destination)->second;
            if(city->visited)
                continue;
            if(city->total_fee == 0 || city->total_fee > curCity->total_fee + edge->fee)
            {
                city->total_fee = curCity->total_fee + edge->fee;
                city->total_distance = curCity->total_distance + edge->distance;
                city->from_city = curCity->name;
            }
        }
        curCity->visited = true; // we visited this city, so we make visited field as true
        City* min = getCheapestCity(from); // The city currently having minimal total_fee
        if(min == curCity)
            break;
        curCity = min;
    }
    City* toCity = cities.find(to)->second; // this city we need to return.
    City* fromCity = cities.find(from)->second; // need to make total_fee as 0.
    fromCity->total_fee = 0; // make 0 again, because we changed it earlier
    if(toCity->total_fee != 0)
        return std::pair<int,int>(toCity->total_fee, toCity->total_distance);
    else
        return  std::pair<int,int>(INT_MAX, INT_MAX);
}

RailSystem::RailSystem(const std::string &filename)
{
    load_services(filename);
}

RailSystem::~RailSystem()
{
    for (auto it = outgoing_services.begin(); it != outgoing_services.end(); it++ )
        for (int i = 0; i < it->second.size(); ++i)
            it->second.pop_back();

    for (auto it = cities.begin(); it != cities.end(); it++)
        delete(it->second);

    outgoing_services.clear();
    cities.clear();
}

void RailSystem::output_cheapest_route(const std::string &from, const std::string &to)
{
    calc_route(from, to);
    std::vector<std::string> path = recover_route(to);
    if(path.size() == 0)
    {
        std::cout << "There is no route from " << from << " to " << to;
        return;
    }
    for (int i = 0; i < path.size() - 1; ++i)
    {
        std::cout << path[i] << " to ";
    }
    std::cout << path[path.size()-1];
}

bool RailSystem::is_valid_city(const std::string &name)
{
    return cities.find(name) != cities.end();
}

Route RailSystem::getCheapestRoute(const std::string &from, const std::string &to)
{
    std::pair<int,int> pair = calc_route(from, to);
    return Route(from, to, pair.first, pair.second, recover_route(to));
}

City* RailSystem::getCheapestCity(const std::string &from)
{
    City* min = cities.find(from)->second; // The city currently having minimal total_fee
    auto iter = cities.begin();
    min->total_fee = INT_MAX;
    while(iter!=cities.end())
    {
        if(iter->second->total_fee != 0 && !iter->second->visited && iter->second->total_fee < min->total_fee)
            min = iter->second;
        iter++;
    }
    return min;
}
