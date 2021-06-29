#ifndef _MDR_FILE_H_
#define _MDR_FILE_H_

#include <stdio.h>
#include <iostream>

#include "types.h"
#include "string.h"
#include "result.h"

namespace mdr
{
    class file_stream
    {
    public:
	file_stream(const char file_path[])
	{
	    internal_open(file_path);
	}

	~file_stream()
	{
	    internal_close();
	}
	
	string read_line()
	{
	    auto bytes_read = ::fread(m_buffer, sizeof(char), sizeof(m_buffer) - 1, m_file);

	    if (!bytes_read)
		return "";

	    string result { m_buffer };

	    std::cout << "-- result.size(): " << result.size() << '\n';
	    std::cout << "-- bytes_read: " << bytes_read << '\n';
	    
	    if (bytes_read < m_buff_size)
	    {
		std::cout << "-- substr\n";
		return result.substr(static_cast<size_t>(0), bytes_read);
	    }

	    std::cout << "-- fullstr\n";
	    return result;
	}

    private:
	result internal_open(const char file_path[])
	{
	    m_file = ::fopen(file_path, "r");

	    return result();
	}

	void internal_close()
	{
	    ::fclose(m_file);
	}
	
    private:
	static const size_t m_buff_size { 50 };

	char m_buffer[50];
	FILE* m_file;
    };
}

#endif
