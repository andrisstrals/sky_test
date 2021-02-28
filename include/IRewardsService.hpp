#ifndef IREWARDSSERVICE_HPP
#define IREWARDSSERVICE_HPP

#include <set>
#include <string>
#include <memory>

class Subscription;
class Reward;

template <typename T>
class IRewardsService {
public:

    struct Response {
        bool requestSuccessful;     // indocates successful processing, not the presence of rewards
        std::set<Reward> rewards;   // actual rewards
        std::string infoMessage;    // error message incase of techical failure (if requestSuccessful is false)
    };

    virtual ~IRewardsService() = default;


    virtual void setEligibilityService(std::shared_ptr<IEligibilityService> service) = 0;

    // rewards response returned async via Recipient interface
    virtual IRewardsService::Response getRewards(const T &accountNo, const std::set<Subscription> &subscriptions) = 0;


};




#endif      //IREWARDSSERVICE_HPP
