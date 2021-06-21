#pragma once
#include <iostream>
#include <string>
#include "typedefs.h"


class BaseError
{
    friend std::ostream& operator<<(std::ostream& out, const BaseError& e) { return e.print(out); }
    protected:
    const std::string message;
    virtual std::ostream& print(std::ostream&) const = 0;
    BaseError(std::string msg) : message(msg) {}
};


class CMDLineError : public BaseError
{
    const std::string arg;
    public:
    CMDLineError(std::string, std::string);
    std::ostream& print(std::ostream&) const override;
};


class FileError : public BaseError
{
    protected:
    const std::string filename;
    public:
    FileError(std::string, std::string);
    enum location : u8
    {
        table  = 1 << 0,
        column = 1 << 1,
        object = 1 << 2
    };
};


class ParserError : public FileError
{
    protected:
    const std::string code;
    const int line;
    const short column;
    public:
    ParserError(std::string, std::string, std::string, int, short);
    std::ostream& print(std::ostream&) const override;
};


class ReadError : public FileError
{
    protected:
    const u16 index;
    public:
    ReadError(std::string, std::string, u16);
    std::ostream& print(std::ostream&) const override;
};


class WriteError : public FileError
{
    public:
};


class TableError : public BaseError
{
    protected:
    const std::string table_name;
};


class ColumnError : public TableError
{
    protected:
    const std::string col_name;
};


class ConstraintError : public ColumnError
{
    protected:
    const std::string name;
};
