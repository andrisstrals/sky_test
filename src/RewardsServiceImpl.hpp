#ifndef REWARDSSERVICEIMPL_HPP
#define REWARDSSERVICEIMPL_HPP

#include "IRewardsService.hpp"
#include "IEligibilityService.hpp"
#include "Subscription.hpp"

#include <memory>
#include <set>
#include <map>
#include <string>

template <typename T>
class RewardsService : public IRewardsService<T>  {
public:
    virtual ~RewardsService() = default;


    void setEligibilityService(std::shared_ptr<IEligibilityService<T> > service) override {
        m_eligibilityService = service;
    }


    typename IRewardsService<T>::Response getRewards(const T &accountNo, const std::set<Subscription> &subscriptions) override {
        typename IRewardsService<T>::Response resp;
        if(m_eligibilityService.get() == nullptr) {
            resp.requestSuccessful = false;
            resp.infoMessage = "No EligibilityService available";
        }

        return resp;
    }

    // loads rewards for subscription from external source (db, network, file, etc...)
    void loadRewards() override {
        
    }

private:
    std::shared_ptr<IEligibilityService<T> > m_eligibilityService;

    // in case there is more than one reward for subscription
    std::map<Subscription, std::set<Reward> > m_rewardsMapping;

};



#endif  //REWARDSSERVICEIMPL_HPP

