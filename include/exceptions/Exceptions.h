#pragma once

class Exceptions {
public:
    virtual void printError();
};


class StackEmptyException : private Exceptions {
public:
    virtual void printError();
};
