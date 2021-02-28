#ifndef SUBSCRIPTION_HPP
#define SUBSCRIPTION_HPP


class Subscription;
bool operator<(const Subscription& lhs, const Subscription& rhs);

class Subscription {
    friend bool operator<(const Subscription& lhs, const Subscription& rhs);
public:
    enum class Channel {
        SPORTS,
        KIDS,
        MUSIC,
        NEWS,
        MOVIES
    };

    Subscription(Subscription::Channel channel) : m_channel(channel) {}
    ~Subscription() = default;

    std::string toString() {
        switch(m_channel) {
        case Subscription::Channel::SPORTS : return "SPORTS";
        case Subscription::Channel::KIDS : return "KIDS";
        case Subscription::Channel::MUSIC : return "MUSIC";
        case Subscription::Channel::NEWS : return "NEWS";
        case Subscription::Channel::MOVIES : return "MOVIES";
        }
    }

    // inline bool operator<(const Subscription& rhs) {
    //     return m_channel < rhs.m_channel;
    // }

private:
    Subscription::Channel m_channel;
};

inline bool operator<(const Subscription& lhs, const Subscription& rhs) {
    return lhs.m_channel < rhs.m_channel;
}



#endif      //SUBSCRIPTION_HPP
