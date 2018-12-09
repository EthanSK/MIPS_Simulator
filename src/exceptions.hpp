#include <iostream>
#include <exception>

struct Mips_exception : public std::exception
{
    virtual int exit_code() const = 0;
};

struct End_of_program : public std::exception //much easier to implement as exception as we want to ignore delay slot forcefully
{
    const char *what() const throw() override
    {
        return "End of program";
    }
};

struct Arithmetic_exception : public Mips_exception
{
    const char *what() const throw() override
    {
        return "Arithmetic exception";
    }

    int exit_code() const override
    {
        return -10;
    }
};

struct Memory_exception : public Mips_exception
{
    const char *what() const throw() override
    {
        return "Memory exception";
    }
    int exit_code() const override
    {
        return -11;
    }
};

struct Invalid_instruction_exception : public Mips_exception
{
    const char *what() const throw() override
    {
        return "Invalid instruction exception";
    }
    int exit_code() const override
    {
        return -12;
    }
};

struct IO_error : public Mips_exception
{
    const char *what() const throw() override
    {
        return "IO error";
    }
    int exit_code() const override
    {
        return -21;
    }
};

struct Internal_error : public Mips_exception
{
    const char *what() const throw() override
    {
        return "Internal error";
    }
    int exit_code() const override
    {
        return -20;
    }
};

struct Environment_error : public IO_error
{
    const char *what() const throw() override
    {
        return "Environment error";
    }
};

struct Address_exception : public Memory_exception
{
    const char *what() const throw() override
    {
        return "Address exception";
    }
};
