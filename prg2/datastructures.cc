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
    return static_cast<int>(affiliation_data.size());
}

void Datastructures::clear_all()
{
    affiliation_data.clear();
    publications_data.clear();
    affiliations_with_distances.clear();
    affiliations_with_names.clear();
    affiliations_with_years.clear();
    sorted_affiliations.clear();
    all_affiliations.clear();
    all_publications_vec.clear();
    sorted_affiliations_alp.clear();
    all_connections.clear();
    connected_affs.clear();
    visitedAffiliations.clear();
}

std::vector<AffiliationID> Datastructures::get_all_affiliations()
{
    all_affiliations.clear();
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
        affiliations_with_distances[xy] = id;
        affiliations_with_names[name] = id;
        aff_change = true;
        aff_change_coord = true;
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
    if (aff_change == true){
        sorted_affiliations_alp.clear();
        for (auto& pair : affiliations_with_names)
        {
            sorted_affiliations_alp.push_back(pair.second);
        }
        aff_change = false;
        return sorted_affiliations_alp;
    }
    return sorted_affiliations_alp;
}


std::vector<AffiliationID> Datastructures::get_affiliations_distance_increasing()
{
    if (dis_change == true|| aff_change_coord == true){
        sorted_affiliations.clear();
        for (auto& pair : affiliations_with_distances)
        {
            sorted_affiliations.push_back(pair.second);
        }
        dis_change = false;
        aff_change_coord = false;
        return sorted_affiliations;
    }
    return sorted_affiliations;
}


AffiliationID Datastructures::find_affiliation_with_coord(Coord xy)
{
    auto findit = affiliations_with_distances.find(xy);
    if (findit == affiliations_with_distances.end()) {
        return NO_AFFILIATION;
    }
    return affiliations_with_distances[xy];
}

bool Datastructures::change_affiliation_coord(AffiliationID id, Coord newcoord)
{
     if (affiliation_data.find(id) != affiliation_data.end()) {
        Coord old = affiliation_data[id].coordinates;
        affiliation_data[id].coordinates = newcoord;
        affiliations_with_distances.erase(old);
        affiliations_with_distances[newcoord] = id;
        dis_change = true;
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
        aff_change = true;
        pub_change = true;
        get_all_connections();
        for (const auto& aff_id : affiliations)
        {
            affiliations_with_years[aff_id].insert({year, id});
        }
        return true;
    }
    return false;
}

std::vector<PublicationID> Datastructures::all_publications()
{
    all_publications_vec.clear();
    for (const auto& pair : publications_data)
    {
        all_publications_vec.push_back(pair.first);
    }
    return all_publications_vec;
}

Name Datastructures::get_publication_name(PublicationID id)
{
    auto it = publications_data.find(id);
    if (it == publications_data.end()) {
        return NO_NAME;
    }

    return publications_data[id].name;
}

Year Datastructures::get_publication_year(PublicationID id)
{
    auto it = publications_data.find(id);
    if (it == publications_data.end()) {
        return NO_YEAR;
    }
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
    publications_data[parentid].referencing.insert(id);
    publications_data[id].referenced_by = parentid;
    return true;

}

std::vector<PublicationID> Datastructures::get_direct_references(PublicationID id)
{
    all_publications_vec.clear();
    auto iter_id = publications_data.find(id);

    if (iter_id != publications_data.end()) {
        for (const auto& ref : iter_id->second.referencing) {
            all_publications_vec.push_back(ref);
        }
    }
    return all_publications_vec;
}

bool Datastructures::add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid)
{
    if ((affiliation_data.find(affiliationid) != affiliation_data.end()) &&
    (publications_data.find(publicationid) != publications_data.end())) {
        publications_data[publicationid].affiliations.push_back(affiliationid);
        affiliations_with_years[affiliationid].insert({publications_data[publicationid].publication_year, publicationid});
        pub_change = true;
        get_all_connections();
        return true;
    } else {
        return false;
    }
}

std::vector<PublicationID> Datastructures::get_publications(AffiliationID id)
{
    all_publications_vec.clear();
    auto findit = affiliation_data.find(id);
    if (findit == affiliation_data.end()) {
        return {NO_PUBLICATION};
    }
    for (const auto& pair : publications_data)
    {
        if (std::find(pair.second.affiliations.begin(), pair.second.affiliations.end(), id) != pair.second.affiliations.end())
        {
            all_publications_vec.push_back(pair.first);
        }
    }
    return all_publications_vec;
}

PublicationID Datastructures::get_parent(PublicationID id)
{
    auto it = publications_data.find(id);
    if (it != publications_data.end() && it->second.referenced_by != NO_PUBLICATION) {
        return it->second.referenced_by;
    }
    return NO_PUBLICATION;
}

std::vector<std::pair<Year, PublicationID>> Datastructures::get_publications_after(AffiliationID affiliationid, Year year)
{
    std::vector<std::pair<Year, PublicationID>> publications;
    auto it = affiliation_data.find(affiliationid);
    if (it == affiliation_data.end()) {
        return publications;
    }

    for (const auto& pair : affiliations_with_years[affiliationid])
    {
        if (pair.first >= year){
           publications.push_back(pair);
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
    all_publications_vec.clear();

    auto it = publications_data.find(id);
    if (it == publications_data.end()) {
        return {NO_PUBLICATION};
    }

    PublicationID publication = it->second.referenced_by;
    while (publication != NO_PUBLICATION) {
        all_publications_vec.push_back(publication);
        publication = publications_data[publication].referenced_by;
    }

    return all_publications_vec;
}

std::vector<PublicationID> Datastructures::get_all_references(PublicationID id)
{
    if (publications_data.find(id) == publications_data.end()) {
        return {NO_PUBLICATION};
    }

    std::vector<PublicationID> all_references;
    std::vector<PublicationID> direct_references = get_direct_references(id);
    for (auto direct_reference : direct_references) {
        all_references.push_back(direct_reference);
        std::vector<PublicationID> indirect_references = get_all_references(direct_reference);
        all_references.insert(all_references.end(), indirect_references.begin(), indirect_references.end());
    }

    std::sort(all_references.begin(), all_references.end(), [](PublicationID id1, PublicationID id2) {
        return id1 < id2;
    });
    return all_references;
}

std::vector<AffiliationID> Datastructures::get_affiliations_closest_to(Coord xy)
{
    std::vector<std::pair<double, AffiliationID>> distances;

        // Calculate distances and store them in the vector
        for (const auto& affiliation : affiliations_with_distances) {
            double distance = std::sqrt(
                (xy.x - affiliation.first.x) * (xy.x - affiliation.first.x) +
                (xy.y - affiliation.first.y) * (xy.y - affiliation.first.y)
            );
            distances.emplace_back(distance, affiliation.second);
        }

        // Sort the vector based on distances
        std::sort(distances.begin(), distances.end(), [](const auto& a, const auto& b) {
            return a.first < b.first || (a.first == b.first && a.second < b.second);
        });

        // Extract the affiliation IDs up to three or all if less than three
        std::vector<AffiliationID> result;
        for (const auto& pair : distances) {
            result.push_back(pair.second);
            if (result.size() >= 3) {
                break;
            }
        }

        return result;
}

bool Datastructures::remove_affiliation(AffiliationID id)
{
    auto findit = affiliation_data.find(id);
    if (findit == affiliation_data.end()) {
        return false;
    }

    affiliation_data.erase(findit);

    affiliations_with_years.erase(id);

    for (auto& pair : publications_data) {
        auto& affiliations = pair.second.affiliations;
        affiliations.erase(std::remove(affiliations.begin(), affiliations.end(), id), affiliations.end());
    }

    auto it = std::find_if(affiliations_with_names.begin(), affiliations_with_names.end(),
                           [id](const auto& pair) { return pair.second == id; });
    if (it != affiliations_with_names.end()) {
        affiliations_with_names.erase(it);
    }

    auto distance_it = std::find_if(affiliations_with_distances.begin(), affiliations_with_distances.end(),
                                    [id](const auto& pair) { return pair.second == id; });
    if (distance_it != affiliations_with_distances.end()) {
        affiliations_with_distances.erase(distance_it);
    }

    pub_change = true;
    get_all_connections();
    return true;
}



PublicationID Datastructures::get_closest_common_parent(PublicationID id1, PublicationID id2)
{
    if (publications_data.find(id1) == publications_data.end() ||
            publications_data.find(id2) == publications_data.end()) {
            return NO_PUBLICATION;
        }

        std::vector<PublicationID> parent_id1 = get_referenced_by_chain(id1);
        std::vector<PublicationID> parent_id2 = get_referenced_by_chain(id2);
        for (PublicationID parent : parent_id1) {
            for (PublicationID parent2 : parent_id2) {
            if (parent == parent2) {
                return parent;
                }
            }
        }

        return NO_PUBLICATION;
}

bool Datastructures::remove_publication(PublicationID publicationid)
{
    auto it = publications_data.find(publicationid);
        if (it == publications_data.end()) {
            return false;
        }

        for (auto& pair : affiliations_with_years) {
            for (auto it = pair.second.begin(); it != pair.second.end();) {
                if (it->second == publicationid) {
                    it = pair.second.erase(it);
                } else {
                    ++it;
                }
            }
        }

        for (auto& pair : publications_data) {
            if (pair.second.referenced_by == publicationid) {
                pair.second.referenced_by = NO_PUBLICATION;
            }

            pair.second.referencing.erase(publicationid);
        }

        publications_data.erase(publicationid);

        pub_change = true;

        return true;

}

std::vector<Connection> Datastructures::get_connected_affiliations(AffiliationID id)
{
    connected_affs.clear();
    auto it = affiliation_data.find(id);
    if (it == affiliation_data.end()) {
        return connected_affs;
    }
    for (const auto& conn : all_connections)
    {
        if (conn.aff1 == id)
        {
            connected_affs.push_back(conn);
        }
        else if (conn.aff2 == id)
        {
            Connection new_conn;
            new_conn.aff1 = conn.aff2;
            new_conn.aff2 = conn.aff1;
            new_conn.weight = conn.weight;
            connected_affs.push_back(new_conn);
        }
    }
    return connected_affs;
}

std::vector<Connection> Datastructures::get_all_connections()
{
    if (pub_change){
    all_connections.clear();
    for (const auto& pair : affiliation_data)
    {
        std::vector<PublicationID> main_pubs = get_publications(pair.first);
        for (const auto& pair2 : affiliation_data)
        {
            std::vector<PublicationID> other_pubs = get_publications(pair2.first);
            int count = 0;
            for (const auto& pub : main_pubs)
            {
                std::unordered_set<PublicationID> other_pubs_set(other_pubs.begin(), other_pubs.end());
                if (other_pubs_set.find(pub) != other_pubs_set.end())
                {
                    count += 1;
                }
            }
            if (count > 0 && pair.first != pair2.first)
            {
                Connection new_connection;
                if (pair.first < pair2.first){
                    new_connection.aff1 = pair.first;
                    new_connection.aff2 = pair2.first;
                } else {
                    new_connection.aff1 = pair2.first;
                    new_connection.aff2 = pair.first;
                }

                new_connection.weight = count;
                bool exists = false;
                for (const auto& conn : all_connections){
                    if ((new_connection.aff1 == conn.aff2 && new_connection.aff2 == conn.aff1) || new_connection == conn){
                        exists = true;
                    }
                }
                if (!exists){
                    all_connections.emplace_back(new_connection);
                }
            }
        }
    }
    }
    return all_connections;
}

Path Datastructures::get_any_path(AffiliationID source, AffiliationID target)
{
    Path path;

    // Check if the source and target are the same
    if (source == target || visitedAffiliations.count(source) > 0) {
        return path;
    }

    visitedAffiliations.insert(source);

    auto it = affiliation_data.find(source);
    auto it2 = affiliation_data.find(target);

    if (it == affiliation_data.end() || it2 == affiliation_data.end()) {
        visitedAffiliations.erase(source);  // Remove from visited set if not found
        return path;
    }

    std::vector<Connection> source_connections = get_connected_affiliations(source);

    for (const auto& source_conn : source_connections) {
        // Check if the connection leads to the target
        if (source_conn.aff2 == target) {
            path.push_back(source_conn);
            visitedAffiliations.erase(source);  // Remove from visited set
            return path;
        }

        // Recursively find a path from the current connection's aff2 to the target
        if (visitedAffiliations.find(source_conn.aff2) == visitedAffiliations.end()){
            Path subpath = get_any_path(source_conn.aff2, target);
            if (!subpath.empty()) {
                path.push_back(source_conn);
                path.insert(path.end(), subpath.begin(), subpath.end());
                visitedAffiliations.erase(source);  // Remove from visited set
                return path;
            }
        }
    }

    // Remove from visited set before returning
    visitedAffiliations.erase(source);

    // Return an empty path if no valid path is found
    return path;
}

Path Datastructures::get_path_with_least_affiliations(AffiliationID /*source*/, AffiliationID /*target*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_path_with_least_affiliations()");
}

Path Datastructures::get_path_of_least_friction(AffiliationID /*source*/, AffiliationID /*target*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_path_of_least_friction()");
}

PathWithDist Datastructures::get_shortest_path(AffiliationID /*source*/, AffiliationID /*target*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_shortest_path()");
}

