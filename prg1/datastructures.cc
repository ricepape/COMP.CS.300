// Datastructures.cc
//
// Student name:
// Student email:
// Student number:

#include "datastructures.hh"

#include <random>

#include <cmath>

using namespace std;

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{}

Datastructures::~Datastructures()
{
    // Write any cleanup you need here
}

unsigned int Datastructures::get_affiliation_count()
{
    return static_cast<int>(affiliation_data.size());
}

void Datastructures::clear_all()
{
    affiliation_data.clear();
    publications_data.clear();
}

std::vector<AffiliationID> Datastructures::get_all_affiliations()
{
    std::vector<AffiliationID> all_affiliations;
    for (const auto& pair : affiliation_data)
    {
        all_affiliations.push_back(pair.first);
    }
    return all_affiliations;
}

bool Datastructures::add_affiliation(AffiliationID id, const Name &name, Coord xy)
{
    auto findit = affiliation_data.find(id);
    if (findit == affiliation_data.end()) {
        AffiliationData new_aff;
        new_aff.name = name;  
        new_aff.coordinates = xy;
        affiliation_data[id] = new_aff; 
        return true;
    }
    return false;
}

Name Datastructures::get_affiliation_name(AffiliationID id)
{
    return affiliation_data[id].name;
}

Coord Datastructures::get_affiliation_coord(AffiliationID id)
{

    return affiliation_data[id].coordinates;
}

std::vector<AffiliationID> Datastructures::get_affiliations_alphabetically()
{
    std::vector<AffiliationID> all_affiliations;
    data = affiliation_data(data.begin(), data.end(), compareName);

    for (const auto& pair : data)
    {
        all_affiliations.push_back(pair.first);
    }
    return all_affiliations;

}

std::vector<AffiliationID> Datastructures::get_affiliations_distance_increasing()
{
    // Create a vector to store affiliations and their distances
    std::vector<std::pair<AffiliationID, double>> affiliations_with_distances;

    // Calculate distances for each affiliation and store in the vector
    for (const auto& pair : affiliation_data)
    {
        double distance = std::sqrt(
            std::pow(pair.second.coordinates.first, 2) +
            std::pow(pair.second.coordinates.second, 2)
        );
        affiliations_with_distances.push_back({pair.first, distance});
    }

    // Sort the vector based on distances in increasing order
    std::sort(
        affiliations_with_distances.begin(),
        affiliations_with_distances.end(),
        [](const auto& a, const auto& b) {
            return a.second < b.second;
        }
    );

    // Extract and return the sorted AffiliationIDs
    std::vector<AffiliationID> sorted_affiliations;
    for (const auto& pair : affiliations_with_distances)
    {
        sorted_affiliations.push_back(pair.first);
    }

    return sorted_affiliations;
}

AffiliationID Datastructures::find_affiliation_with_coord(Coord xy)
{
    for (const auto& pair : affiliation_data)
    {
        if (pair.second.coordinates == xy){
            return pair.first;
    }
    }
}

bool Datastructures::change_affiliation_coord(AffiliationID id, Coord newcoord)
{
     if (affiliation_data.find(id) != affiliation_data.end()) {
        affiliation_data[id].coordinates = newcoord;
        return true;
    } else {
        return false;
    }
}

bool Datastructures::add_publication(PublicationID id, const Name &name, Year year, const std::vector<AffiliationID> &affiliations)
{
    auto findit = publications_data.find(id);
    if (findit == publications_data.end()) {
        PublicationData new_pub;
        new_pub.name = name;  
        new_pub.publication_year = year; 
        new_pub.affiliations = affiliations;
        publications_data[id] = new_pub; 
        return true;
    }
    return false;
}

std::vector<PublicationID> Datastructures::all_publications()
{
    std::vector<PublicationID> all_publications;
    for (const auto& pair : publications_data)
    {
        publications_data.push_back(pair.first);
    }
    return all_publications;
}

Name Datastructures::get_publication_name(PublicationID id)
{
    return publications_data[id].name;
}

Year Datastructures::get_publication_year(PublicationID id)
{
    return publications_data[id].publication_year;
}

std::vector<AffiliationID> Datastructures::get_affiliations(PublicationID id)
{
    return publications_data[id].affiliations;
}

bool Datastructures::add_reference(PublicationID id, PublicationID parentid)
{
    if ((publications_data.find(id) != publications_data.end()) && 
    (publications_data.find(parentid) != publications_data.end())) {
        publications_data[id].affiliations.push_back(parentid);
        return true;    
    } else {
        return false;
    }
}

std::vector<PublicationID> Datastructures::get_direct_references(PublicationID id)
{
    std::vector<PublicationID> references;
    for for (const PublicationID &number : data){
        cout << number;
    }
}

bool Datastructures::add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid)
{
    if ((affiliation_data.find(affiliationid) != affiliation_data.end()) && 
    (publications_data.find(publicationid) != publications_data.end())) {
        publications_data[publicationid].affiliations.push_back(affiliationid);
        return true;    
    } else {
        return false;
    }
}

std::vector<PublicationID> Datastructures::get_publications(AffiliationID id)
{
    std::vector<PublicationID> publications;
    for (const auto& pair : publications_data)
    {
        if (pair.second.affiliations.find(id) != affiliation_data.end()){
            publications.push_back(pair.first);
    }
    return publications;
    }
}

PublicationID Datastructures::get_parent(PublicationID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_parent()");
}

std::vector<std::pair<Year, PublicationID> > Datastructures::get_publications_after(AffiliationID /*affiliationid*/, Year /*year*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_publications_after()");
}

std::vector<PublicationID> Datastructures::get_referenced_by_chain(PublicationID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_referenced_by_chain()");
}

std::vector<PublicationID> Datastructures::get_all_references(PublicationID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_all_references()");
}

std::vector<AffiliationID> Datastructures::get_affiliations_closest_to(Coord /*xy*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_affiliations_closest_to()");
}

bool Datastructures::remove_affiliation(AffiliationID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("remove_affiliation()");
}

PublicationID Datastructures::get_closest_common_parent(PublicationID /*id1*/, PublicationID /*id2*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_closest_common_parent()");
}

bool Datastructures::remove_publication(PublicationID /*publicationid*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("remove_publication()");
}


