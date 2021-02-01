/*
One of the advantages of C++ over C is the use of classes. This is an educational
example of creating the C++ 'string' class attempting to mimic to behaviour
and demonstrate the increased ease of use that is not offered in C.
*/
#include <string.h> // strcpy_s and strcat_s, not available in "<string>"
#include <string>
#include <iostream>

class String 
{
    char *p;
    int len;

public:
    String() {
        len = 0;
        p = '\0';
    };

    ~String() {
        delete p;
    };

    String(const char * s);
    String(const String & s);
    friend String operator+(const String& a, const String &);
    friend std::ostream& operator<<(std::ostream& os, String const& m);

};

String::String(const char * s) 
{
    len = strlen(s);
    p = new char[len + 1];
    strcpy_s(p, len + 1,  s);

    /*
    strcpy is a unsafe funtion. When you try to copy a String using strcpy(), to a buffer which is not large enough to contain it, it will cause a buffer overflow.

    char tuna[5];  // a buffer which holds 5 chars incluing the null character.
    char salmon[] = "A String which is longer than 5 chars";

    strcpy( tuna, salmon ); // This will corrupt your memory because of the buffer overflow.

    strcpy_s( tuna, 5, salmon ); // strcpy_s will not write more than 5 chars.

    strcpy_s() is a security enhanced version of strcpy(). With strcpy_s you can specify the size of the destination buffer to avoid buffer overflows during copies.
    */
}

String::String(const String & s)
{
    len = s.len; // Define len on object, equivalent to "self.len = s.len" in Python
    int buffer_size = s.len + 1;

    p = new char[buffer_size];
    strcpy_s(p, buffer_size, s.p);
}

/*
In Python this could be done using __add__ or an alternative approach is not using a friend
and using "String String::operator+(const String & r)".

In C++ this can be interpreted as "If I have the '+' operator with a 'String' type
on and left and a 'String' type on the right, call this function".
*/
String operator+(const String & l, const String & r) {

    String temp;
    temp.len = l.len + r.len;
    int temp_buffer_size = temp.len + 1;

    temp.p = new char[temp_buffer_size];

    strcpy_s(temp.p, temp_buffer_size, l.p); // argument 2 in strcpy_s() is the size of the destination buffer not the size of the source.
    strcat_s(temp.p, temp_buffer_size, r.p);
    /*
    strcat will look for the null-terminator, interpret that as the end of the string, 
    and append the new text there, overwriting the null-terminator in the process,
    and writing a new null-terminator at the end of the concatenation. Therefore requires
    strcpy to be used first in order to have a '\0' (It could be NULL and not work!).
    */
    return temp;
}

/*                                                                      v---------
cout definition is "__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2_IMPORT ostream cout;"

To get cout to accept a String object after the insertion operator, overload the
insertion operator to recognize an ostream object on the left and a Date on the right.
 
                                v---- left = cout, right = String. This is called from "cout << String(...);"
*/
std::ostream & operator<<(std::ostream & os, String const & m) {
    return os << m.p;
}

int main() {
    String left("left "); // Equivalent to, "String left = String("left ")" or "String left = "left"";
    String right("right");
    
    String out = "left " + right + " ";
    std::cout << out;

    return 0;
}
