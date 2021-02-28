#ifndef IELIGIBILITYSERVICE_HPP
#define IELIGIBILITYSERVICE_HPP

template <typename T>
class IEligibilityService {
public:
    enum class Eligibility {
        CUSTOMER_ELIGIBLE,
        CUSTOMER_INELIGIBLE
    };

    virtual ~IEligibilityService() = default;

    // checks if provided account is eligible for rewards
    // throws exception on technical fault or invalid account number
    virtual IEligibilityService::Eligibility
     checkEligibility(const T &accountNo) = 0;
    // virtual bool
};

#endif      //IELIGIBILITYSERVICE_HPP
