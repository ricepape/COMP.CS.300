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
    AffiliationData new_aff;
    new_aff.name = id;
    new_aff.coordinates = xy;
    affiliation_data.insert(id, new_aff);
}

Name Datastructures::get_affiliation_name(AffiliationID id)
{
    return affiliation_data[id].name;
}

Coord Datastructures::get_affiliation_coord(AffiliationID /*id*/)
{
    // Replace the line below with your implementation
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
    
}

AffiliationID Datastructures::find_affiliation_with_coord(Coord /*xy*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("find_affiliation_with_coord()");
}

bool Datastructures::change_affiliation_coord(AffiliationID /*id*/, Coord /*newcoord*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("change_affiliation_coord()");
}

bool Datastructures::add_publication(PublicationID /*id*/, const Name &/*name*/, Year /*year*/, const std::vector<AffiliationID> &/*affiliations*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("add_publication()");
}

std::vector<PublicationID> Datastructures::all_publications()
{
    // Replace the line below with your implementation
    throw NotImplemented("all_publications()");
}

Name Datastructures::get_publication_name(PublicationID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_publication_name()");
}

Year Datastructures::get_publication_year(PublicationID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_publication_year()");
}

std::vector<AffiliationID> Datastructures::get_affiliations(PublicationID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_affiliations()");
}

bool Datastructures::add_reference(PublicationID /*id*/, PublicationID /*parentid*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("add_reference()");
}

std::vector<PublicationID> Datastructures::get_direct_references(PublicationID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_direct_references()");
}

bool Datastructures::add_affiliation_to_publication(AffiliationID /*affiliationid*/, PublicationID /*publicationid*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("add_affiliation_to_publication()");
}

std::vector<PublicationID> Datastructures::get_publications(AffiliationID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_publications()");
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

struct CompareName {
    bool operator()(const std::pair<AffiliationID, AffiliationData>& a, const std::pair<AffiliationID, AffiliationData>& b) const {
        return a.second.name < b.second.name;
    }
};

