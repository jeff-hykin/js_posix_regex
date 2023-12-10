// #include <iostream>
#include <regex>
#include <vector>
#include <emscripten/emscripten.h>
#include <sstream>

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif

EXTERN EMSCRIPTEN_KEEPALIVE void myFunction(int argc, char ** argv) {
    printf("MyFunction Called\n");
}

char* createDynamicString(const std::string& source) {
    // Allocate memory for the string (including the null terminator)
    char* dynamicString = new char[source.length() + 1];

    // Copy the content to the allocated memory
    std::strcpy(dynamicString, source.c_str());

    return dynamicString;
}

// ident, returnType, argTypes, args, opts

std::string escapeForJson(const std::string& input) {
    std::string result;
    result.reserve(input.length() + 2);  // Reserve enough space for the escaped string

    result += '"';  // Add double quote at the beginning

    for (char c : input) {
        switch (c) {
            case '\"':
                result += "\\\"";
                break;
            case '\\':
                result += "\\\\";
                break;
            case '/':
                result += "\\/";
                break;
            case '\b':
                result += "\\b";
                break;
            case '\f':
                result += "\\f";
                break;
            case '\n':
                result += "\\n";
                break;
            case '\r':
                result += "\\r";
                break;
            case '\t':
                result += "\\t";
                break;
            // Add other cases for characters you want to escape
            default:
                result += c;
                break;
        }
    }

    result += '"';  // Add double quote at the end

    return result;
}

// Function to convert vector of strings to JSON array
std::string vectorToJsonArray(const std::vector<std::string>& inputVector) {
    std::stringstream jsonStream;

    jsonStream << "[";

    // Iterate over the vector
    for (size_t i = 0; i < inputVector.size(); ++i) {
        // Escape each element
        jsonStream << escapeForJson(inputVector[i]);

        // Add a comma if it's not the last element
        if (i < inputVector.size() - 1) {
            jsonStream << ",";
        }
    }

    jsonStream << "]";

    return jsonStream.str();
}



EXTERN EMSCRIPTEN_KEEPALIVE
const char* getCapturedGroups(const char* pattern_str, const char* str_str) {
    const std::string pattern = std::string(pattern_str);
    const std::string str = std::string(str_str);
    std::regex regex(pattern);
    std::smatch match;
    
    if (std::regex_match(str, match, regex)) {
        // The first element of match contains the entire matched string
        // The subsequent elements (from index 1) contain captured groups
        const auto output = vectorToJsonArray({match.begin(), match.end()});
        return createDynamicString(output);
    } else {
        const auto output = createDynamicString("[]");
        return output; // Return an empty vector if there are no matches
    }
}


int main() {
    return 0;
    // // Test strings and patterns with capture groups
    // const std::vector<std::pair<std::string, std::string>> test_cases = {
    //     {"^([0-9]{3})-([0-9]{2})-([[:digit:]]{4})$", "123-45-6789"},  // Matching SSN pattern with capture groups
    //     {"^([0-9]{3})-([0-9]{2})-([0-9]{4})$", "abc-12-3456"},  // Non-matching SSN pattern
    //     {"^([0-9]{3})-([0-9]{2})-([0-9]{4})$", "987-65-4321"},  // Matching SSN pattern with capture groups
    //     {"^([0-9]{3})-([0-9]{2})-([0-9]{4})$", "123-456-7890"}  // Non-matching SSN pattern
    // };

    // // Loop through the test cases and display results
    // for (const auto& test_case : test_cases) {
    //     auto captured_groups = getCapturedGroups(test_case.first, test_case.second);
    //     std::std::cout << "Captured groups for string '" << test_case.second << "' with pattern '" << test_case.first << "': ";
        
    //     std::std::cout << "captured_groups = " << (captured_groups) << "\n";

    //     std::std::cout << std::endl;
    // }

    // return 0;  // Exit successfully
}


// EXTERN EMSCRIPTEN_KEEPALIVE
// const char * main() {
//     // Define a regular expression pattern
//     const char *pattern = "^[0-9]{3}-[0-9]{2}-[0-9]{4}$";  // This example matches Social Security Numbers (SSN)

//     // Compile the regular expression
//     regex_t regex;
//     int compile_status = regcomp(&regex, pattern, REG_EXTENDED);
//     if (compile_status != 0) {
//         // If there's an error compiling the regular expression, print an error message
//         char error_message[100];
//         regerror(compile_status, &regex, error_message, sizeof(error_message));
//         fprintf(stderr, "Error compiling regex: %s\n", error_message);
//         return 1;  // Exit with an error code
//     }

//     // Test strings to match
//     const char *test_strings[] = {
//         "123-45-6789",
//         "abc-12-3456",
//         "987-65-4321",
//         "123-456-7890"
//     };

//     // Loop through the test strings and match against the regular expression
//     for (int i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); i++) {
//         if (regexec(&regex, test_strings[i], 0, NULL, 0) == 0) {
//             printf("String '%s' matches the pattern.\n", test_strings[i]);
//         } else {
//             printf("String '%s' does not match the pattern.\n", test_strings[i]);
//         }
//     }

//     // Free the compiled regular expression
//     regfree(&regex);

//     return 0;  // Exit successfully
// }