#ifndef REWARD_HPP
#define REWARD_HPP

class Reward;
bool operator<(const Reward& lhs, const Reward& rhs);

class Reward {
    friend bool operator<(const Reward& lhs, const Reward& rhs);
public:
    enum class EReward {
        CHAMPIONS_LEAGUE_FINAL_TICKET,
        KARAOKE_PRO_MICROPHONE,
        PIRATES_OF_THE_CARIBBEAN_COLLECTION
    };

    Reward(Reward::EReward reward) : m_reward(reward) {}
    ~Reward() = default;

    std::string toString() {
        switch(m_reward) {
        case Reward::EReward::CHAMPIONS_LEAGUE_FINAL_TICKET : return "CHAMPIONS_LEAGUE_FINAL_TICKET";
        case Reward::EReward::KARAOKE_PRO_MICROPHONE : return "KARAOKE_PRO_MICROPHONE";
        case Reward::EReward::PIRATES_OF_THE_CARIBBEAN_COLLECTION : return "PIRATES_OF_THE_CARIBBEAN_COLLECTION";
        }
    }

private:
    Reward::EReward m_reward;
};

inline bool operator<(const Reward& lhs, const Reward& rhs) {
    return lhs.m_reward < rhs.m_reward;
}

#endif  //REWARD_HPP
