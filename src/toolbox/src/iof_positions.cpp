#include "iof_chunk.h"

                                                ///Member pushes parameter data into a two column list
void                                                        iof_positions::add_entries( unsigned __int64 Parent, unsigned __int64 Child )
{
    Positions[PARENT].push_back( Parent );
    Positions[CHILD].push_back( Child );
}
                                                ///Member returns the size of child position list
const unsigned __int32                      iof_positions::count_entries()
{
    return Positions[CHILD].size();
}
                                                ///Member searches for a specified child and returns the position of its parent
const unsigned __int64                      iof_positions::get_parent_of( unsigned __int64 Child )
{
    Parent_Itr = Positions[PARENT].begin();
    Child_Itr = Positions[CHILD].begin();

    while ( ( Child_Itr != Positions[CHILD].end() ) && ( Child != *Child_Itr ) )
    {
        Parent_Itr++;
        Child_Itr++;
    }
    return *Parent_Itr;
}
                                                ///Member searches for a specified parent and returns a list of all its immediate children
std::list<const unsigned __int64>       iof_positions::get_children_of( unsigned __int64 Parent )
{
    std::list<const unsigned __int64> temp_l;

    Parent_Itr = Positions[PARENT].begin();
    Child_Itr = Positions[CHILD].begin();

    while ( ( Parent != *Parent_Itr ) && ( Parent_Itr != Positions[PARENT].end() ) )
    {
        Parent_Itr++;
        Child_Itr++;
    }
    while ( Parent == *Parent_Itr )
    {
        temp_l.push_back( *Child_Itr );
        Child_Itr++;
        Parent_Itr++;
    }

    return temp_l;
}
                                                ///Member returns a list of all start positions stored as a child
std::list<const unsigned __int64>       iof_positions::get_all()
{
    return Positions[CHILD];
}
