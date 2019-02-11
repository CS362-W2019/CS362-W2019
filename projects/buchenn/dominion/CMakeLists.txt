cmake_minimum_required(VERSION 3.13)
project(dominion C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(dominion
        badTestDrawCard.c
        betterTestDrawCard.c
        dominion.c
        dominion.h
        dominion_helpers.h
        interface.c
        interface.h
        playdom.c
        player.c
        rngs.c
        rngs.h
        rt.c
        supplyTest.c
        testBuyCard.c
        testDrawCard.c
        testInit.c
        testShuffle.c
        myTestSuite.c
        myTestSuite.h
        unittest1.c
        unittest2.c
        unittest3.c
        unittest4.c
        cardtest1.c
        cardtest2.c
        cardtest3.c
        cardtest4.c)
