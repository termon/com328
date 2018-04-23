/* 
 * File:   Movie.h
 * Author: aiden
 *
 * Created on 13 December 2014, 14:19
 */

#ifndef MOVIE_H
#define	MOVIE_H

#include <string>
#include <vector>
#include <sstream>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) 
{
    std::stringstream ss(s+' ');
    std::string item;
    while(std::getline(ss, item, delim)) 
    {
        elems.push_back(item);
    }
    return elems;
}

class Movie
{
public:
    Movie() : title(), director() {};
    Movie(std::string serial) {
        init(serial);
    };
    
    inline void init(std::string serial) { 
        std::vector<std::string> ss;
        ss = split(serial,'#',ss);
        if (ss.capacity() > 1) {
            title = ss[0];
            director = ss[1];
        }
    };
    
    inline std::string  getTitle() const                { return title; };
    inline std::string  getDirector() const             { return director;};
    inline void         print(std::ostream & os) const  { os << title << "#" << director; }

private:
    std::string title;
    std::string director;    
};

std::ostream& operator <<(std::ostream& output, const Movie& m) {
    m.print(output);
    return output;  // for multiple << operators.
}

/* std::istream& operator >>(std::istream& input, Movie& m) {
    //char s[256];
    std::string s;
    input >> s;
    //input.getline(s,256);
    m.init(s);
    return input;  // for multiple >> operators.
} */

#endif	/* MOVIE_H */

