#include <catch2/catch.hpp>
#include "trompeloeil/catch2/trompeloeil.hpp"


#include <IEligibilityService.hpp>
#include <RewardsServiceImpl.hpp>


#include <iostream>
#include <memory>

using trompeloeil::_;


class mockEligibility : public IEligibilityService<std::string> {
public:
    MAKE_MOCK1(checkEligibility, IEligibilityService<std::string>::Eligibility(const std::string&), override);
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

    serv.setEligibilityService(&eligibility);
    serv.loadRewards();

    SECTION("TestEmptySubscription") {
        ALLOW_CALL(eligibility, checkEligibility(_))
                    .RETURN(IEligibilityService<std::string>::Eligibility::CUSTOMER_ELIGIBLE);
        RewardsService<std::string>::Response resp = serv.getRewards("abc", std::set<Subscription>());
        REQUIRE(resp.requestSuccessful == true);
        REQUIRE(resp.rewards.size() == 0);
    }

    SECTION("Test SPORTS Subscription eligible") {
        std::set<Subscription> subs {Subscription::Channel::SPORTS};
        REQUIRE_CALL(eligibility, checkEligibility("abc"))
                    .RETURN(IEligibilityService<std::string>::Eligibility::CUSTOMER_ELIGIBLE);

        RewardsService<std::string>::Response resp = serv.getRewards("abc", subs);
        REQUIRE(resp.requestSuccessful == true);
        REQUIRE(resp.rewards.size() == 1);
        REQUIRE(resp.rewards.find(Reward::CHAMPIONS_LEAGUE_FINAL_TICKET) != resp.rewards.end());
    }

    SECTION("Test MUSIC Subscription eligible") {
        std::set<Subscription> subs {Subscription::Channel::MUSIC};
        REQUIRE_CALL(eligibility, checkEligibility("abc"))
                    .RETURN(IEligibilityService<std::string>::Eligibility::CUSTOMER_ELIGIBLE);

        RewardsService<std::string>::Response resp = serv.getRewards("abc", subs);
        REQUIRE(resp.requestSuccessful == true);
        REQUIRE(resp.rewards.size() == 1);
        REQUIRE(resp.rewards.find(Reward::KARAOKE_PRO_MICROPHONE) != resp.rewards.end());
    }

    SECTION("Test MOVIES Subscription eligible") {
        std::set<Subscription> subs {Subscription::Channel::MOVIES};
        REQUIRE_CALL(eligibility, checkEligibility("abc"))
                    .RETURN(IEligibilityService<std::string>::Eligibility::CUSTOMER_ELIGIBLE);

        RewardsService<std::string>::Response resp = serv.getRewards("abc", subs);
        REQUIRE(resp.requestSuccessful == true);
        REQUIRE(resp.rewards.size() == 1);
        REQUIRE(resp.rewards.find(Reward::PIRATES_OF_THE_CARIBBEAN_COLLECTION) != resp.rewards.end());
    }

    SECTION("Test KIDS & NEWS Subscription eligible") {
        std::set<Subscription> subs {Subscription::Channel::KIDS, Subscription::Channel::NEWS};
        ALLOW_CALL(eligibility, checkEligibility("abc"))
                    .RETURN(IEligibilityService<std::string>::Eligibility::CUSTOMER_ELIGIBLE);

        RewardsService<std::string>::Response resp = serv.getRewards("abc", subs);
        REQUIRE(resp.requestSuccessful == true);
        REQUIRE(resp.rewards.size() == 0);
    }

    SECTION("Test Multi Rewards") {
        std::set<Subscription> subs {Subscription::Channel::SPORTS,
                                     Subscription::Channel::MUSIC,
                                     Subscription::Channel::MOVIES,
                                     Subscription::Channel::KIDS,
                                     Subscription::Channel::NEWS};

        REQUIRE_CALL(eligibility, checkEligibility("abc"))
                    .TIMES(1)
                    .RETURN(IEligibilityService<std::string>::Eligibility::CUSTOMER_ELIGIBLE);

        RewardsService<std::string>::Response resp = serv.getRewards("abc", subs);
        REQUIRE(resp.requestSuccessful == true);
        REQUIRE(resp.rewards.size() == 3);
        REQUIRE(resp.rewards.find(Reward::CHAMPIONS_LEAGUE_FINAL_TICKET) != resp.rewards.end());
        REQUIRE(resp.rewards.find(Reward::KARAOKE_PRO_MICROPHONE) != resp.rewards.end());
        REQUIRE(resp.rewards.find(Reward::PIRATES_OF_THE_CARIBBEAN_COLLECTION) != resp.rewards.end());
    }
}

TEST_CASE("Rewards INELIGIBLE Scenario") {
    RewardsService<std::string> serv;
    mockEligibility eligibility;

    serv.setEligibilityService(&eligibility);
    serv.loadRewards();
    SECTION("Test Multi Rewards") {
        std::set<Subscription> subs {Subscription::Channel::SPORTS,
                                     Subscription::Channel::MUSIC,
                                     Subscription::Channel::MOVIES,
                                     Subscription::Channel::KIDS,
                                     Subscription::Channel::NEWS};

        REQUIRE_CALL(eligibility, checkEligibility("abc"))
                    .TIMES(1)
                    .RETURN(IEligibilityService<std::string>::Eligibility::CUSTOMER_INELIGIBLE);

        RewardsService<std::string>::Response resp = serv.getRewards("abc", subs);
        REQUIRE(resp.requestSuccessful == true);
        REQUIRE(resp.rewards.size() == 0);
    }
}


TEST_CASE("Invalid account number") {
    RewardsService<std::string> serv;
    mockEligibility eligibility;

    serv.setEligibilityService(&eligibility);
    serv.loadRewards();
    SECTION("Test Multi Rewards") {
        std::set<Subscription> subs {Subscription::Channel::SPORTS,
                                     Subscription::Channel::MUSIC,
                                     Subscription::Channel::MOVIES,
                                     Subscription::Channel::KIDS,
                                     Subscription::Channel::NEWS};

        REQUIRE_CALL(eligibility, checkEligibility("abc"))
                    .THROW(std::domain_error("Invalid account number"));

        RewardsService<std::string>::Response resp = serv.getRewards("abc", subs);
        REQUIRE(resp.requestSuccessful == false);
        REQUIRE(resp.rewards.size() == 0);
        REQUIRE(resp.infoMessage == "Invalid account number");
    }
}

TEST_CASE("Technical failure") {
    RewardsService<std::string> serv;
    mockEligibility eligibility;

    serv.setEligibilityService(&eligibility);
    serv.loadRewards();
    SECTION("Test Multi Rewards") {
        std::set<Subscription> subs {Subscription::Channel::SPORTS,
                                     Subscription::Channel::MUSIC,
                                     Subscription::Channel::MOVIES,
                                     Subscription::Channel::KIDS,
                                     Subscription::Channel::NEWS};

        REQUIRE_CALL(eligibility, checkEligibility("abc"))
                    .THROW(std::runtime_error("Technical failure"));

        RewardsService<std::string>::Response resp = serv.getRewards("abc", subs);
        REQUIRE(resp.requestSuccessful == false);
        REQUIRE(resp.rewards.size() == 0);
        REQUIRE(resp.infoMessage == "");
    }
}


