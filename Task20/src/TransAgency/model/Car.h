#pragma once

#include <string>

#include <cpe/ui/IModel.h>

class Car : public cpe::IModel {
public:
    enum Fields : uint32_t {
        F_MARK,
        F_MAKER,
        F_SEATS,
        F_STATE_NUMBER
    };

    ~Car() override;

    const std::string &mark() const;

    std::string &mark();

    const std::string &maker() const;

    std::string &maker();

    const uint32_t &seats() const;

    uint32_t &seats();

    const std::string &state_number() const;

    std::string &state_number();

    std::string field_value(uint32_t idField) const override;

    std::string to_string() const override;

private:
    std::string mMark;
    std::string mMaker;
    uint32_t mSeats;
    std::string mStateNumber;
};


