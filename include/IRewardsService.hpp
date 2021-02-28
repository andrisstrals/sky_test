#ifndef IREWARDSSERVICE_HPP
#define IREWARDSSERVICE_HPP

#include <set>
#include <string>
#include <memory>

#include "IEligibilityService.hpp"
#include "Reward.hpp"

class Subscription;

template <typename T>
class IRewardsService {
public:

    struct Response {
        bool requestSuccessful;     // indocates successful processing, not the presence of rewards
        std::set<Reward> rewards;   // actual rewards
        std::string infoMessage;    // error message incase of techical failure (if requestSuccessful is false)
    };

    virtual ~IRewardsService() = default;


    // virtual void setEligibilityService(std::shared_ptr<IEligibilityService<T> > service) = 0;
    virtual void setEligibilityService(IEligibilityService<T> *service) = 0;


    virtual IRewardsService::Response getRewards(const T &accountNo, const std::set<Subscription> &subscriptions) = 0;

    // loads rewards for subscription from external source (db, network, file, etc...)
    virtual void loadRewards() = 0;

};




#endif      //IREWARDSSERVICE_HPP
