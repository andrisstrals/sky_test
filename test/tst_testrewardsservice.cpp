#include <catch2/catch.hpp>

#include <IEligibilityService.hpp>
#include <RewardsServiceImpl.hpp>


#include <iostream>

TEST_CASE("RewardsServiceTestnoEligibilityService", "[alone]")
{

    RewardsService<std::string> serv;
    RewardsService<std::string>::Response resp = serv.getRewards("abc", std::set<Subscription>());

    REQUIRE(resp.requestSuccessful == false);
    REQUIRE(resp.infoMessage == "No EligibilityService available");

}
