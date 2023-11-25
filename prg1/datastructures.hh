// Datastructures.hh
//
// Student name: Vu Dinh Thi
// Student email: thi.vu@tuni.fi
// Student number: 151394898

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <math.h>


// Types for IDs
using AffiliationID = std::string;
using PublicationID = unsigned long long int;
using Name = std::string;
using Year = unsigned short int;
using Weight = int;
using Distance = int;

// Return values for cases where required thing was not found
AffiliationID const NO_AFFILIATION = "---";
PublicationID const NO_PUBLICATION = -1;
Name const NO_NAME = "!NO_NAME!";
Year const NO_YEAR = -1;
Weight const NO_WEIGHT = -1;

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};


// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Return value for cases where Distance is unknown
Distance const NO_DISTANCE = NO_VALUE;

// This exception class is there just so that the user interface can notify
// about operations which are not (yet) implemented
class NotImplemented : public std::exception
{
public:
    NotImplemented() : msg_{} {}
    explicit NotImplemented(std::string const& msg) : msg_{msg + " not implemented"} {}

    virtual const char* what() const noexcept override
    {
        return msg_.c_str();
    }
private:
    std::string msg_;
};

// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: O(1)
    // Short rationale for estimate: The function returns the size of the container
    // only, not going through the elements
    unsigned int get_affiliation_count();

    // Estimate of performance: O(n)
    // Short rationale for estimate: The function goes through each element
    // in the container to clear
    void clear_all();

    // Estimate of performance: O(n)
    // Short rationale for estimate: The function goes through each element
    // in the container to retrieve the element and add element to a vector
    std::vector<AffiliationID> get_all_affiliations();

    // Estimate of performance: O(1)
    // Short rationale for estimate: The function goes through the map to 
    // check and inserting into maps
    bool add_affiliation(AffiliationID id, Name const& name, Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Goes through the elements, in worst case all elemets
    // in the map to check and return the name.
    Name get_affiliation_name(AffiliationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Goes through the elements, in worst case all elemets
    // in the map to check and return the coordinates.
    Coord get_affiliation_coord(AffiliationID id);


    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n)
    // Short rationale for estimate: Go through all the elements and insert them 
    // into a vector.
    std::vector<AffiliationID> get_affiliations_alphabetically();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Go through all the elements and insert them 
    // into a vector with distance increasing.
    std::vector<AffiliationID> get_affiliations_distance_increasing();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Go through all the elements to check if the 
    // coordinations exists
    AffiliationID find_affiliation_with_coord(Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Go through all the elements in worst case 
    // to check if the affiliation exists
    bool change_affiliation_coord(AffiliationID id, Coord newcoord);


    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n)
    // Short rationale for estimate: Go through all the elements to check if the publication exists 
    // then add it to the container.
    bool add_publication(PublicationID id, Name const& name, Year year, const std::vector<AffiliationID> & affiliations);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Go through all the elements to get and push them 
    // into the container.
    std::vector<PublicationID> all_publications();

    // Estimate of performance: O(1)
    // Short rationale for estimate: Return a name value with a given key, derived instantly
    Name get_publication_name(PublicationID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate: Return the year value with a given key, derived instantly
    Year get_publication_year(PublicationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Return the vector of affiliationid value with a given key
    std::vector<AffiliationID> get_affiliations(PublicationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Go through the elements in publications_data to check
    // if the ids exist, then add instantly the new value.
    bool add_reference(PublicationID id, PublicationID parentid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Go through the elements in publications_data to check
    // if the id exists, then add instantly the new value.
    std::vector<PublicationID> get_direct_references(PublicationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Use the find function to go through all elements
    // to check its existence.
    bool add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Go through each element in the publication data,
    // the for each publication, go through all elements in the related affiliations
    std::vector<PublicationID> get_publications(AffiliationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Use the find function to go through all elements
    // to check the publication id's existence.
    PublicationID get_parent(PublicationID id);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: Go through each element in the publication data,
    // the for each publication, go through all elements in the related affiliations.
    // All the other has time complexity small enough compared to this
    std::vector<std::pair<Year, PublicationID>> get_publications_after(AffiliationID affiliationid, Year year);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Go through each element to check the existence
    // of the publication id and go through the chain of parent reference.
    std::vector<PublicationID> get_referenced_by_chain(PublicationID id);


    // Non-compulsory operations

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<PublicationID> get_all_references(PublicationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<AffiliationID> get_affiliations_closest_to(Coord xy);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: Go through all elements in the given map to access
    // to the AffiliationID vector, then from that delete the given id.
    bool remove_affiliation(AffiliationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    PublicationID get_closest_common_parent(PublicationID id1, PublicationID id2);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate:Go through all elements in the given map to access
    // to the PublicationID set, then from that delete the given id.
    bool remove_publication(PublicationID publicationid);


private:
    struct AffiliationData {
        Name name;
        Coord coordinates;
    };

    std::unordered_map<AffiliationID, AffiliationData> affiliation_data;

    struct PublicationData {
       Name name;
       Year publication_year;
       std::vector<AffiliationID> affiliations;
       std::unordered_set<PublicationID> referencing;
       PublicationID referenced_by = NO_PUBLICATION;
    };

    struct DistanceComparator{
        bool operator()(Coord x1, Coord x2) const {
            if (std::sqrt(x1.x*x1.x+x1.y*x1.y) < std::sqrt(x2.x*x2.x+x2.y*x2.y)){
                return true;
            }
            if (std::sqrt(x1.x*x1.x+x1.y*x1.y) > std::sqrt(x2.x*x2.x+x2.y*x2.y)){
                return false;
            }
            else return x1.y < x2.y;
        }
    };

    std::unordered_map<PublicationID, PublicationData> publications_data;
    std::map<Coord, AffiliationID, DistanceComparator> affiliations_with_distances;
    std::map<Name, AffiliationID> affiliations_with_names;
    std::unordered_map<AffiliationID, std::unordered_map<Year, PublicationID>> affiliations_with_years;
    std::vector<AffiliationID> sorted_affiliations;
    std::vector<AffiliationID> all_affiliations;
    std::vector<PublicationID> all_publications_vec;
};

#endif // DATASTRUCTURES_HH
