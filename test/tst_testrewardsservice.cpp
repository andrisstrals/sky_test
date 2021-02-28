#include <catch2/catch.hpp>
#include "trompeloeil/catch2/trompeloeil.hpp"


#include <IEligibilityService.hpp>
#include <RewardsServiceImpl.hpp>


#include <iostream>


class mockEligibility : public trompeloeil::mock_interface<IEligibilityService<std::string> > {
public:
    MAKE_MOCK1(checkEligibility, IEligibilityService::Eligibility(const std::string&), override);
};

TEST_CASE("RewardsServiceTestnoEligibilityService", "[dry]")
{

    RewardsService<std::string> serv;
    RewardsService<std::string>::Response resp = serv.getRewards("abc", std::set<Subscription>());

    REQUIRE(resp.requestSuccessful == false);
    REQUIRE(resp.infoMessage == "No EligibilityService available");

}

TEST_CASE("RewardsHappyScenario") {
    RewardsService<std::string> serv;
    mockEligibility eligibility;

    serv.setEligibilityService(std::make_shared<mockEligibility>());

    SECTION("TestEmptySubscription") {
        RewardsService<std::string>::Response resp = serv.getRewards("abc", std::set<Subscription>());
        REQUIRE(resp.requestSuccessful == true);
        REQUIRE(resp.rewards.size() == 0);
    }
}