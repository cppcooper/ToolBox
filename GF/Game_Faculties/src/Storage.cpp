#include "../Storage.h"

Asset_Storage::~Asset_Storage()
{
	for ( auto ptr : Address_Table )
	{
		delete ptr;
	}
}

void Asset_Storage::Update()
{

}