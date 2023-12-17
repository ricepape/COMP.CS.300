// Datastructures.cc
//
// Student name:
// Student email:
// Student number:

#include "datastructures.hh"

#include <random>

#include <cmath>
#include <queue>

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
        affiliation_connections[id] = std::vector<Connection>();
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

        for (const auto& aff_id : affiliations)
        {
            affiliations_with_years[aff_id].insert({year, id});
        }
        for (const auto& aff_id : affiliations)
        {
            affiliationPublications[aff_id].push_back(id);
        }
        pub_change = true;
        create_connection(publications_data[id]);
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

    auto pub = publications_data.find(publicationid);
    if ((affiliation_data.find(affiliationid) != affiliation_data.end()) &&
    (pub != publications_data.end())) {
        publications_data[publicationid].affiliations.push_back(affiliationid);
        affiliations_with_years[affiliationid].insert({publications_data[publicationid].publication_year, publicationid});
        pub_change = true;
        create_connection(pub->second, affiliationid);
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


std::vector<PublicationID> Datastructures::get_common_publication(AffiliationID id1, AffiliationID id2)
{
    std::vector<PublicationID> pub1 = get_publications(id1);
    std::vector<PublicationID> pub2 = get_publications(id2);

    std::vector<PublicationID> commonPublications;
    if (id1 == id2) {
        return commonPublications;
    }
    for (const PublicationID id : pub1) {
        if (std::find(pub2.begin(), pub2.end(), id) != pub2.end()) {
            commonPublications.push_back(id);
        }
    }

    return commonPublications;
}

void Datastructures::create_connection(const PublicationData& publication, AffiliationID aff_to_fix)
{
    if (aff_to_fix == NO_AFFILIATION) {
        for (size_t i = 0; i < publication.affiliations.size(); ++i) {
            for (size_t j = i + 1; j < publication.affiliations.size(); ++j) {
                AffiliationID target;
                AffiliationID source;
                if (publication.affiliations[i] < publication.affiliations[j]) {
                    source = publication.affiliations[i];
                    target = publication.affiliations[j];
                }
                else {
                    source = publication.affiliations[j];
                    target = publication.affiliations[i];
                }
                if (target == source) {
                    break;
                }
                bool exist = false;
                auto it = affiliation_connections.find(source);

                if (it != affiliation_connections.end()) {
                    std::vector<Connection> connections = it->second;
                    for (auto& conn : connections) {
                        if (conn.aff1 == source && conn.aff2 == target) {
                            // Found a connection with the same source and target
                            exist = true;
                            conn.weight += 1;
                            break;
                        }
                    }

                    if (!exist) {
                        Connection connection, connection_reverse;
                        connection.aff1 = source;
                        connection.aff2 = target;
                        connection.weight = 1;
                        connection_reverse.aff1 = target;
                        connection_reverse.aff2 = source;
                        connection_reverse.weight = 1;
                        all_connections.push_back(connection);

                        affiliation_connections[source].push_back(connection);
                        affiliation_connections[target].push_back(connection_reverse);

                    }

                }
                if (exist) {
                    auto it_reverse = affiliation_connections.find(target);
                    if (it_reverse != affiliation_connections.end()) {
                        std::vector<Connection> connections_reverse = it_reverse->second;
                        for (auto& conn : connections_reverse) {
                            if (conn.aff1 == target && conn.aff2 == source) {
                                conn.weight += 1;
                                break;
                            }
                        }
                    }

                }
            }
        }
    } else {
        for (size_t i = 0; i < publication.affiliations.size(); ++i) {
            AffiliationID target;
            AffiliationID source;
            if (publication.affiliations[i] < aff_to_fix) {
                source = publication.affiliations[i];
                target = aff_to_fix;
            }
            else {
                source = aff_to_fix;
                target = publication.affiliations[i];
            }
            if (target == source) {
                break;
            }
            bool exist = false;
            auto it = affiliation_connections.find(source);

            if (it != affiliation_connections.end()) {
                std::vector<Connection> connections = it->second;
                for (auto& conn : connections) {
                    if (conn.aff1 == source && conn.aff2 == target) {
                        // Found a connection with the same source and target
                        exist = true;
                        conn.weight += 1;
                        break;
                    }
                }

                if (!exist) {
                    Connection connection, connection_reverse;
                    connection.aff1 = source;
                    connection.aff2 = target;
                    connection.weight = 1;
                    connection_reverse.aff1 = target;
                    connection_reverse.aff2 = source;
                    connection_reverse.weight = 1;
                    all_connections.push_back(connection);

                    affiliation_connections[source].push_back(connection);
                    affiliation_connections[target].push_back(connection_reverse);

                }

            }
            if (exist) {
                auto it_reverse = affiliation_connections.find(target);
                if (it_reverse != affiliation_connections.end()) {
                    std::vector<Connection> connections_reverse = it_reverse->second;
                    for (auto& conn : connections_reverse) {
                        if (conn.aff1 == target && conn.aff2 == source) {
                            conn.weight += 1;
                            break;
                        }
                    }
                }

            }
        }
    }
}

std::vector<Connection> Datastructures::get_connected_affiliations(AffiliationID id)
{

    if (affiliation_connections.find(id) != affiliation_connections.end()) {
        return affiliation_connections[id];
    }

    return {};
}

std::vector<Connection> Datastructures::get_all_connections()
{
    return all_connections;
}

bool Datastructures::findPath(AffiliationID current, AffiliationID target, Path& path, std::unordered_map<AffiliationID, bool>& visited) {

    if (current == target) {
        return true;
    }

    visited[current] = true;

    for (const Connection &connection : affiliation_connections[current]) {

        // Check if the connection is not visited and if it leads to the target
        if (!visited[connection.aff2]) {
            path.push_back(connection);

            if (findPath(connection.aff2, target, path, visited)) {

                return true;
            }
            path.pop_back();
        }
    }

    return false;
}

Path Datastructures::get_any_path(AffiliationID source, AffiliationID target)
{
    Path path;
    std::unordered_map<AffiliationID, bool> visited;

    if (source == target) {
        return path;
    }

    for (auto& conn : all_connections) {
        visited[conn.aff1] = false;
        visited[conn.aff2] = false;
    }

    if (findPath(source, target, path, visited)) {
        return path;
    }

    return {};


}


Path Datastructures::get_path_with_least_affiliations(AffiliationID source, AffiliationID target)
{
    // create_connection_for_all();
        std::unordered_set<AffiliationID> visited;
        std::queue<Path> paths;
        paths.push({});

        while (!paths.empty()) {
            std::vector<Connection> currentPath = paths.front();
            paths.pop();

            Connection lastConnection;
            if (!currentPath.empty()) {
                lastConnection = currentPath.back();
            }

            AffiliationID currentAffiliation = (currentPath.empty()) ? source : lastConnection.aff2;

            if (currentAffiliation == target) {
                return currentPath;
            }

            visited.insert(currentAffiliation);

            for (auto& conn : affiliation_connections[currentAffiliation]) {
                if (visited.find(conn.aff2) == visited.end()) {
                    std::vector<Connection> newPath = currentPath;
                    newPath.push_back(conn);
                    paths.push(newPath);
                }
            }
        }

        return {};
}

double Datastructures::calculateFriction(const Path& path) {
    double minWeight = std::numeric_limits<double>::max();
    for (const auto& conn : path) {
        if (conn.weight < minWeight) {
            minWeight = conn.weight;
        }
    }

    return 1.0 / minWeight;
}

void Datastructures::findAllPaths(AffiliationID source, AffiliationID target, Path& currentPath, std::vector<Path>& allPaths, std::unordered_set<AffiliationID>& visited) {

    visited.insert(source);

    if (source == target) {
        allPaths.push_back(currentPath);
    } else {
        for (const auto& conn : affiliation_connections[source]) {
            if (visited.find(conn.aff2) == visited.end()) {
                currentPath.push_back(conn);
                findAllPaths(conn.aff2, target, currentPath, allPaths, visited);
                currentPath.pop_back();
            }
        }
    }

    visited.erase(source);

}

Path Datastructures::get_path_of_least_friction(AffiliationID source, AffiliationID target)
{
    Path path;
        std::vector<Path> allPaths;
        std::unordered_set<AffiliationID> visited;
        findAllPaths(source, target, path, allPaths, visited);
        double minFriction = std::numeric_limits<double>::max();
        int minPathLength = std::numeric_limits<int>::max();
        Path bestPath;
        for (auto& path : allPaths) {
            double friction = calculateFriction(path);
            if (friction < minFriction) {
                minFriction = friction;
                minPathLength = path.size();
                bestPath = path;
            }
            if (friction == minFriction) {
                if (int(path.size()) < minPathLength) {
                    minPathLength = path.size();
                    bestPath = path;
                }
            }
        }
        return bestPath;
}

double Datastructures::calculateConnectionLength(const Connection conn) {
    auto source = affiliation_data.find(conn.aff1);
    auto target = affiliation_data.find(conn.aff2);
    double length = 0;
    if (source != affiliation_data.end() && source != affiliation_data.end()) {
        length = std::sqrt(std::pow(source->second.coordinates.x - target->second.coordinates.x, 2) + std::pow(source->second.coordinates.y - target->second.coordinates.y, 2));

    }
    return length;
}

std::pair<double, PathWithDist> Datastructures::Dijkstra_shortest(AffiliationID source, AffiliationID target) {
    std::priority_queue<std::pair<int, AffiliationID>, std::vector<std::pair<int, AffiliationID>>, std::greater<std::pair<int, AffiliationID>>> pq;
    std::unordered_map<AffiliationID, int> distance;
    std::unordered_map<AffiliationID, Connection*> previous; // Store previous connections

    // Initialize distances to infinity
    for (auto& kp : affiliation_connections) {
        distance[kp.first] = std::numeric_limits<int>::max();
    }

    distance[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        AffiliationID current = pq.top().second;
        int currentDistance = pq.top().first;
        pq.pop();

        if (current == target) {
            PathWithDist shortestPath;
            while (previous.find(current) != previous.end()) {
                shortestPath.push_back(std::make_pair(*previous[current], calculateConnectionLength(*previous[current])));
                current = previous[current]->aff1; // Move to the previous node in the path
            }
            std::reverse(shortestPath.begin(), shortestPath.end()); // Reverse to get correct order
            return { distance[target], shortestPath }; // Return shortest path length and the path
        }

        for (Connection conn : affiliation_connections[current]) {
            double connection_length = calculateConnectionLength(conn);
            int newDistance = currentDistance + connection_length;
            if (newDistance < distance[conn.aff2]) {
                distance[conn.aff2] = newDistance;
                pq.push({newDistance, conn.aff2});
                previous[conn.aff2] = &conn; // Record the connection for the shortest path
            }
        }
    }

    return { -1, {} }; // No path found, return -1 for distance and an empty vector for the path
}

PathWithDist Datastructures::get_shortest_path(AffiliationID source, AffiliationID target)
{
    PathWithDist bestPath;
        double shortestPathLength;


        std::tie(shortestPathLength, bestPath) = Dijkstra_shortest(source, target);
        if (shortestPathLength == -1 || shortestPathLength == 0) {
            return bestPath;
        } else {
            return bestPath;
        }
}
