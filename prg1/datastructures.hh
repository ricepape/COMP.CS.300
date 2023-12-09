// Datastructures.hh
//
// Student name:
// Student email:
// Student number:

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>
#include <memory>
#include <map>
#include <math.h>
#include <unordered_set>
#include <stack>
#include <unordered_map>


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
    Distance dist_1 = sqrt(pow(c1.x,2)+pow(c1.y,2));
    Distance dist_2 = sqrt(pow(c2.x,2)+pow(c2.y,2));

    if (dist_1 < dist_2) {return true;}
    if (dist_2 < dist_1) {return false;}
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
    // Short rationale for estimate: The size of a std::unordered_map
    // is typically implemented to be retrieved in constant time.
    unsigned int get_affiliation_count();

    // Estimate of performance: O(n)
    // Short rationale for estimate: The clear-operation for std::unordered_map
    // and std::vector typically has a linear time complexity proportional to
    // the number of elements.
    void clear_all();

    // Estimate of performance: O(n)
    // Short rationale for estimate: returning a vector by value typically
    // involves a move operation, which is linear.
    std::vector<AffiliationID> get_all_affiliations();

    // Estimate of performance: O(n)
    // Short rationale for estimate:The find()-operation is O(n) on average, so adding a new
    // affiliation is linear.
    bool add_affiliation(AffiliationID id, Name const& name, Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate:The find()-operation is
    // O(n) on average, so getting an affiliation name is linear.
    Name get_affiliation_name(AffiliationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: The find()-operation is
    // O(n) on average, so getting an affiliation coordinate is linear.
    Coord get_affiliation_coord(AffiliationID id);


    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n * log(n))
    // Short rationale for estimate: This method uses a bucket-sort,
    // which is typically estimated as O(n * log(n)).
    std::vector<AffiliationID> get_affiliations_alphabetically();

    // Estimate of performance: O(n * log(n))
    // Short rationale for estimate: extracts the affiliations from the Coordinate_map,
    // and the final sorting step determines the time complexity.
    std::vector<AffiliationID> get_affiliations_distance_increasing();

    // Estimate of performance: O(n)
    // Short rationale for estimate:The find()-operation is
    // O(n) on average, so finding an affiliation with a coordinate is linear.
    AffiliationID find_affiliation_with_coord(Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: The std::map::erase and std::map::operator[]
    // operations have linear time complexity for balanced trees.
    bool change_affiliation_coord(AffiliationID id, Coord newcoord);


    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n)
    // Short rationale for estimate: The find()-operation is
    // O(n) on average, so adding a new publication is linear.
    bool add_publication(PublicationID id, Name const& name, Year year, const std::vector<AffiliationID> & affiliations);

    // Estimate of performance: O(n)
    // Short rationale for estimate: returning a vector by value typically
    // involves a move operation, which is linear.
    std::vector<PublicationID> all_publications();

    // Estimate of performance: O(n)
    // Short rationale for estimate: The find()-operation
    // is O(n) on average, so getting a publication name is linear.
    Name get_publication_name(PublicationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate:The find()-operation is
    // O(n) on average, so getting a publication year is linear.
    Year get_publication_year(PublicationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: The find()-operation is
    // O(n) on average, so getting affiliations is linear.
    std::vector<AffiliationID> get_affiliations(PublicationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: The find()-operation is
    // O(n) on average, so adding a reference is linear.
    bool add_reference(PublicationID id, PublicationID parentid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: The find()-operation is
    //  O(n) on average, so getting a direct reference is linear.
    std::vector<PublicationID> get_direct_references(PublicationID id);

    // Estimate of performance: O(log(n))
    // Short rationale for estimate: This method has several
    // steps so it is O(log(n)) on average.
    bool add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: The find()-operation is
    // O(n) on average, so getting publications is linear.
    std::vector<PublicationID> get_publications(AffiliationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: The find()-operation is
    // O(n) on average, so getting a parent is linear.
    PublicationID get_parent(PublicationID id);

    // Estimate of performance: O(n * log(n))
    // Short rationale for estimate: Contains a lot of steps, find()-
    // operator, for-loop and sorting.´
    std::vector<std::pair<Year, PublicationID>> get_publications_after(AffiliationID affiliationid, Year year);

    // Estimate of performance: O(n)
    // Short rationale for estimate: The find()-operation is
    //  O(n) on average, so getting referenced by chain is linear.
    std::vector<PublicationID> get_referenced_by_chain(PublicationID id);

    // Non-compulsory operations

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<PublicationID> get_all_references(PublicationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<AffiliationID> get_affiliations_closest_to(Coord xy);

    void find_ancestors(PublicationID id, std::unordered_set<PublicationID>& ancestors);


    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_affiliation(AffiliationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_publication(PublicationID publicationid);

    double calculate_distance(const Coord& coord1, const Coord& coord2);

private:

    struct aff_info
    {
        AffiliationID aff_ID;
        Name name;
        Coord coordinates;
        std::vector<PublicationID> publications;
    };

    struct pub_info
    {
        PublicationID pub_ID;
        Name name;
        Year year;
        std::vector<AffiliationID> affiliations;
        std::vector<PublicationID> references;
        PublicationID referenced_by;
    };

    std::unordered_map<AffiliationID, aff_info> Affiliations_map;
    std::vector<AffiliationID> Affiliations_vec;

    std::map<Coord, aff_info> Coordinate_map;
    std::vector<AffiliationID> affiliations_increasing;
    void update_coord();

    std::map<Name, aff_info> Name_map;
    std::vector<AffiliationID> alphabetical_names;
    void update_names();

    std::unordered_map<PublicationID, pub_info> Publications_map;
    std::vector<PublicationID> Publications_vec;
};

#endif // DATASTRUCTURES_HH
