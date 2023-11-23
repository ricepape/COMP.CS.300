// Datastructures.cc
//
// Student name: Vu Dinh Thi
// Student email: thi.vu@tuni.fi
// Student number: 151394898

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
    auto findit = affiliation_data.find(id);
    if (findit == affiliation_data.end()) {
        return NO_NAME;
    }
    return affiliation_data[id].name;
}

Coord Datastructures::get_affiliation_coord(AffiliationID id)
{
    auto findit = affiliation_data.find(id);
    if (findit == affiliation_data.end()) {
        return NO_COORD;
    }
    return affiliation_data[id].coordinates;
}

std::vector<AffiliationID> Datastructures::get_affiliations_alphabetically()
{

    auto compareName = [](const std::pair<AffiliationID, AffiliationData>& a, const std::pair<AffiliationID, AffiliationData>& b) {
        return a.second.name < b.second.name;
    };

    std::vector<std::pair<AffiliationID, AffiliationData>> data(affiliation_data.begin(), affiliation_data.end());

    std::sort(data.begin(), data.end(), compareName);

    std::vector<AffiliationID> all_affiliations;
    for (const auto& pair : data) {
        all_affiliations.push_back(pair.first);
    }

    return all_affiliations;
}


std::vector<AffiliationID> Datastructures::get_affiliations_distance_increasing()
{
    std::vector<std::pair<AffiliationID, double>> affiliations_with_distances;
    for (const auto& pair : affiliation_data)
    {
        double distance = std::sqrt(
            std::pow(pair.second.coordinates.x, 2) +
            std::pow(pair.second.coordinates.y, 2)
        );
        affiliations_with_distances.push_back({pair.first, distance});
    }
    std::sort(
        affiliations_with_distances.begin(),
        affiliations_with_distances.end(),
        [](const auto& a, const auto& b) {
            return a.second < b.second;
        }
    );

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
    return NO_AFFILIATION;
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
        all_publications.push_back(pair.first);
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
    auto iter_id = publications_data.find(id);
    auto iter_parentid = publications_data.find(parentid);

    if (iter_id == publications_data.end() || iter_parentid == publications_data.end()) {
        return false;
    }
    PublicationID* child = &id;
    publications_data[parentid].referencing.insert(child);
    PublicationID* parent = &parentid;
    publications_data[id].referenced_by = parent;
    return true;
    
}

std::vector<PublicationID> Datastructures::get_direct_references(PublicationID id)
{
    std::vector<PublicationID> references;
    auto iter_id = publications_data.find(id);

    if (iter_id != publications_data.end()) {
        for (const auto& ref : iter_id->second.referencing) {
            references.push_back(*ref);
        }
    }
    return references;
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
        if (std::find(pair.second.affiliations.begin(), pair.second.affiliations.end(), id) != pair.second.affiliations.end())
        {
            publications.push_back(pair.first);
        }
    }
    return publications;
}

PublicationID Datastructures::get_parent(PublicationID id)
{
    auto it = publications_data.find(id);
    if (it != publications_data.end()) {
        PublicationID* publication_ptr = it->second.referenced_by;
        return *publication_ptr;
    }
    return NO_PUBLICATION;
}

std::vector<std::pair<Year, PublicationID> > Datastructures::get_publications_after(AffiliationID affiliationid, Year year)
{
    std::vector<std::pair<Year, PublicationID>> publications;
    auto it = affiliation_data.find(affiliationid);
    if (it == affiliation_data.end()) {
        return publications;
    }
    for (const auto& pair : publications_data)
    {
        if (std::find(pair.second.affiliations.begin(), pair.second.affiliations.end(), affiliationid)!= pair.second.affiliations.end()){
            if (pair.second.publication_year >= year){
                publications.push_back({pair.second.publication_year, pair.first});
            }
        }
    }
    auto compareYear = [](const std::pair<Year, PublicationID>& a, const std::pair<Year, PublicationID>& b) {
        if (a.first < b.first) {
            return true;
        }
        if (a.first > b.first) {
            return false;
        }
        return a.second < b.second;
    };

    std::sort(publications.begin(), publications.end(), compareYear);
    return publications;
}

std::vector<PublicationID> Datastructures::get_referenced_by_chain(PublicationID id)
{
    std::vector<PublicationID> publication_chain;
        auto it = publications_data.find(id);
        if (it == publications_data.end()) {
            return {NO_PUBLICATION};
        }

        PublicationID* publication_ptr = it->second.referenced_by;
        while (publication_ptr != nullptr) {
            publication_chain.push_back(*publication_ptr);
            publication_ptr = publications_data[*publication_ptr].referenced_by;
        }

        return publication_chain;
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


