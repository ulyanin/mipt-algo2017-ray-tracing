//
// Created by ulyanin on 12.05.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_SCANNER_H
#define MIPT_ALGO2017_RAY_TRACING_SCANNER_H

#include <exception>
#include <sstream>
#include <string>
#include <fstream>
#include "../geometry/GeomFloat.h"
#include "../geometry/Vector.h"


using namespace Geometry;
using std::string;

static string ltrim(const string &s) {
    size_t beg_pos = 0;
    while (beg_pos < s.length() && isspace(s[beg_pos])) {
        beg_pos++;
    }
    return s.substr(beg_pos);
}

static string rtrim(const string &s) {
    string res = s;
    while (res.size() > 0 && isspace(res.back())) {
        res.pop_back();
    }
    return res;
}

static string trim(const string &s) {

    return ltrim(rtrim(s));
}

class FileScanner {
    std::ifstream file;

public:
    FileScanner(const string &filename) {
        FILE *c_file;
        if ((c_file = fopen(filename.c_str(), "r")) == nullptr) {
            fprintf(stderr, "Error with file open");
            throw std::exception();
        }
        fclose(c_file);
        file.open(filename, std::ios_base::in);
    }

    bool eof() const {
        return file.eof();
    }

    string nextLine() {
        string line;
        while (!file.eof()) {
            getline(file, line);
            line = trim(line);

            if (line[0] == '#' || line == "") {
                line = "";
                continue;
            } else {
                break;
            }
        }

        return line;
    }

    void close() {
        file.close();
    }

    ~FileScanner() {
        close();
    }
};

class StringScanner {
    std::stringstream stream;
public:
    StringScanner() {}

    StringScanner(const string &s) : stream(s) {}

    void setBuffer(const string &s) {
        stream = std::stringstream(s);
    }

    string nextString() {
        string res;
        stream >> res;
        return res;
    }

    int nextInt() {
        int res = 0;
        stream >> res;
        return res;
    }

    Float nextDouble() {
        Float res;
        stream >> res;
        return res;
    }

    Vector nextVector() {
        Float x, y, z;
        x = nextDouble();
        y = nextDouble();
        z = nextDouble();
        return std::move(Vector(x, y, z));
    }
};

#endif //MIPT_ALGO2017_RAY_TRACING_SCANNER_H
