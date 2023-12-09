// Datastructures.cc
//
// Student name:
// Student email:
// Student number:

#include "datastructures.hh"

#include <random>

#include <cmath>

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
{
    // Write any initialization you need here
}

Datastructures::~Datastructures()
{
    // Write any cleanup you need here
}

unsigned int Datastructures::get_affiliation_count()
{
    return Affiliations_map.size();
}

void Datastructures::clear_all()
{
    Affiliations_map.clear();
    Publications_map.clear();
    Affiliations_vec.clear();
    Coordinate_map.clear();
    alphabetical_names.clear();
    affiliations_increasing.clear();
    Publications_vec.clear();
    Name_map.clear();
}

std::vector<AffiliationID> Datastructures::get_all_affiliations()
{
    return Affiliations_vec;
}

bool Datastructures::add_affiliation(AffiliationID id, const Name &name, Coord xy)
{
    aff_info new_affiliation{id, name, xy, {}};

    if (Affiliations_map.find(id) == Affiliations_map.end())
    {
        Affiliations_map[id] = new_affiliation;
        Coordinate_map[xy] = new_affiliation;
        Affiliations_vec.push_back(id);
        Name_map[name] = new_affiliation;

        return true;
    }

    return false;
}

Name Datastructures::get_affiliation_name(AffiliationID id)
{
    auto it = Affiliations_map.find(id);
       if (it != Affiliations_map.end())
       {
           return it->second.name;
       }
       return NO_NAME;
}

Coord Datastructures::get_affiliation_coord(AffiliationID id)
{
    auto it = Affiliations_map.find(id);
    if (it != Affiliations_map.end())
    {
        return it->second.coordinates;
    }
    return NO_COORD;
}

std::vector<AffiliationID> Datastructures::get_affiliations_alphabetically()
{
    if (alphabetical_names.empty())
    {
        update_names();
    }

    return alphabetical_names;
}

void Datastructures::update_names()
{
    alphabetical_names.clear();

    for (const auto &elem : Name_map)
    {
        alphabetical_names.push_back(elem.second.aff_ID);
    }
}

std::vector<AffiliationID> Datastructures::get_affiliations_distance_increasing()
{
    if (affiliations_increasing.empty())
    {
        update_coord();
    }

    return affiliations_increasing;
}

void Datastructures::update_coord()
{
    affiliations_increasing.clear();

    for (const auto &elem : Coordinate_map) {
        affiliations_increasing.push_back(elem.second.aff_ID);
    }
}

AffiliationID Datastructures::find_affiliation_with_coord(Coord xy)
{
    auto it = Coordinate_map.find(xy);

    if (it != Coordinate_map.end()) {
        return it->second.aff_ID;
    }

    return NO_AFFILIATION;
}

bool Datastructures::change_affiliation_coord(AffiliationID id, Coord newcoord)
{
    auto it_affiliation = Affiliations_map.find(id);

    if (it_affiliation != Affiliations_map.end()) {
        // Erase the old coordinate from the Coordinate_map
        Coordinate_map.erase(it_affiliation->second.coordinates);

        // Update the affiliation's coordinates
        it_affiliation->second.coordinates = newcoord;

        // Update the Coordinate_map with the new coordinate
        Coordinate_map[newcoord] = it_affiliation->second;

        update_coord();
        return true;
    }

    return false;
}

bool Datastructures::add_publication(PublicationID id, const Name &name, Year year, const std::vector<AffiliationID> &affiliations)
{
    pub_info new_publication{id, name, year, affiliations, {}, NO_PUBLICATION};

    if(Publications_map.find(id) == Publications_map.end())
    {
        Publications_map[id] = new_publication;
        Publications_vec.push_back(id);
        return true;
    }

    return false;
}

std::vector<PublicationID> Datastructures::all_publications()
{
    return Publications_vec;
}

Name Datastructures::get_publication_name(PublicationID id)
{
    auto it = Publications_map.find(id);
       if (it != Publications_map.end())
       {
           return it->second.name;
       }
       return NO_NAME;
}

Year Datastructures::get_publication_year(PublicationID id)
{
    auto it = Publications_map.find(id);
       if (it != Publications_map.end())
       {
           return it->second.year;
       }
       return NO_YEAR;
}

std::vector<AffiliationID> Datastructures::get_affiliations(PublicationID id)
{
    auto it = Publications_map.find(id);
       if (it != Publications_map.end())
       {
           return it->second.affiliations;
       }
       return {NO_AFFILIATION};
}

bool Datastructures::add_reference(PublicationID id, PublicationID parentid)
{
    auto it_id = Publications_map.find(id);
    auto it_parentid = Publications_map.find(parentid);

    if (it_id == Publications_map.end() || it_parentid == Publications_map.end())
    {
       return false;
    }

    it_parentid->second.references.push_back(id);
    it_id->second.referenced_by = parentid;

    return true;
}

std::vector<PublicationID> Datastructures::get_direct_references(PublicationID id)
{
    auto it = Publications_map.find(id);
       if (it != Publications_map.end())
       {
           return it->second.references;
       }
       return {NO_PUBLICATION};
}

bool Datastructures::add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid)
{
    auto it_affiliation = Affiliations_map.find(affiliationid);
    auto it_publication = Publications_map.find(publicationid);

    if (it_affiliation != Affiliations_map.end() && it_publication != Publications_map.end())
    {
        it_publication->second.affiliations.push_back(affiliationid);
        it_affiliation->second.publications.push_back(publicationid);
        return true;
    }

    // If either affiliation or publication does not exist, return false
    return false;
}

std::vector<PublicationID> Datastructures::get_publications(AffiliationID id)
{
    auto it = Affiliations_map.find(id);

       if (it != Affiliations_map.end())
       {
           return it->second.publications;
       }
       return {NO_PUBLICATION};
}

PublicationID Datastructures::get_parent(PublicationID id)
{
    auto it = Publications_map.find(id);

    if (it != Publications_map.end())
    {
        auto parent_iter = Publications_map.find(it->second.referenced_by);
        if (parent_iter == Publications_map.end() || parent_iter->second.name == NO_NAME)
        {
            return NO_PUBLICATION;
        }

        else return it->second.referenced_by;
    }

    else {return NO_PUBLICATION;}
}

std::vector<std::pair<Year, PublicationID> > Datastructures::get_publications_after(AffiliationID affiliationid, Year year)
{
    auto it_affiliation = Affiliations_map.find(affiliationid);

    if (it_affiliation != Affiliations_map.end())
    {
        std::vector<std::pair<Year, PublicationID>> result;

        for (const PublicationID& pub_id : it_affiliation->second.publications)
        {
            auto it_publication = Publications_map.find(pub_id);
            if (it_publication != Publications_map.end() && it_publication->second.year >= year)
            {
                result.emplace_back(it_publication->second.year, pub_id);
            }
        }

        std::sort(result.begin(), result.end(), [](const auto& a, const auto& b) {
            return std::tie(a.first, a.second) < std::tie(b.first, b.second);
        });

        return result;
    }

    return {{NO_YEAR, NO_PUBLICATION}};
}

std::vector<PublicationID> Datastructures::get_referenced_by_chain(PublicationID id)
{
    auto it = Publications_map.find(id);

    if (it == Publications_map.end())
    {
        return {NO_PUBLICATION};
    }

    std::vector<PublicationID> result;

    auto current_id = id;

    while (Publications_map.find(current_id) != Publications_map.end())
    {
        current_id = Publications_map[current_id].referenced_by;

        if (current_id != NO_PUBLICATION && current_id != 0)
        {
            result.push_back(current_id);
        }

        else {break;}
    }

    return result;
}

std::vector<PublicationID> Datastructures::get_all_references(PublicationID id)
{
    auto it = Publications_map.find(id);

    if (it == Publications_map.end()) {
        return {NO_PUBLICATION};
    }

    std::vector<PublicationID> result;
    std::unordered_set<PublicationID> visited;

    std::function<void(PublicationID)> traverse_references = [&](PublicationID current_id) {
        auto current_it = Publications_map.find(current_id);

        if (current_it != Publications_map.end()) {
            for (PublicationID reference_id : current_it->second.references) {
                if (visited.find(reference_id) == visited.end()) {
                    visited.insert(reference_id);
                    result.push_back(reference_id);
                    traverse_references(reference_id);
                }
            }
        }
    };

    traverse_references(id);

    return result;
}

std::vector<AffiliationID> Datastructures::get_affiliations_closest_to(Coord xy)
{
    std::vector<std::pair<AffiliationID, double>> distances;

    for (const auto& affiliation : Affiliations_map){
        double dist = calculate_distance(xy, affiliation.second.coordinates);
        distances.emplace_back(affiliation.first, dist);
    }

    std::sort(distances.begin(), distances.end(), [](const auto& a, const auto& b){
        return a.second < b.second;
    });

    std::vector<AffiliationID> result;
    for (size_t i = 0; i < std::min(distances.size(), static_cast<size_t>(3)); i++)
    {
        result.push_back(distances[i].first);
    }

    return result;
}

double Datastructures::calculate_distance(const Coord& coord1, const Coord& coord2)
{
    return std::sqrt(std::pow(coord1.x - coord2.x, 2) + std::pow(coord1.y - coord2.y, 2));
}

bool Datastructures::remove_affiliation(AffiliationID id)
{
    auto it = Affiliations_map.find(id);

    if (it != Affiliations_map.end())
    {
        Affiliations_map.erase(it->second.aff_ID);
        for (auto it = Coordinate_map.begin(); it != Coordinate_map.end();)
        {
            if (it->second.aff_ID == id) {it = Coordinate_map.erase(it);}
            else {++it;}
        }
        for (auto it = Name_map.begin(); it!= Name_map.end();)
        {
            if (it->second.aff_ID == id) {it = Name_map.erase(it);}
            else {++it;}
        }
        Affiliations_vec.erase(std::remove(Affiliations_vec.begin(), Affiliations_vec.end(), id), Affiliations_vec.end());
        for (auto &elem : Publications_map)
        {
            elem.second.affiliations.erase(elem.second.affiliations.begin(), elem.second.affiliations.end());
        }
        alphabetical_names.clear();
        affiliations_increasing.clear();
        return true;
    }

    else {return false;}
}

PublicationID Datastructures::get_closest_common_parent(PublicationID id1, PublicationID id2)
{
    auto it_1 = Publications_map.find(id1);
    auto it_2 = Publications_map.find(id2);

    if (it_1 != Publications_map.end() && it_2 != Publications_map.end()){

        auto parent_1 = id1;
        auto parent_2 = id2;

        while (parent_1 != NO_PUBLICATION && parent_2 != NO_PUBLICATION){

            if (parent_1 == parent_2) {return parent_2;}

            if (get_parent(parent_1) != NO_PUBLICATION){
                parent_1 = get_parent(parent_1);
            }

            if (get_parent(parent_2) != NO_PUBLICATION){
                parent_2 = get_parent(parent_2);
            }

            if (get_parent(parent_1) == NO_PUBLICATION && get_parent(parent_2) == NO_PUBLICATION){
                return parent_2;
            }
        }
    }
    return NO_PUBLICATION;
}

bool Datastructures::remove_publication(PublicationID publicationid)
{
    auto it = Publications_map.find(publicationid);

    if (it == Publications_map.end())
    {
        return false;
    }

    for (auto& iterator : Publications_map)
    {
        auto& references = iterator.second.references;
        references.erase(std::remove(references.begin(), references.end(), publicationid), references.end());

        if (iterator.second.referenced_by == publicationid)
        {
            iterator.second.referenced_by = NO_PUBLICATION;
        }
    }

    for (auto& affiliation : Affiliations_map)
    {
        auto& publications = affiliation.second.publications;
        publications.erase(std::remove(publications.begin(), publications.end(), publicationid), publications.end());
    }

    Publications_map.erase(it);
    Publications_vec.erase(std::remove(Publications_vec.begin(), Publications_vec.end(), publicationid), Publications_vec.end());

    return true;
}










