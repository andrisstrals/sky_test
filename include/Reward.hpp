#ifndef REWARD_HPP
#define REWARD_HPP


class Reward {
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


#endif  //REWARD_HPP
