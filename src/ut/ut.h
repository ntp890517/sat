#ifndef UTIL_H_
#define UTIL_H_ 

#include <iostream>

inline ostream& MSG() { return (cout << "[MSG] ");}
inline ostream& WARN() { return (cout << "[WARN] ");}
inline ostream& ERROR() { return (cout << "[ERROR] ");}

inline ostream& PROGERROR() { return (cout << "[PROGERROR] ");}

#endif
