#ifndef HYSQL_UTIL_EXCEPTION_H
#define HYSQL_UTIL_EXCEPTION_H

#include <cstdio>
#include <string>

namespace hysql {
namespace util {

class Error {
public:
    enum Code {
        kErrUndefined = 0,
        kErrUnsupported,
        kErrInvalideSyntax,

        kErrSchemaDuplicated,
        kErrSchemaNotExist,

        kErrTableDuplicated,
        kErrTableNotExist,
    };

private:
    Code code_;
    std::string message_;

public:
    Error(const Code code = kErrUndefined, const std::string& message = "")
        : code_(code), message_(message) {}

    std::string ToString() const {
        std::string format("%s (ERROR_CODE: %d)");
        int length =
            std::snprintf(nullptr, 0, format.c_str(), message_.c_str(), code_);
        char* buf = new char[length + 1];
        std::snprintf(buf, length + 1, format.c_str(), message_.c_str(), code_);
        std::string str(buf);
        delete[] buf;
        return str;
    }

public:
    static Error* NewUnsupportedError(const std::string& message) {
        return new Error(kErrUnsupported, message);
    }

    static Error* NewInvalidSyntaxError(const std::string& message) {
        return new Error(kErrInvalideSyntax, message);
    }

    static Error* NewSchemaDuplicatedError(const std::string& message) {
        return new Error(kErrSchemaDuplicated, message);
    }

    static Error* NewSchemaNotExistError(const std::string& message) {
        return new Error(kErrSchemaNotExist, message);
    }

    static Error* NewTableDuplicatedError(const std::string& message) {
        return new Error(kErrTableDuplicated, message);
    }

    static Error* NewTableNotExistError(const std::string& message) {
        return new Error(kErrTableNotExist, message);
    }
};

}  // namespace util
}  // namespace hysql

#endif
