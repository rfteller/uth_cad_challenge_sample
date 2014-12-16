

#include <string>
#include <vector>


std::vector<std::string>* separate_std_string(
	std::vector<std::string>* dest, const std::string &src, const std::string &delim)
{
    std::string::size_type start = 0;	

    while(true)
	{
		std::string::size_type end = src.find(delim, start);	

        if(end != std::string::npos)
		{	
			dest->push_back(src.substr(start, end - start));
        } 
		else 
		{
            dest->push_back(src.substr(start, src.length() - start));
            break;
        }

        start = end + delim.length();	
    }

    return dest;
}

