#pragma once

namespace wce {

template <class TSender>
class BaseEventArgs {
public:
    explicit BaseEventArgs(TSender& sender);

    virtual ~BaseEventArgs() { }

    TSender& getSender();

private:
    TSender& m_sender;
};

template<class TSender>
BaseEventArgs<TSender>::BaseEventArgs(TSender &sender)
    : m_sender(sender) { }

template<class TSender>
TSender &BaseEventArgs<TSender>::getSender() {
    return m_sender;
}

}




